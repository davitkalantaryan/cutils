//
// file:            main_lhash_test.c
// path:			src/tests/main_lhash_test.c
// created on:		2023 Feb 25
// created by:		Davit Kalantaryan (davit.kalantaryan@desy.de)
//


#include <cinternal/hash/lhash.h>
#include <stdio.h>
#include <assert.h>

int main(void)
{
	const int key1 = 1;
	const int key2 = 2;
	int nNumber;
	CInternalLHashIterator pItem;
	CinternalLHash_t aHash = CInternalLHashCreate(1024);

	if (!aHash) {
		perror("\n");
		return 1;
	}

	CInternalLHashAddDataEvenIfExist(aHash, (void*)2, &key1, sizeof(int));
	CInternalLHashAddDataEvenIfExist(aHash, (void*)4, &key2, sizeof(int));
	assert(CInternalLHashSize(aHash)==2);

	nNumber = 0;
	pItem = CInternalLHashFirstItem(aHash);
	while (pItem) {
		++nNumber;
		pItem = pItem->nextInList;
	}

	assert(nNumber==2);
	
	pItem = CInternalLHashFind(aHash, &key1, sizeof(int));
	assert(pItem);
	assert(((size_t)pItem->data)==2);

	pItem = CInternalLHashFind(aHash, &key2, sizeof(int));
	assert(pItem);
	assert(((size_t)pItem->data) == 4);

	CInternalLHashDestroy(aHash);

	return 0;
}
