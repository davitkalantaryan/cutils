# cutils  
  
  
## Introduction  
  
If you are doing C development then you will find here some stuff (headers some tools as well example files) to help with it (C development).  
  
  
## What is available 
    
    
  
### Some tools  
 1. Hash table in C. See: [dllhash.h](include/cinternal/hash/dllhash.h)  
 2. List in the C. See: [dllist.h](include/cinternal/list/dllist.h)  
   
     
  
### Changing function during runtime windows  
  
Code example [main_function_changer_test.c](src/tests/main_function_changer_test.c)  
  
```cpp  
#include <cutils/replace_function.h>
#include <stdlib.h>
#include <stdio.h>

typedef void* (*TypeMallocFnc)(size_t);
typedef void (*TypeFreeFnc)(void*);

static TypeMallocFnc    s_originalMalloc = &malloc;
static TypeFreeFnc    s_originalFree = &free;
static int CPPUTILS_THREAD_LOCAL  s_nIgnoreThisStack = 0;

static void* MyMalloc(size_t a_size){
	void* pRet;
	if (s_nIgnoreThisStack) {
		pRet = (*s_originalMalloc)(a_size);
	}
	else {
		s_nIgnoreThisStack = 1;
		pRet = (*s_originalMalloc)(a_size);
		printf(" +++++ MyMalloc pRet=%p\n", pRet);
		s_nIgnoreThisStack = 0;
	}
	return pRet;
}

static void MyFree(void* a_ptr){
	if (s_nIgnoreThisStack) {
		(*s_originalFree)(a_ptr);
	}
	else {
		s_nIgnoreThisStack = 1;
		printf(" ----- MyFree pRet=%p\n", a_ptr);
		(*s_originalFree)(a_ptr);
		s_nIgnoreThisStack = 0;
	}
}

int main(void){
	void* pMem;
	struct SCInternalReplaceFunctionData aReplaceData[2];

	s_originalMalloc = &malloc;
	s_originalFree = &free;

	aReplaceData[0].funcname = "malloc";
	aReplaceData[0].newFuncAddress = &MyMalloc;

	aReplaceData[1].funcname = "free";
	aReplaceData[1].newFuncAddress = &MyFree;

	CInternalReplaceFunctions(2, aReplaceData);

	pMem = malloc(100);
	printf("pMem = %p\n", pMem);
	free(pMem);

	return 0;
}
```  
  
  
### Load or free library on other process  
See: 
[loadfreelib_on_remote_process.h](include/cutils/loadfreelib_on_remote_process.h) and 
[loadfreelib_on_remote_process_sys.h](include/cutils/loadfreelib_on_remote_process_sys.h) 
works only for Windows and Linux X64
  
  
  
## Conclusion  
  
The expectation is that these codes are good examples (starting points) for clean C development. 
If you will have any questions concerning stuff in this repository or in C at all, please let me know.
