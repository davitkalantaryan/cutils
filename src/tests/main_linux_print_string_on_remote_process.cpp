
// see: https://stackoverflow.com/questions/24355344/inject-shared-library-into-a-process
#ifndef _GNU_SOURCE
#define  _GNU_SOURCE
#endif
#include <sys/ptrace.h>
#include <sys/user.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/syscall.h>
#include <string.h>
#include <errno.h>
#include <stdio.h>
#include <unistd.h>


static unsigned long freeAddressSpaceOnRemoteProcess(pid_t a_pid)
{
	FILE *fp;
	char filename[30];
	char line[850];
	unsigned long long int addr = 0;
	char str[20];
	char perms[5];
	
	sprintf(filename, "/proc/%d/maps", a_pid);
	if ((fp = fopen(filename, "r")) == NULL) {
		printf("[!] Error, could not open maps file for process %d\n", a_pid);
		return 0;
	}
	
	while(fgets(line, 850, fp) != NULL) {
		sscanf(line, "%llx-%*x %s %*s %s %*d", &addr, perms, str);
		if(strstr(perms, "x") != NULL) {break;}
	}
	
	fclose(fp);
	return addr;
}


bool WriteDataToProcess(int a_pid, unsigned long a_addr, const unsigned char* a_data, size_t a_dataLen)
{
    long data = 0;
    size_t rmn, itr = 0;
    const size_t itersCount = a_dataLen / 8;

    for(;itr<itersCount;++itr){
        memcpy(&data, a_data + 8*itr, 8);
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


int main(int argc, char *argv[])
{
    struct user_regs_struct oldregs, regs;
    unsigned long  pid, addr, fn_addr, data_addr, save[1024];
    siginfo_t      info;
    char           dummy;
    const unsigned char injectCode[8] = {0x0F, 0x05};  // for syscall
    size_t strLen;
    size_t itr,itersCount;

    if (argc < 3 || !strcmp(argv[1], "-h") || !strcmp(argv[1], "--help")) {
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

    addr = freeAddressSpaceOnRemoteProcess(pid);
    if ((!addr)||(addr & 7)) {
        fprintf(stderr, "%s: Address is not a multiple of 8.\n", argv[2]);
        return 1;
    }

    fn_addr = addr;
    data_addr = addr + 8;

    strLen = strlen(argv[2]);

    itersCount = ((strLen + 8)/8)+1;

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

    /* Replace the bytes. */
    if(!WriteDataToProcess(pid,fn_addr,injectCode,8)){
        ptrace(PTRACE_DETACH, (pid_t)pid, NULL, NULL);
        return 1;
    }
    if(!WriteDataToProcess(pid,data_addr,(unsigned char*)argv[2],strLen)){
        ptrace(PTRACE_DETACH, (pid_t)pid, NULL, NULL);
        return 1;
    }

    /* Modify process registers, to execute the just inserted code. */
    regs = oldregs;
    regs.rip = fn_addr;
    regs.rax = SYS_write;
    regs.rdi = STDERR_FILENO;
    regs.rsi = data_addr;
    regs.rdx = strLen; /* 14 bytes of message, no '\0' at end needed. */
    if (ptrace(PTRACE_SETREGS, (pid_t)pid, NULL, &regs)) {
        fprintf(stderr, "Cannot set register state from process %lu: %s.\n", pid, strerror(errno));
        ptrace(PTRACE_DETACH, (pid_t)pid, NULL, NULL);
        return 1;
    }

    /* Do the syscall. */
    if (ptrace(PTRACE_SINGLESTEP, (pid_t)pid, NULL, NULL)) {
        fprintf(stderr, "Cannot execute injected code to process %lu: %s.\n", pid, strerror(errno));
        ptrace(PTRACE_DETACH, (pid_t)pid, NULL, NULL);
        return 1;
    }

    /* Wait for the client to execute the syscall, and stop. */
    waitid(P_PID, (pid_t)pid, &info, WSTOPPED);

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
