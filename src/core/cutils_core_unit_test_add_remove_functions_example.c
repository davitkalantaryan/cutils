//
// repo:			cutils
// file:			main_cutils_unit_test.c
// path:			src/tools/cutils_unit_test/main_cutils_unit_test.c
// created on:		2023 May 18
// created by:		Davit Kalantaryan (davit.kalantaryan@gmail.com)
// comment:         This is an example file and shows how one can owerwrite some functions from cinternal unit test
//

#include <cutils/list/dllist.h>
#include <cinternal/unit_test.h>
#include <stdlib.h>
#include <stdio.h>


static CinternalDLList_t	s_listOfFunctions = CPPUTILS_NULL;
CPPUTILS_EXTERN_C_DECL CPPUTILS_DLL_PRIVATE int s_nMagicNumber;

struct SFunctionsToCall {
	TypeFunction			func;
	const char* maj, * min;
};

CPPUTILS_EXTERN_C void CinternalIterateAndCallUnitTestFunctions(void)
{    
	if (s_listOfFunctions) {
		struct SFunctionsToCall* pFunctToCall;
		CinternalDLListItem_t pItemNext, pItem = CInternalDLListFirstItem(s_listOfFunctions);
		while (pItem) {
			pItemNext = CInternalDLListItemFromDLListIterator(CInternalDLListIteratorFromDLListItem(pItem)->next);
			pFunctToCall = CPPUTILS_STATIC_CAST(struct SFunctionsToCall*, pItem->data);
			(*(pFunctToCall->func))(pFunctToCall->maj, pFunctToCall->min);
			free(pFunctToCall);
			pItem = pItemNext;
		}

		CInternalDLListDestroy(s_listOfFunctions);
		s_listOfFunctions = CPPUTILS_NULL;
	}
}


CPPUTILS_EXTERN_C void CinternalAddUnitTestFunction(TypeFunction a_function, const char* a_maj, const char* a_min)
{
	struct SFunctionsToCall* pNext;
	if (!s_listOfFunctions) {
		s_nMagicNumber = 1;
		s_listOfFunctions = CInternalDLListCreate();
		if (!s_listOfFunctions) {
			fprintf(stderr,"Unable add function to the list!\n");
			fflush(stderr);
			exit(1);
		}
	}

	pNext = (struct SFunctionsToCall*)malloc(sizeof(struct SFunctionsToCall));
	if (!pNext) {
		exit(1);
	}
	pNext->func = a_function;
	pNext->maj = a_maj;
	pNext->min = a_min;

	CInternalDLListAddDataToFrontFn(s_listOfFunctions, (void*)pNext);
}
