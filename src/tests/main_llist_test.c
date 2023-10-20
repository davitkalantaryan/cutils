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
	CutilDLListItem_t pItem;
	CutilDLList_t aList = CUtilDLListCreate();

	if (!aList) {
		perror("\n");
		return 1;
	}

	CUtilDLListAddDataToFront(aList, (void*)1);
	CUtilDLListAddDataToFront(aList, (void*)2);
	CUtilDLListAddDataToFront(aList, (void*)3);
	CinternalUnitTestAssertCheckSrc(CUtilDLListSize(aList) == 3);

	nNumber = 0;
	pItem = CUtilDLListFirstItem(aList);
	while (pItem) {
		++nNumber;
		pItem = CUtilDLListItemFromDLListIterator(CUtilDLListIteratorFromDLListItem(pItem)->next);
	}

	CinternalUnitTestAssertCheckSrc(nNumber==3);
	
	pItem = CUtilDLListFirstItem(aList);
	CinternalUnitTestAssertCheckSrc(pItem);
	CinternalUnitTestAssertCheckSrc(((size_t)pItem->data)==3);

	pItem = CUtilDLListItemFromDLListIterator(CUtilDLListIteratorFromDLListItem(pItem)->next);
	CinternalUnitTestAssertCheckSrc(pItem);
	CinternalUnitTestAssertCheckSrc(((size_t)pItem->data) == 2);

	CUtilDLListDestroy(aList);

	return 0;
}
