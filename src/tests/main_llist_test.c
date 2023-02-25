//
// file:            main_llist_test.c
// path:			src/tests/main_llist_test.c
// created on:		2023 Feb 25
// created by:		Davit Kalantaryan (davit.kalantaryan@desy.de)
//


#include <cinternal/list/llist.h>
#include <stdio.h>
#include <assert.h>

int main(void)
{
	int nNumber;
	CInternalLListIterator pItem;
	CinternalLList_t aList = CInternalLListCreate();

	if (!aList) {
		perror("\n");
		return 1;
	}

	CInternalLListAddDataToFront(aList, (void*)1);
	CInternalLListAddDataToFront(aList, (void*)2);
	CInternalLListAddDataToFront(aList, (void*)3);
	assert(CInternalLListSize(aList) == 3);

	nNumber = 0;
	pItem = CInternalLListFirstItem(aList);
	while (pItem) {
		++nNumber;
		pItem = pItem->nextInList;
	}

	assert(nNumber==3);
	
	pItem = CInternalLListFirstItem(aList);
	assert(pItem);
	assert(((size_t)pItem->data)==3);

	pItem = pItem->nextInList;
	assert(pItem);
	assert(((size_t)pItem->data) == 2);

	CInternalLListDestroy(aList);

	return 0;
}
