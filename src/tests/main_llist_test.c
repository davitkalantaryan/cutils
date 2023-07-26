//
// repo:			cutils
// file:            main_llist_test.c
// path:			src/tests/main_llist_test.c
// created on:		2023 Feb 25
// created by:		Davit Kalantaryan (davit.kalantaryan@desy.de)
//

#include <cutils/list/dllist.h>
#include <cinternal/unit_test.h>
#include <stdio.h>

int main(void)
{
	int nNumber;
	CinternalDLListItem_t pItem;
	CinternalDLList_t aList = CInternalDLListCreate();

	if (!aList) {
		perror("\n");
		return 1;
	}

	CInternalDLListAddDataToFront(aList, (void*)1);
	CInternalDLListAddDataToFront(aList, (void*)2);
	CInternalDLListAddDataToFront(aList, (void*)3);
	CinternalUnitTestAssertCheckSrc(CInternalDLListSize(aList) == 3);

	nNumber = 0;
	pItem = CInternalDLListFirstItem(aList);
	while (pItem) {
		++nNumber;
		pItem = CInternalDLListItemFromDLListIterator(CInternalDLListIteratorFromDLListItem(pItem)->next);
	}

	CinternalUnitTestAssertCheckSrc(nNumber==3);
	
	pItem = CInternalDLListFirstItem(aList);
	CinternalUnitTestAssertCheckSrc(pItem);
	CinternalUnitTestAssertCheckSrc(((size_t)pItem->data)==3);

	pItem = CInternalDLListItemFromDLListIterator(CInternalDLListIteratorFromDLListItem(pItem)->next);
	CinternalUnitTestAssertCheckSrc(pItem);
	CinternalUnitTestAssertCheckSrc(((size_t)pItem->data) == 2);

	CInternalDLListDestroy(aList);

	return 0;
}
