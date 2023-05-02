#include <stdlib.h>
#include <unistd.h>
#include <sys/mman.h>
#include <string.h>
#include <stddef.h>
#define __USE_GNU
#include <dlfcn.h>
#include <stdint.h>
#include <stdio.h>

typedef void* (*TypeMalloc)(size_t);

static TypeMalloc  s_malloc_clib = NULL;

void* my_malloc(size_t a_size) {
    // custom implementation of malloc
    // ...
    return (*s_malloc_clib)(a_size);
}

static void __attribute__ ((__constructor__)) MallocChangerInitializer(void) {
    //s_malloc_clib = &malloc;

    // Look up the original malloc function using dlsym.
        s_malloc_clib = (TypeMalloc)dlsym(RTLD_NEXT, "malloc");
        if (s_malloc_clib == NULL) {
            fprintf(stderr, "Error: failed to locate original malloc function\n");
            return;
        }
        // Calculate the address of the jump instruction that will redirect execution to our new implementation.
        void* jump_addr = (void*)my_malloc;
        // Overwrite the original malloc function with the jump instruction.
        unsigned char jump_instr[] = { 0xff, 0x25, 0x00, 0x00, 0x00, 0x00 }; // jmp *0x0(%rip)
        *(void**)(&jump_instr[2]) = &jump_addr;
        size_t page_size = sysconf(_SC_PAGESIZE);
        void* malloc_page = (void*)(((unsigned long)s_malloc_clib) & ~(page_size - 1));
        if (mprotect(malloc_page, page_size, PROT_READ | PROT_WRITE | PROT_EXEC) == -1) {
            perror("Error: failed to set page permissions");
            return;
        }
        memcpy(s_malloc_clib, jump_instr, sizeof(jump_instr));
        //printf("malloc function hooked!\n");
        mprotect(malloc_page, page_size, PROT_READ | PROT_EXEC);


    //void *mainProgramHandle = dlopen(NULL, RTLD_NOW);
    //    int64_t origFunc = (int64_t)dlsym(mainProgramHandle , "malloc");
    //    int64_t newFunc = (int64_t)&my_malloc;
    //    int64_t offset = (int64_t)newFunc - ((int64_t)origFunc + 5 * sizeof(char));

    //    //Make the memory containing the original funcion writable
    //        //Code from http://stackoverflow.com/questions/20381812/mprotect-always-returns-invalid-arguments
    //        size_t pageSize = sysconf(_SC_PAGESIZE);
    //        ptrdiff_t start = (ptrdiff_t)origFunc;
    //        ptrdiff_t end = start + 1;
    //        ptrdiff_t pageStart = start & (-pageSize);
    //        int nRet = mprotect((void *)pageStart, end - pageStart, PROT_READ | PROT_WRITE | PROT_EXEC);
    //        (void)nRet;

    //        //Insert the jump instruction at the beginning of the original function
    //        uint64_t instruction = 0xe9 | offset << 8;
    //        *((uint64_t*)origFunc) = instruction;

#if 0
    ptrdiff_t pageSize = sysconf(_SC_PAGESIZE);

    // Find the address of the process's `malloc` function in the symbol table
        void* malloc_addr_bs = (void*) (malloc);
        //void* malloc_addr = (void*) (&malloc_addr_bs);
        void* malloc_addr = malloc_addr_bs;
        ptrdiff_t malloc_addr_i = (ptrdiff_t)malloc_addr_bs;
        ptrdiff_t malloc_addr_page_start_i = malloc_addr_i & (-pageSize);
        void* malloc_addr_page_start = (void*)malloc_addr_page_start_i;

        // Allocate a page of memory with read, write, and execute permissions
        void* page = mmap(NULL, getpagesize(), PROT_READ | PROT_WRITE | PROT_EXEC, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);

        // Set the first 4 bytes of the new page to the address of our custom `my_malloc` function
        *(void**)page = my_malloc;

        // Make the page read-only and executable
        int nRet = mprotect(page, getpagesize(), PROT_READ | PROT_EXEC);
        (void)nRet;

        // Disable memory protection for the page containing the original `malloc` function
        nRet = mprotect(malloc_addr_page_start, getpagesize(), PROT_READ | PROT_WRITE | PROT_EXEC);
        (void)nRet;

        // Update the process's `malloc` function in the symbol table to point to the new page
        //*(void**) malloc_addr = (void*)my_malloc;
        memcpy(malloc_addr,(void*)my_malloc,0x500);

        // Restore memory protection for the page containing the original `malloc` function
        nRet = mprotect(malloc_addr_page_start, getpagesize(), PROT_READ | PROT_EXEC);
        (void)nRet;
#endif
}



int main(void)
{
    char* pMem = malloc(100);
    (void)pMem;
    return 0;
}
