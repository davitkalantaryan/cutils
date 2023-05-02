

// see: https://stackoverflow.com/questions/24355344/inject-shared-library-into-a-process
#ifndef _GNU_SOURCE
#define  _GNU_SOURCE
#endif
#ifndef __USE_GNU
#define  __USE_GNU
#endif
#include <dlfcn.h>
#include <sys/ptrace.h>
#include <sys/user.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/syscall.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#define DLL_TO_LOAD "libtest_lib01.so"
#define LIBDL_DLL_NAME  "libdl-2.31.so"

bool WriteDataToProcess(int a_pid, unsigned long a_addr, const unsigned char* a_data, size_t a_dataLen)
{
    long data = 0;
    size_t rmn, itr = 0;
    const size_t itersCount = a_dataLen / 8;

    for(;itr<itersCount;++itr){
        memcpy(&data, a_data + 8*itr, 8);
        //if (ptrace(PTRACE_POKETEXT, (pid_t)a_pid, (void *)(a_addr + 8*itr), (void *)(a_data + 8*itr))){
        //    return false;
        //}
        if (ptrace(PTRACE_POKETEXT, (pid_t)a_pid, (void *)(a_addr + 8*itr), data)){
            return false;
        }
    }

    rmn = a_dataLen % 8;
    if(rmn){
        memcpy(&data, a_data + 8*itr, rmn);
        if (ptrace(PTRACE_POKETEXT, (pid_t)a_pid, (void *)(a_addr + 8*itr), data)){
            return false;
        }
    }

    return true;
}


void injectme(void) {
    asm("mov $2, %esi\n"
        "call *%rax\n"
        "int $0x03\n"
    );
}


unsigned long long findLibrary(const char *library, pid_t pid) {
char mapFilename[1024];
char buffer[9076];
FILE *fd;
unsigned long long addr = 0;

    if (pid == -1) {
        snprintf(mapFilename, sizeof(mapFilename), "/proc/self/maps");
    } else {
        snprintf(mapFilename, sizeof(mapFilename), "/proc/%d/maps", pid);
    }

    fd = fopen(mapFilename, "r");

    while(fgets(buffer, sizeof(buffer), fd)) {
        if (strstr(buffer, library)) {
            addr = strtoull(buffer, NULL, 16);
            break;
        }
    }

    fclose(fd);

    return addr;
}


static unsigned long freeAddressSpaceOnRemoteProcess(pid_t a_pid)
{
    FILE *fp;
    char filename[30];
    char line[850];
    unsigned long addr = 0;
    char str[20];
    char perms[5];

    sprintf(filename, "/proc/%d/maps", a_pid);
    if ((fp = fopen(filename, "r")) == NULL) {
        printf("[!] Error, could not open maps file for process %d\n", a_pid);
        return 0;
    }

    while(fgets(line, 850, fp) != NULL) {
        sscanf(line, "%lx-%*lx %s %*s %s %*d", &addr, perms, str);
        if(strstr(perms, "x") != NULL) {break;}
    }

    fclose(fp);
    return addr;
}




int main(int argc, char *argv[])
{
    int status;
    struct user_regs_struct oldregs, regs;
    unsigned long  pid, addr, fn_addr, data_addr, lib_dl_address_on_remote,lib_dl_address_here, dlopen_address_on_remote, dlopen_address_here;
    siginfo_t      info;
    char           dummy;
    size_t itr;
    const size_t strLenPlus1 = strlen(DLL_TO_LOAD) + 1;

    {
       void *handle;
       const char *error;
       handle = dlopen(LIBDL_DLL_NAME, RTLD_LAZY);
       if (!handle) {
           fprintf(stderr, "%s\n", dlerror());
           return 1;
       }
       dlopen_address_here = (unsigned long)dlsym(handle, "dlopen");
       if ((error = dlerror()) != NULL)  {
           fprintf(stderr, "%s\n", error);
           return 1;
       }
       printf("dlopen address: %p\n", (void*)dlopen_address_here);
       dlclose(handle);
   }


    //unsigned char injectCode[] = {
    //    0x48, 0xC7, 0xC7, 0x00, 0x00, 0x00, 0x00, // mov rdi, 0x0 (placeholder for address)
    //    0x48, 0xC7, 0xC6, 0x00, 0x00, 0x00, 0x00, // mov rsi, 0x0 (placeholder for flags)
    //    0xE8, 0x00, 0x00, 0x00, 0x00 // callq (placeholder for dlopen)
    //};

    //unsigned char injectCode[] = {0xe8,0x6a,0xea,0xff,0xff};

    //unsigned char injectCode[] = {0xff,0xd0,0xcd,0x03};
    const unsigned char injectCode[] = {0xff,0xd0};
    const size_t injectCodeSize = sizeof(injectCode);

    //unsigned char* injectCode = (unsigned char*)(&injectme)+4;
    //const size_t injectCodeSize = 32;
    size_t itersCount;
    unsigned long save[1024];

    itersCount = ((strLenPlus1 + injectCodeSize)/8)+1;

    if (argc < 2 || !strcmp(argv[1], "-h") || !strcmp(argv[1], "--help")) {
        fprintf(stderr, "\n");
        fprintf(stderr, "Usage: %s [ -h | --help ]\n", argv[0]);
        fprintf(stderr, "       %s PID ADDRESS\n", argv[0]);
        fprintf(stderr, "\n");
        return 1;
    }

    if (sscanf(argv[1], " %lu %c", &pid, &dummy) != 1 || pid < 1UL) {
        fprintf(stderr, "%s: Invalid process ID.\n", argv[1]);
        return 1;
    }

    lib_dl_address_on_remote = findLibrary(LIBDL_DLL_NAME, pid);
    if(!lib_dl_address_on_remote){
        return 1;
    }
    lib_dl_address_here = findLibrary(LIBDL_DLL_NAME, -1);
    if(!lib_dl_address_here){
        return 1;
    }

    //if (sscanf(argv[2], " %lx %c", &addr, &dummy) != 1) {
    //    fprintf(stderr, "%s: Invalid address.\n", argv[2]);
    //    return 1;
    //}
    addr = freeAddressSpaceOnRemoteProcess(pid);
    if ((!addr) || (addr & 7)) {
        fprintf(stderr, "%s: Address is not a multiple of 8.\n", argv[2]);
        return 1;
    }

    //if (sscanf(argv[3], " %lx %c", &lib_dl_address_on_remote, &dummy) != 1) {
    //    fprintf(stderr, "%s: Invalid address.\n", argv[2]);
    //    return 1;
    //}

    fn_addr= addr;
    data_addr = addr + injectCodeSize;
    dlopen_address_on_remote = lib_dl_address_on_remote + (dlopen_address_here - lib_dl_address_here);

    //// set the address of the string in the injected code
    //*(unsigned long long int *)&injectCode[2] = (unsigned long long int)data_addr;
    //// set the value of the flags in the injected code
    //*(unsigned long long int *)&injectCode[9] = (unsigned long long int)RTLD_NOW;
    //// set the address of the dlopen function in the injected code
    //*(long long int *)&injectCode[14] = (unsigned long long int)dlopen_address_on_remote;

    /* Attach to the target process. */
    if (ptrace(PTRACE_ATTACH, (pid_t)pid, NULL, NULL)) {
        fprintf(stderr, "Cannot attach to process %lu: %s.\n", pid, strerror(errno));
        return 1;
    }

    /* Wait for attaching to complete. */
    waitid(P_PID, (pid_t)pid, &info, WSTOPPED);

    /* Get target process (main thread) register state. */
    if (ptrace(PTRACE_GETREGS, (pid_t)pid, NULL, &oldregs)) {
        fprintf(stderr, "Cannot get register state from process %lu: %s.\n", pid, strerror(errno));
        ptrace(PTRACE_DETACH, (pid_t)pid, NULL, NULL);
        return 1;
    }

    /* Save the bytes at the specified address in the target process. */
    for(itr=0;itr<itersCount;++itr){
        save[itr] = ptrace(PTRACE_PEEKTEXT, (pid_t)pid, (void *)(addr + itr*8), NULL);
    }


    /* Replace the bytes */
    if(!WriteDataToProcess(pid,fn_addr,injectCode,injectCodeSize)){
        ptrace(PTRACE_DETACH, (pid_t)pid, NULL, NULL);
        return 1;
    }
    if(!WriteDataToProcess(pid,data_addr,(const unsigned char*)DLL_TO_LOAD,strLenPlus1)){
        ptrace(PTRACE_DETACH, (pid_t)pid, NULL, NULL);
        return 1;
    }
    //WriteDataToProcess(pid, data_addr+16, (const unsigned char*)"\x90\x90\x90\x90\x90\x90\x90", 8);

    /* Modify process registers, to execute the just inserted code. */
    regs = oldregs;
    regs.rip = (unsigned long long int)fn_addr;
    regs.rax = (unsigned long long int)dlopen_address_on_remote;
    regs.rdi = (unsigned long long int)data_addr;
    regs.rsi = (unsigned long long int)RTLD_NOW;
    if (ptrace(PTRACE_SETREGS, (pid_t)pid, NULL, &regs)) {
        fprintf(stderr, "Cannot set register state from process %lu: %s.\n", pid, strerror(errno));
        ptrace(PTRACE_DETACH, (pid_t)pid, NULL, NULL);
        return 1;
    }

    /* Do the syscall. */
    if (ptrace(PTRACE_CONT, (pid_t)pid, NULL, NULL)) {
        fprintf(stderr, "Cannot execute injected code to process %lu: %s.\n", pid, strerror(errno));
        ptrace(PTRACE_DETACH, (pid_t)pid, NULL, NULL);
        return 1;
    }

    /* Wait for the client to execute the syscall, and stop. */
    waitpid(pid, &status, WUNTRACED);
    if (WIFSTOPPED(status) && WSTOPSIG(status) == SIGTRAP) {
        // Get process registers, indicating if the injection suceeded
        ptrace(PTRACE_GETREGS, pid, NULL, &regs);
        if (regs.rax != 0x0) {
            printf("[*] Injected library loaded at address %p\n", (void*)regs.rax);
        } else {
            printf("[!] Library could not be injected\n");
        }
    } else {
        printf("[!] Fatal Error: Process stopped for unknown reason\n");
    }


    /* Revert the bytes we modified. */
    for(itr=0;itr<itersCount;++itr){
        if (ptrace(PTRACE_POKETEXT, (pid_t)pid, (void *)(addr + 8*itr), (void *)save[itr])){
            fprintf(stderr, "Cannot revert process %lu code modifications: %s.\n", pid, strerror(errno));
            ptrace(PTRACE_DETACH, (pid_t)pid, NULL, NULL);
            return 1;
        }
    }

    /* Revert the registers, too, to the old state. */
    if (ptrace(PTRACE_SETREGS, (pid_t)pid, NULL, &oldregs)) {
        fprintf(stderr, "Cannot reset register state from process %lu: %s.\n", pid, strerror(errno));
        ptrace(PTRACE_DETACH, (pid_t)pid, NULL, NULL);
        return 1;
    }

    /* Detach. */
    if (ptrace(PTRACE_DETACH, (pid_t)pid, NULL, NULL)) {
        fprintf(stderr, "Cannot detach from process %lu: %s.\n", pid, strerror(errno));
        return 1;
    }

    fprintf(stderr, "Done.\n");

    return 0;
}
