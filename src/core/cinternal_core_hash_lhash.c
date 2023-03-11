//
// file:            cinternal_core_hash_lhash.c
// path:			src/core/cinternal_core_hash_lhash.c
// created on:		2023 Feb 25
// created by:		Davit Kalantaryan (davit.kalantaryan@desy.de)
//


#include <cinternal/hash/lhash.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#ifdef _MSC_VER

#elif defined(__GNUC__) 

#pragma GCC diagnostic ignored "-Wattributes"

#endif

#define CINTERNAL_HASH_DEFAULT_NUMBER_OF_BASKETS	4096

static size_t cinternal_hash1_raw_mem(const void* a_pKey, size_t a_unKeySize) CPPUTILS_NOEXCEPT;


CPPUTILS_BEGIN_C

static void CinternalDefaultDataCleaner(void* a_pData) {
	CPPUTILS_STATIC_CAST(void, a_pData);
}


struct CPPUTILS_DLL_PRIVATE SCinternalLHash {
	struct SCinternalLHashItem**		ppTable;
	size_t								numberOfBaskets;
	TypeCinternalHasher					hasher;
	TypeCinternalAllocator				allocator;
	TypeCinternalDeallocator			deallocator;
	TypeCinternalIsMemoriesIdentical	isEq;
	TypeCinternalStoreKey				keyStore;
	TypeCinternalUnstoreKey				keyUnstore;
	struct SCinternalLHashItem*			first;
	size_t								m_size;
	size_t								reserved01;
};


static size_t cinternal_hash1_small_int(const void* a_key, size_t a_keySize) CPPUTILS_NOEXCEPT
{
	CPPUTILS_STATIC_CAST(void, a_keySize);
	return CPPUTILS_REINTERPRET_CAST(size_t, a_key);
}


static bool CinternalIsMemoriesIdenticalRawMemory(const void* a_key1, size_t a_keySize1, const void* a_key2, size_t a_keySize2) CPPUTILS_NOEXCEPT
{
	return (a_keySize1 == a_keySize2) && (memcmp(a_key1, a_key2, a_keySize1) == 0);
}


static bool CinternalStoreKeyRawMemory(TypeCinternalAllocator a_allocator, void** a_pKeyStore, size_t* a_pKeySizeStore, const void* a_key, size_t a_keySize) CPPUTILS_NOEXCEPT
{
	*a_pKeyStore = (*a_allocator)(a_keySize);
	if (!(*a_pKeyStore)) {
		return false;
	}
	memcpy(*a_pKeyStore, a_key, a_keySize);
	*a_pKeySizeStore = a_keySize;
	return true;
}


static void CinternalUnstoreKeyRawMemory(TypeCinternalDeallocator a_deallocator, void* a_key, size_t a_keySize) CPPUTILS_NOEXCEPT
{
	CPPUTILS_STATIC_CAST(void, a_keySize);
	(*a_deallocator)(a_key);
}


static bool CinternalIsMemoriesIdenticalSmallInt(const void* a_key1, size_t a_keySize1, const void* a_key2, size_t a_keySize2) CPPUTILS_NOEXCEPT
{
	CPPUTILS_STATIC_CAST(void, a_keySize1);
	CPPUTILS_STATIC_CAST(void, a_keySize2);
	return (a_key1 == a_key2);
}


static bool CinternalStoreKeySmallInt(TypeCinternalAllocator a_allocator, void** a_pKeyStore, size_t* a_pKeySizeStore, const void* a_key, size_t a_keySize) CPPUTILS_NOEXCEPT
{
	CPPUTILS_STATIC_CAST(void, a_allocator);
	CPPUTILS_STATIC_CAST(void, a_keySize);
	CPPUTILS_STATIC_CAST(void, a_pKeySizeStore);
	*a_pKeyStore = CPPUTILS_CONST_CAST(void*,a_key);
	return true;
}


static void CinternalUnstoreKeySmallInt(TypeCinternalDeallocator a_deallocator, void* a_key, size_t a_keySize) CPPUTILS_NOEXCEPT
{
	CPPUTILS_STATIC_CAST(void, a_deallocator);
	CPPUTILS_STATIC_CAST(void, a_key);
	CPPUTILS_STATIC_CAST(void, a_keySize);
}


CINTERNAL_EXPORT CinternalLHash_t CInternalLHashCreateExAny(size_t a_numberOfBaskets,
	TypeCinternalHasher CPPUTILS_ARG_NONULL a_hasher, TypeCinternalIsMemoriesIdentical CPPUTILS_ARG_NONULL a_isEq,
	TypeCinternalStoreKey CPPUTILS_ARG_NONULL a_keyStore, TypeCinternalUnstoreKey CPPUTILS_ARG_NONULL a_keyUnstore,
	TypeCinternalAllocator a_allocator, TypeCinternalDeallocator a_deallocator)
{
	CinternalLHash_t pRet;
	size_t tableMemorySize;

	a_allocator = a_allocator ? a_allocator : (&malloc);

	pRet = CPPUTILS_STATIC_CAST(CinternalLHash_t, (*a_allocator)(sizeof(struct SCinternalLHash)));
	if (!pRet) {
		return CPPUTILS_NULL;
	}

	pRet->allocator = a_allocator;
	pRet->deallocator = a_deallocator ? a_deallocator : (&free);
	pRet->numberOfBaskets = a_numberOfBaskets ? a_numberOfBaskets : CINTERNAL_HASH_DEFAULT_NUMBER_OF_BASKETS;

	tableMemorySize = pRet->numberOfBaskets * sizeof(struct SCinternalLHashItem*);
	pRet->ppTable = CPPUTILS_STATIC_CAST(struct SCinternalLHashItem**, (*a_allocator)(tableMemorySize));
	if (!(pRet->ppTable)) {
		(*(pRet->deallocator))(pRet);
		return CPPUTILS_NULL;
	}
	memset(pRet->ppTable, 0, tableMemorySize);

	pRet->first = CPPUTILS_NULL;
	pRet->m_size = 0;

	//pRet->hasher = a_hasher ? a_hasher : (&cinternal_hash1_);
	//pRet->isEq = a_isEq ? a_isEq : (&CinternaldefaultIsMemoriesIdentical);
	pRet->hasher = a_hasher;
	pRet->isEq = a_isEq;

	pRet->keyStore = a_keyStore;
	pRet->keyUnstore = a_keyUnstore;

	return pRet;
}


CINTERNAL_EXPORT CinternalLHash_t CInternalLHashCreateExAnyDefRawMem(size_t a_numberOfBaskets,
	TypeCinternalHasher a_hasher, TypeCinternalIsMemoriesIdentical a_isEq,
	TypeCinternalStoreKey a_keyStore, TypeCinternalUnstoreKey a_keyUnstore,
	TypeCinternalAllocator a_allocator, TypeCinternalDeallocator a_deallocator)
{
#ifdef __cplusplus
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable:5039)
#endif
#endif
	return CInternalLHashCreateExAny(a_numberOfBaskets,
		a_hasher ? a_hasher : (&cinternal_hash1_raw_mem), a_isEq ? a_isEq :(&CinternalIsMemoriesIdenticalRawMemory),
		a_keyStore ? a_keyStore : (&CinternalStoreKeyRawMemory), a_keyUnstore ? a_keyUnstore :(&CinternalUnstoreKeyRawMemory),
		a_allocator, a_deallocator);
}


CINTERNAL_EXPORT CinternalLHash_t CInternalLHashCreateExAnyDefSmlInt(size_t a_numberOfBaskets,
	TypeCinternalHasher a_hasher, TypeCinternalIsMemoriesIdentical a_isEq,
	TypeCinternalStoreKey a_keyStore, TypeCinternalUnstoreKey a_keyUnstore,
	TypeCinternalAllocator a_allocator, TypeCinternalDeallocator a_deallocator)
{
	return CInternalLHashCreateExAny(a_numberOfBaskets,
		a_hasher ? a_hasher : (&cinternal_hash1_small_int), a_isEq ? a_isEq : (&CinternalIsMemoriesIdenticalSmallInt),
		a_keyStore ? a_keyStore : (&CinternalStoreKeySmallInt), a_keyUnstore ? a_keyUnstore : (&CinternalUnstoreKeySmallInt),
		a_allocator, a_deallocator);
}


CINTERNAL_EXPORT CinternalLHash_t CInternalLHashCreateExRawMem(size_t a_numberOfBaskets, TypeCinternalAllocator a_allocator, TypeCinternalDeallocator a_deallocator)
{
	return CInternalLHashCreateExAny(a_numberOfBaskets,
		&cinternal_hash1_raw_mem, &CinternalIsMemoriesIdenticalRawMemory,
		&CinternalStoreKeyRawMemory, &CinternalUnstoreKeyRawMemory,
		a_allocator, a_deallocator);
}


CINTERNAL_EXPORT CinternalLHash_t CInternalLHashCreateExSmlInt(size_t a_numberOfBaskets, TypeCinternalAllocator a_allocator, TypeCinternalDeallocator a_deallocator)
{
	return CInternalLHashCreateExAny(a_numberOfBaskets,
		&cinternal_hash1_small_int, &CinternalIsMemoriesIdenticalSmallInt,
		&CinternalStoreKeySmallInt, &CinternalUnstoreKeySmallInt,
		a_allocator, a_deallocator);
#ifdef __cplusplus
#ifdef _MSC_VER
#pragma warning (pop)
#endif
#endif
}


CINTERNAL_EXPORT void CInternalLHashDestroyEx(CinternalLHash_t a_hashTbl, TypeCinternalDeallocator a_remainingDataCleaner)
{
	struct SCinternalLHashItem *pItemTmp, *pItem = a_hashTbl->first;

	a_remainingDataCleaner = a_remainingDataCleaner ? a_remainingDataCleaner : (&CinternalDefaultDataCleaner); // if null, then data should not be cleaned

	while (pItem) {
		pItemTmp = pItem->nextInList;
		(*a_remainingDataCleaner)(pItem->data);
		(*(a_hashTbl->keyUnstore))(a_hashTbl->deallocator, pItem->key, pItem->keySize);
		(*(a_hashTbl->deallocator))(pItem);
		pItem = pItemTmp;
	}

	(*(a_hashTbl->deallocator))(a_hashTbl->ppTable);
	(*(a_hashTbl->deallocator))(a_hashTbl);
}


CINTERNAL_EXPORT CInternalLHashIterator CInternalLHashAddDataEvenIfExist(CinternalLHash_t a_hashTbl, const void* a_data, const void* a_key, size_t a_keySize)
{
	const size_t hash = ((*(a_hashTbl->hasher))(a_key, a_keySize)) % (a_hashTbl->numberOfBaskets);
	return CInternalLHashAddDataWithKnownHash(a_hashTbl,a_data,a_key, a_keySize, hash);
}


CINTERNAL_EXPORT CInternalLHashIterator CInternalLHashAddDataIfNotExists(CinternalLHash_t a_hashTbl, const void* a_data, const void* a_key, size_t a_keySize)
{
	const size_t hash = ((*(a_hashTbl->hasher))(a_key, a_keySize)) % (a_hashTbl->numberOfBaskets);
	struct SCinternalLHashItem * pItem = a_hashTbl->ppTable[hash];

	while (pItem) {
		if( (*(a_hashTbl->isEq))(pItem->key,pItem->keySize, a_key, a_keySize) ){
			return CPPUTILS_NULL;
		}
		pItem = pItem->nextInTbl;
	}

	return CInternalLHashAddDataWithKnownHash(a_hashTbl, a_data, a_key, a_keySize, hash);
}


CINTERNAL_EXPORT CInternalLHashIterator CInternalLHashAddDataWithKnownHash(CinternalLHash_t a_hashTbl, const void* a_data, const void* a_key, size_t a_keySize, size_t a_hash)
{
	struct SCinternalLHashItem* pItem = CPPUTILS_STATIC_CAST(struct SCinternalLHashItem*, (*(a_hashTbl->allocator))(sizeof(struct SCinternalLHashItem)));
	if (!pItem) {
		return CPPUTILS_NULL;
	}

	//pItem->key = (*(a_hashTbl->allocator))(a_keySize);
	//if (!(pItem->key)) {
	//	(*(a_hashTbl->deallocator))(pItem);
	//	return CPPUTILS_NULL;
	//}
	//memcpy(pItem->key, a_key, a_keySize);
	//pItem->keySize = a_keySize;
	if (!(*(a_hashTbl->keyStore))(a_hashTbl->allocator, &(pItem->key), &(pItem->keySize), a_key, a_keySize)) {
		(*(a_hashTbl->deallocator))(pItem);
		return CPPUTILS_NULL;
	}

	pItem->prevIList = CPPUTILS_NULL;
	pItem->prevInTbl = CPPUTILS_NULL;

	pItem->hash = a_hash;
	pItem->data = CPPUTILS_CONST_CAST(void*, a_data);

	pItem->nextInList = a_hashTbl->first;
	if (a_hashTbl->first) {
		a_hashTbl->first->prevIList = pItem;
	}
	a_hashTbl->first = pItem;

	pItem->nextInTbl = a_hashTbl->ppTable[a_hash];
	if (a_hashTbl->ppTable[a_hash]) {
		a_hashTbl->ppTable[a_hash]->prevInTbl = pItem;
	}
	a_hashTbl->ppTable[a_hash] = pItem;
	++(a_hashTbl->m_size);

	return pItem;
}


CINTERNAL_EXPORT CInternalLHashIterator CInternalLHashFindEx(ConstCinternalLHash_t a_hashTbl, const void* a_key, size_t a_keySize, size_t* CPPUTILS_ARG_NO_NULL a_pHash)
{
	struct SCinternalLHashItem* pItem;
	
	*a_pHash = ((*(a_hashTbl->hasher))(a_key, a_keySize)) % (a_hashTbl->numberOfBaskets);
	pItem = a_hashTbl->ppTable[*a_pHash];

	while (pItem) {
		if ((*(a_hashTbl->isEq))(pItem->key, pItem->keySize, a_key, a_keySize)) {
			return pItem;
		}
		pItem = pItem->nextInTbl;
	}

	return CPPUTILS_NULL;
}


CINTERNAL_EXPORT CInternalLHashIterator CInternalLHashFind(ConstCinternalLHash_t a_hashTbl, const void* a_key, size_t a_keySize)
{
	size_t unHash;
	return CInternalLHashFindEx(a_hashTbl,a_key,a_keySize,&unHash);
}


CINTERNAL_EXPORT CInternalLHashIterator CInternalLHashFirstItem(ConstCinternalLHash_t a_hashTbl)
{
	return a_hashTbl->first;
}


CINTERNAL_EXPORT bool CInternalLHashRemoveData(CinternalLHash_t a_hashTbl, const void* a_key, size_t a_keySize)
{
	CInternalLHashIterator pIterator = CInternalLHashFind(a_hashTbl, a_key, a_keySize);
	if (pIterator) {
		CInternalLHashRemoveDataEx(a_hashTbl, pIterator);
		return true;
	}
	return false;
}


CINTERNAL_EXPORT void CInternalLHashRemoveDataEx(CinternalLHash_t a_hashTbl, CInternalLHashIterator a_iterator)
{
	if (a_iterator->prevInTbl) {
		a_iterator->prevInTbl->nextInTbl = a_iterator->nextInTbl;
	}

	if (a_iterator->nextInTbl) {
		a_iterator->nextInTbl->prevInTbl = a_iterator->prevInTbl;
	}

	if (a_iterator == a_hashTbl->ppTable[a_iterator->hash]) {
		a_hashTbl->ppTable[a_iterator->hash] = a_iterator->nextInTbl;
	}

	//
	if (a_iterator->prevIList) {
		a_iterator->prevIList->nextInList = a_iterator->nextInList;
	}

	if (a_iterator->nextInList) {
		a_iterator->nextInList->prevIList = a_iterator->prevIList;
	}

	if (a_iterator == a_hashTbl->first) {
		a_hashTbl->first = a_iterator->nextInList;
	}

	--(a_hashTbl->m_size);
	//(*(a_hashTbl->deallocator))(a_iterator->key);
	(*(a_hashTbl->keyUnstore))(a_hashTbl->deallocator, a_iterator->key, a_iterator->keySize);
	(*(a_hashTbl->deallocator))(CPPUTILS_CONST_CAST(struct SCinternalLHashItem*, a_iterator));
}


CINTERNAL_EXPORT size_t CInternalLHashSize(ConstCinternalLHash_t a_hashTbl)
{
	return a_hashTbl->m_size;
}


CPPUTILS_END_C




/* The mixing step */
#define mix2(a,b,c) \
{ \
  a=a-b;  a=a-c;  a=a^(c>>13); \
  b=b-c;  b=b-a;  b=b^(a<<8);  \
  c=c-a;  c=c-b;  c=c^(b>>13); \
  a=a-b;  a=a-c;  a=a^(c>>12); \
  b=b-c;  b=b-a;  b=b^(a<<16); \
  c=c-a;  c=c-b;  c=c^(b>>5);  \
  a=a-b;  a=a-c;  a=a^(c>>3);  \
  b=b-c;  b=b-a;  b=b^(a<<10); \
  c=c-a;  c=c-b;  c=c^(b>>15); \
}

static size_t cinternal_hash1_raw_mem(const void* a_pKey, size_t a_unKeySize) CPPUTILS_NOEXCEPT
{
	const uint32_t unKeySize = CPPUTILS_STATIC_CAST(uint32_t, a_unKeySize);
	CPPUTILS_REGISTER const uint8_t* k = CPPUTILS_STATIC_CAST(const uint8_t*, a_pKey);
	CPPUTILS_REGISTER uint32_t a, b, c;  /* the internal state */

	uint32_t          len;    /* how many key bytes still need mixing */

	/* Set up the internal state */
	len = unKeySize;
	a = b = 0x9e3779b9;  /* the golden ratio; an arbitrary value */
	c = 13;         /* variable initialization of internal state */

	/*---------------------------------------- handle most of the key */
	while (len >= 12) {
		a = a + (k[0] + (CPPUTILS_STATIC_CAST(uint32_t, k[1]) << 8) + (CPPUTILS_STATIC_CAST(uint32_t, k[2]) << 16) + (CPPUTILS_STATIC_CAST(uint32_t, k[3]) << 24));
		b = b + (k[4] + (CPPUTILS_STATIC_CAST(uint32_t, k[5]) << 8) + (CPPUTILS_STATIC_CAST(uint32_t, k[6]) << 16) + (CPPUTILS_STATIC_CAST(uint32_t, k[7]) << 24));
		c = c + (k[8] + (CPPUTILS_STATIC_CAST(uint32_t, k[9]) << 8) + (CPPUTILS_STATIC_CAST(uint32_t, k[10]) << 16) + (CPPUTILS_STATIC_CAST(uint32_t, k[11]) << 24));
		mix2(a, b, c);
		k = k + 12; len = len - 12;
	}

	/*------------------------------------- handle the last 11 bytes */
	c = c + unKeySize;

	/* all the case statements fall through */
	switch (len) {
	case 11: c = c + (CPPUTILS_STATIC_CAST(uint32_t, k[10]) << 24); CPPUTILS_FALLTHROUGH
	case 10: c = c + (CPPUTILS_STATIC_CAST(uint32_t, k[9]) << 16); CPPUTILS_FALLTHROUGH
	case 9: c = c + (CPPUTILS_STATIC_CAST(uint32_t, k[8]) << 8); CPPUTILS_FALLTHROUGH

		/* the first byte of c is reserved for the length */
	case 8: b = b + (CPPUTILS_STATIC_CAST(uint32_t, k[7]) << 24); CPPUTILS_FALLTHROUGH
	case 7: b = b + (CPPUTILS_STATIC_CAST(uint32_t, k[6]) << 16); CPPUTILS_FALLTHROUGH
	case 6: b = b + (CPPUTILS_STATIC_CAST(uint32_t, k[5]) << 8); CPPUTILS_FALLTHROUGH
	case 5: b = b + k[4]; CPPUTILS_FALLTHROUGH
	case 4: a = a + (CPPUTILS_STATIC_CAST(uint32_t, k[3]) << 24); CPPUTILS_FALLTHROUGH
	case 3: a = a + (CPPUTILS_STATIC_CAST(uint32_t, k[2]) << 16); CPPUTILS_FALLTHROUGH
	case 2: a = a + (CPPUTILS_STATIC_CAST(uint32_t, k[1]) << 8); CPPUTILS_FALLTHROUGH
	case 1: a = a + k[0];
		/* case 0: nothing left to add */
	}
	mix2(a, b, c);
	/*-------------------------------------------- report the result */

	return CPPUTILS_STATIC_CAST(size_t, c);
}
