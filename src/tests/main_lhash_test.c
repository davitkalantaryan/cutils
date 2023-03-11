//
// file:            main_lhash_test.c
// path:			src/tests/main_lhash_test.c
// created on:		2023 Feb 25
// created by:		Davit Kalantaryan (davit.kalantaryan@desy.de)
//


#include <cinternal/hash/lhash.h>
#include <stdio.h>
#include <assert.h>

#define CINTR_TEST_HASH_DATA1		2
#define CINTR_TEST_HASH_DATA2		4


static void TestHash(CinternalLHash_t a_hash, const void* a_key1, size_t keySize1, const void* a_key2, size_t keySize2);

int main(void)
{
	const int key1 = 1;
	const int key2 = 2;
	CinternalLHash_t aHash;

	aHash = CInternalLHashCreateRawMem(1024);
	if (!aHash) {
		perror("\n");
		return 1;
	}
	CInternalLHashAddDataEvenIfExist(aHash, (void*)CINTR_TEST_HASH_DATA1, &key1, sizeof(int));
	CInternalLHashAddDataEvenIfExist(aHash, (void*)CINTR_TEST_HASH_DATA2, &key2, sizeof(int));
	TestHash(aHash, &key1, sizeof(int), &key2, sizeof(int));
	CInternalLHashDestroy(aHash);


	aHash = CInternalLHashCreateSmlInt(1024);
	if (!aHash) {
		perror("\n");
		return 1;
	}
	CInternalLHashAddDataEvenIfExist(aHash, (void*)CINTR_TEST_HASH_DATA1, CInternalSmallIntHPair(1));
	CInternalLHashAddDataEvenIfExist(aHash, (void*)CINTR_TEST_HASH_DATA2, CInternalSmallIntHPair(2));
	TestHash(aHash, CInternalSmallIntHPair(1), CInternalSmallIntHPair(2));
	CInternalLHashDestroy(aHash);

	return 0;
}


static void TestHash(CinternalLHash_t a_hash, const void* a_key1, size_t a_keySize1, const void* a_key2, size_t a_keySize2)
{
	CInternalLHashIterator pItem;
	int nNumber;

	assert(CInternalLHashSize(a_hash) == 2);

	nNumber = 0;
	pItem = CInternalLHashFirstItem(a_hash);
	while (pItem) {
		++nNumber;
		pItem = pItem->nextInList;
	}

	assert(nNumber == 2);

	pItem = CInternalLHashFind(a_hash, a_key1, a_keySize1);
	assert(pItem);
	assert(((size_t)pItem->data) == CINTR_TEST_HASH_DATA1);

	pItem = CInternalLHashFind(a_hash, a_key2, a_keySize2);
	assert(pItem);
	assert(((size_t)pItem->data) == CINTR_TEST_HASH_DATA2);
}
