//
// repo:			cutils
// file:            main_lhash_test.c
// path:			src/tests/main_lhash_test.c
// created on:		2023 Feb 25
// created by:		Davit Kalantaryan (davit.kalantaryan@desy.de)
//


#include <cutils/hash/dllhash.h>
#include <cinternal/unit_test.h>
#include <stdio.h>

#define CINTR_TEST_HASH_DATA1		2
#define CINTR_TEST_HASH_DATA2		4


static void TestHash(CinternalDLLHash_t a_hash, const void* a_key1, size_t keySize1, const void* a_key2, size_t keySize2);

int main(void)
{
	const int key1 = 1;
	const int key2 = 2;
	CinternalDLLHash_t aHash;
	CinternalDLLHashItem_t pItem;

	aHash = CInternalDLLHashCreateRawMem(1024);
	if (!aHash) {
		perror("\n");
		return 1;
	}

	CInternalDLLHashAddDataEvenIfExist(aHash, (void*)CINTR_TEST_HASH_DATA1, &key1, sizeof(int));
	pItem = CInternalDLLHashFind(aHash, &key1, sizeof(int));
	CinternalUnitTestAssertCheck(pItem);
	CInternalDLLHashRemoveDataEx(aHash, pItem);

	CInternalDLLHashAddDataEvenIfExist(aHash, (void*)CINTR_TEST_HASH_DATA1, &key1, sizeof(int));
	CInternalDLLHashAddDataEvenIfExist(aHash, (void*)CINTR_TEST_HASH_DATA2, &key2, sizeof(int));
	TestHash(aHash, &key1, sizeof(int), &key2, sizeof(int));
	CInternalDLLHashDestroy(aHash);


	aHash = CInternalDLLHashCreateSmlInt(1024);
	if (!aHash) {
		perror("\n");
		return 1;
	}
	CInternalDLLHashAddDataEvenIfExistSmlInt(aHash, (void*)CINTR_TEST_HASH_DATA1, 1);
	CInternalDLLHashAddDataEvenIfExistSmlInt(aHash, (void*)CINTR_TEST_HASH_DATA2, 2);
	TestHash(aHash, CInternalSmallIntHPairFn(1), CInternalSmallIntHPairFn(2));
	CInternalDLLHashDestroy(aHash);

	return 0;
}


static void TestHash(CinternalDLLHash_t a_hash, const void* a_key1, size_t a_keySize1, const void* a_key2, size_t a_keySize2)
{
	CinternalDLLHashItem_t pItem;
	int nNumber;

	CinternalUnitTestAssertCheck(CInternalDLLHashSize(a_hash) == 2);

	nNumber = 0;
	pItem = CInternalDLLHashFirstItem(a_hash);
	while (pItem) {
		++nNumber;
		pItem = CInternalDLLHashItemFromDLListIterator(CInternalDLListIteratorFromDLLHashItem(pItem)->next);
	}

	CinternalUnitTestAssertCheck(nNumber == 2);

	pItem = CInternalDLLHashFind(a_hash, a_key1, a_keySize1);
	CinternalUnitTestAssertCheck(pItem);
	CinternalUnitTestAssertCheck(((size_t)(pItem->data)) == CINTR_TEST_HASH_DATA1);

	pItem = CInternalDLLHashFind(a_hash, a_key2, a_keySize2);
	CinternalUnitTestAssertCheck(pItem);
	CinternalUnitTestAssertCheck(((size_t)(pItem->data)) == CINTR_TEST_HASH_DATA2);
}
