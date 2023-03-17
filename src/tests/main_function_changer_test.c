//
// file:            main_function_changer_test.c
// path:			src/tests/main_function_changer_test.c
// created on:		2023 Mar 09
// created by:		Davit Kalantaryan (davit.kalantaryan@desy.de)
//


#include <cinternal/replace_function.h>
#include <stdlib.h>
#include <stdio.h>


typedef void* (*TypeMallocFnc)(size_t);
typedef void (*TypeFreeFnc)(void*);


static TypeMallocFnc    s_originalMalloc = &malloc;
static TypeFreeFnc    s_originalFree = &free;

static int CPPUTILS_THREAD_LOCAL  s_nIgnoreThisStack = 0;

static void* MyMalloc(size_t a_size)
{
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


static void MyFree(void* a_ptr)
{
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


int main(void)
{
	void* pMem;
	struct SCInternalReplaceFunctionData aReplaceData[2];

	s_originalMalloc = &malloc;
	s_originalFree = &free;

	aReplaceData[0].funcname = "malloc";
	aReplaceData[0].newFuncAddress = &MyMalloc;

	aReplaceData[1].funcname = "free";
	aReplaceData[1].newFuncAddress = &MyFree;

	//CInternalReplaceFunctions(2, aReplaceData);
	CInternalReplaceFunctionsAllModules(2, aReplaceData);

	pMem = malloc(100);
	printf("pMem = %p\n", pMem);
	free(pMem);

	return 0;
}
