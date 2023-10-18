//
// repo:			cutils
// file:            main_lhash_test.c
// path:			src/tests/main_lhash_test.c
// created on:		2023 Feb 25
// created by:		Davit Kalantaryan (davit.kalantaryan@desy.de)
//


#include <cutils/hash/dllhash.h>
#include <cinternal/unit_test_only_checks.h>
#include <stdio.h>

#define CINTR_TEST_HASH_DATA1		2
#define CINTR_TEST_HASH_DATA2		4


static void TestHash(CutilDLLHash_t a_hash, const void* a_key1, size_t keySize1, const void* a_key2, size_t keySize2);

int main(void)
{
	const int key1 = 1;
	const int key2 = 2;
	CutilDLLHash_t aHash;
	CutilDLLHashItem_t pItem;

	aHash = CUtilDLLHashCreateRawMem(1024);
	if (!aHash) {
		perror("\n");
		return 1;
	}

	CUtilDLLHashAddDataEvenIfExist(aHash, (void*)CINTR_TEST_HASH_DATA1, &key1, sizeof(int));
	pItem = CUtilDLLHashFind(aHash, &key1, sizeof(int));
	CinternalUnitTestAssertCheckSrc(pItem);
	CUtilDLLHashRemoveDataEx(aHash, pItem);

	CUtilDLLHashAddDataEvenIfExist(aHash, (void*)CINTR_TEST_HASH_DATA1, &key1, sizeof(int));
	CUtilDLLHashAddDataEvenIfExist(aHash, (void*)CINTR_TEST_HASH_DATA2, &key2, sizeof(int));
	TestHash(aHash, &key1, sizeof(int), &key2, sizeof(int));
	CUtilDLLHashDestroy(aHash);


	aHash = CUtilDLLHashCreateSmlInt(1024);
	if (!aHash) {
		perror("\n");
		return 1;
	}
	CUtilDLLHashAddDataEvenIfExistSmlInt(aHash, (void*)CINTR_TEST_HASH_DATA1, 1);
	CUtilDLLHashAddDataEvenIfExistSmlInt(aHash, (void*)CINTR_TEST_HASH_DATA2, 2);
	TestHash(aHash, CInternalSmallIntHPairFn(1), CInternalSmallIntHPairFn(2));
	CUtilDLLHashDestroy(aHash);

	return 0;
}


static void TestHash(CutilDLLHash_t a_hash, const void* a_key1, size_t a_keySize1, const void* a_key2, size_t a_keySize2)
{
	CutilDLLHashItem_t pItem;
	int nNumber;

	CinternalUnitTestAssertCheckSrc(CUtilDLLHashSize(a_hash) == 2);

	nNumber = 0;
	pItem = CUtilDLLHashFirstItem(a_hash);
	while (pItem) {
		++nNumber;
		pItem = CUtilDLLHashItemFromDLListIterator(CUtilDLListIteratorFromDLLHashItem(pItem)->next);
	}

	CinternalUnitTestAssertCheckSrc(nNumber == 2);

	pItem = CUtilDLLHashFind(a_hash, a_key1, a_keySize1);
	CinternalUnitTestAssertCheckSrc(pItem);
	CinternalUnitTestAssertCheckSrc(((size_t)(pItem->data)) == CINTR_TEST_HASH_DATA1);

	pItem = CUtilDLLHashFind(a_hash, a_key2, a_keySize2);
	CinternalUnitTestAssertCheckSrc(pItem);
	CinternalUnitTestAssertCheckSrc(((size_t)(pItem->data)) == CINTR_TEST_HASH_DATA2);
}
