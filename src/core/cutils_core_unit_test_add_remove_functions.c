//
// repo:			cutils
// file:			main_cutils_unit_test.c
// path:			src/tools/cutils_unit_test/main_cutils_unit_test.c
// created on:		2023 May 18
// created by:		Davit Kalantaryan (davit.kalantaryan@gmail.com)
//

#include <cutils/list/dllist.h>
#include <cinternal/unit_test_tools.h>
#include <stdlib.h>
#include <stdio.h>


static CinternalDLList_t	s_listOfFunctions = CPPUTILS_NULL;

CPPUTILS_EXTERN_C void CinternalIterateAndCallUnitTestFunctions(void)
{    
	if (s_listOfFunctions) {
		TypeFunction aFunction;
		CinternalDLListItem_t pItem = CInternalDLListFirstItem(s_listOfFunctions);
		while (pItem) {
			aFunction = CPPUTILS_REINTERPRET_CAST(TypeFunction, pItem->data);
			(*aFunction)();
			pItem = CInternalDLListItemFromDLListIterator(CInternalDLListIteratorFromDLListItem(pItem)->next);
		}

		CInternalDLListDestroy(s_listOfFunctions);
		s_listOfFunctions = CPPUTILS_NULL;
	}
}


CPPUTILS_EXTERN_C void CinternalAddUnitTestFunction(void (*a_function)(void))
{
	if (!s_listOfFunctions) {
		s_listOfFunctions = CInternalDLListCreate();
		if (!s_listOfFunctions) {
			fprintf(stderr,"Unable add function to the list!\n");
			fflush(stderr);
			exit(1);
		}
	}

	CInternalDLListAddDataToFrontFn(s_listOfFunctions, (void*)a_function);
}
