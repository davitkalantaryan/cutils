//
// repo:			cutils
// file:            cutil_core_hash_dllhash.c
// path:			src/core/cutils_core_hash_dllhash.c
// created on:		2023 Feb 25
// created by:		Davit Kalantaryan (davit.kalantaryan@desy.de)
//


#include <cutils/hash/dllhash.h>
#define CUTILS_SRC_CORE_CUTILS_CORE_LIST_DLLIST_IMPL_H_NEEDED
#define CInternalDLListAddCreatedIteratorFrontInline1_needed	1
#define	CInternalDLListAddCreatedIteratorFrontInline2_needed	1
#include "cutils_core_list_dllist.impl.h"
#include <string.h>

#define CUTILS_HASH_DEFAULT_NUMBER_OF_BASKETS	4096

static size_t cinternal_hash1_raw_mem(const void* a_pKey, size_t a_unKeySize) CPPUTILS_NOEXCEPT;


CPPUTILS_BEGIN_C

#define CInternalDLLHashItemFromTableIterator(_iter_ptr)	cpputils_container_of(_iter_ptr,const struct SCinternalDLLHashItem,tbl)


struct CPPUTILS_DLL_PRIVATE SCinternalDLLHash {
	TypeCinternalAllocator				allocator;
	TypeCinternalDeallocator			deallocator;
	struct SCinternalDLListIterator		*first,*last;
	size_t								m_size;
	
	struct SCinternalDLListIterator**	ppTable;
	size_t								numberOfBaskets;
	TypeCinternalHasher					hasher;
	TypeCinternalIsMemoriesIdentical	isEq;
	TypeCinternalStoreKey				keyStore;
	TypeCinternalUnstoreKey				keyUnstore;
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


CUTILS_EXPORT CinternalDLLHash_t CInternalDLLHashCreateExAny(size_t a_numberOfBaskets,
	TypeCinternalHasher CPPUTILS_ARG_NN a_hasher, TypeCinternalIsMemoriesIdentical CPPUTILS_ARG_NN a_isEq,
	TypeCinternalStoreKey CPPUTILS_ARG_NN a_keyStore, TypeCinternalUnstoreKey CPPUTILS_ARG_NN a_keyUnstore,
	TypeCinternalAllocator a_allocator, TypeCinternalDeallocator a_deallocator)
{
	CinternalDLLHash_t pRet;
	size_t tableMemorySize;

	a_allocator = a_allocator ? a_allocator : (&malloc);

	pRet = CPPUTILS_STATIC_CAST(CinternalDLLHash_t, (*a_allocator)(sizeof(struct SCinternalDLLHash)));
	if (!pRet) {
		return CPPUTILS_NULL;
	}

	// init the list
	//CInternalDLListInitializeInline(&(pRet->lst), a_allocator, a_deallocator);
	pRet->allocator = a_allocator;
	pRet->deallocator = a_deallocator ? a_deallocator : (&free);
	pRet->last = pRet->first = CPPUTILS_NULL;
	pRet->m_size = 0;

	pRet->numberOfBaskets = a_numberOfBaskets ? a_numberOfBaskets : CUTILS_HASH_DEFAULT_NUMBER_OF_BASKETS;

	tableMemorySize = pRet->numberOfBaskets * sizeof(struct SCinternalDLListIterator*);
	pRet->ppTable = CPPUTILS_STATIC_CAST(struct SCinternalDLListIterator**, (*a_allocator)(tableMemorySize));
	if (!(pRet->ppTable)) {
		(*(pRet->deallocator))(pRet);
		return CPPUTILS_NULL;
	}
	memset(pRet->ppTable, 0, tableMemorySize);

	//pRet->hasher = a_hasher ? a_hasher : (&cinternal_hash1_);
	//pRet->isEq = a_isEq ? a_isEq : (&CinternaldefaultIsMemoriesIdentical);
	pRet->hasher = a_hasher;
	pRet->isEq = a_isEq;

	pRet->keyStore = a_keyStore;
	pRet->keyUnstore = a_keyUnstore;

	return pRet;
}


CUTILS_EXPORT CinternalDLLHash_t CInternalDLLHashCreateExAnyDefRawMem(size_t a_numberOfBaskets,
	TypeCinternalHasher a_hasher, TypeCinternalIsMemoriesIdentical a_isEq,
	TypeCinternalStoreKey a_keyStore, TypeCinternalUnstoreKey a_keyUnstore,
	TypeCinternalAllocator a_allocator, TypeCinternalDeallocator a_deallocator)
{
	return CInternalDLLHashCreateExAny(a_numberOfBaskets,
		a_hasher ? a_hasher : (&cinternal_hash1_raw_mem), a_isEq ? a_isEq :(&CinternalIsMemoriesIdenticalRawMemory),
		a_keyStore ? a_keyStore : (&CinternalStoreKeyRawMemory), a_keyUnstore ? a_keyUnstore :(&CinternalUnstoreKeyRawMemory),
		a_allocator, a_deallocator);
}


CUTILS_EXPORT CinternalDLLHash_t CInternalDLLHashCreateExAnyDefSmlInt(size_t a_numberOfBaskets,
	TypeCinternalHasher a_hasher, TypeCinternalIsMemoriesIdentical a_isEq,
	TypeCinternalStoreKey a_keyStore, TypeCinternalUnstoreKey a_keyUnstore,
	TypeCinternalAllocator a_allocator, TypeCinternalDeallocator a_deallocator)
{
	return CInternalDLLHashCreateExAny(a_numberOfBaskets,
		a_hasher ? a_hasher : (&cinternal_hash1_small_int), a_isEq ? a_isEq : (&CinternalIsMemoriesIdenticalSmallInt),
		a_keyStore ? a_keyStore : (&CinternalStoreKeySmallInt), a_keyUnstore ? a_keyUnstore : (&CinternalUnstoreKeySmallInt),
		a_allocator, a_deallocator);
}


CUTILS_EXPORT CinternalDLLHash_t CInternalDLLHashCreateExRawMem(size_t a_numberOfBaskets, TypeCinternalAllocator a_allocator, TypeCinternalDeallocator a_deallocator)
{
	return CInternalDLLHashCreateExAny(a_numberOfBaskets,
		&cinternal_hash1_raw_mem, &CinternalIsMemoriesIdenticalRawMemory,
		&CinternalStoreKeyRawMemory, &CinternalUnstoreKeyRawMemory,
		a_allocator, a_deallocator);
}


CUTILS_EXPORT CinternalDLLHash_t CInternalDLLHashCreateExSmlInt(size_t a_numberOfBaskets, TypeCinternalAllocator a_allocator, TypeCinternalDeallocator a_deallocator)
{
	return CInternalDLLHashCreateExAny(a_numberOfBaskets,
		&cinternal_hash1_small_int, &CinternalIsMemoriesIdenticalSmallInt,
		&CinternalStoreKeySmallInt, &CinternalUnstoreKeySmallInt,
		a_allocator, a_deallocator);
}


static void CinternalDLListItemExtraCleaner(void* a_container, struct SCinternalDLListIterator* CPPUTILS_ARG_NN a_iter, TypeCinternalDeallocator CPPUTILS_ARG_NN a_remainingDataCleaner)
{
	struct SCinternalDLLHash* pHashTbl = CPPUTILS_STATIC_CAST(struct SCinternalDLLHash*, a_container);
	(*a_remainingDataCleaner)(CInternalDLLHashItemFromDLListIterator(a_iter)->data);
	(*(pHashTbl->keyUnstore))(pHashTbl->deallocator,
		CInternalDLLHashItemFromDLListIterator(a_iter)->key, CInternalDLLHashItemFromDLListIterator(a_iter)->keySize);
}


CUTILS_EXPORT void CInternalDLLHashDestroyEx(CinternalDLLHash_t CPPUTILS_ARG_NN a_hashTbl, TypeCinternalDeallocator a_remainingDataCleaner)
{
	CInternalListCleanInline(a_hashTbl->first, a_hashTbl->deallocator, a_hashTbl, a_remainingDataCleaner, &CinternalDLListItemExtraCleaner);
	(*(a_hashTbl->deallocator))(a_hashTbl->ppTable);
	(*(a_hashTbl->deallocator))(a_hashTbl);
}


CUTILS_EXPORT CinternalDLLHashItem_t CInternalDLLHashAddDataEvenIfExist(CinternalDLLHash_t CPPUTILS_ARG_NN a_hashTbl, const void* a_data, const void* a_key, size_t a_keySize)
{
	const size_t hash = ((*(a_hashTbl->hasher))(a_key, a_keySize)) % (a_hashTbl->numberOfBaskets);
	return CInternalDLLHashAddDataWithKnownHash(a_hashTbl, a_data, a_key, a_keySize, hash);
}


static inline struct SCinternalDLLHashItem* CInternalHashFindItemInline(ConstCinternalDLLHash_t CPPUTILS_ARG_NN a_hashTbl, const void* a_key, size_t a_keySize, size_t* CPPUTILS_ARG_NN a_pHash) {
	struct SCinternalDLListIterator* pItem;
	*a_pHash = ((*(a_hashTbl->hasher))(a_key, a_keySize)) % (a_hashTbl->numberOfBaskets);
	pItem = a_hashTbl->ppTable[*a_pHash];
	while (pItem) {
		if ((*(a_hashTbl->isEq))(CInternalDLLHashItemFromTableIterator(pItem)->key, CInternalDLLHashItemFromTableIterator(pItem)->keySize, a_key, a_keySize)) {
			return CPPUTILS_CONST_CAST(struct SCinternalDLLHashItem* ,CInternalDLLHashItemFromTableIterator(pItem));
		}
		pItem = pItem->next;
	}
	return CPPUTILS_NULL;
}


CUTILS_EXPORT CinternalDLLHashItem_t CInternalDLLHashAddDataIfNotExists(CinternalDLLHash_t CPPUTILS_ARG_NN a_hashTbl, const void* a_data, const void* a_key, size_t a_keySize)
{
	size_t unHash;
	if (CInternalHashFindItemInline(a_hashTbl, a_key, a_keySize,&unHash)) {
		return CPPUTILS_NULL;
	}
	return CInternalDLLHashAddDataWithKnownHash(a_hashTbl, a_data, a_key, a_keySize, unHash);
}



CUTILS_EXPORT CinternalDLLHashItem_t CInternalDLLHashAddDataWithKnownHash(CinternalDLLHash_t CPPUTILS_ARG_NN a_hashTbl, const void* a_data, const void* a_key, size_t a_keySize, size_t a_hash)
{
	struct SCinternalDLLHashItem*const pNewItem = CPPUTILS_STATIC_CAST(struct SCinternalDLLHashItem*, (*(a_hashTbl->allocator))(sizeof(struct SCinternalDLLHashItem)));
	if (!pNewItem) {
		return CPPUTILS_NULL;
	}

	if (!(*(a_hashTbl->keyStore))(a_hashTbl->allocator, &(pNewItem->key), &(pNewItem->keySize), a_key, a_keySize)) {
		(*(a_hashTbl->deallocator))(pNewItem);
		return CPPUTILS_NULL;
	}

	pNewItem->data = CPPUTILS_CONST_CAST(void*, a_data);
	CInternalDLListAddCreatedIteratorFrontInline2(&(a_hashTbl->first), &(a_hashTbl->last), CInternalDLListIteratorFromDLLHashItem(pNewItem));
	CInternalDLListAddCreatedIteratorFrontInline1(&(a_hashTbl->ppTable[a_hash]), &(pNewItem->tbl));

	pNewItem->hash = a_hash;
	++(a_hashTbl->m_size);

	return pNewItem;
}


CUTILS_EXPORT CinternalDLLHashItem_t CInternalDLLHashFindEx(ConstCinternalDLLHash_t CPPUTILS_ARG_NN a_hashTbl, const void* a_key, size_t a_keySize, size_t* CPPUTILS_ARG_NN a_pHash)
{
	return CInternalHashFindItemInline(a_hashTbl, a_key, a_keySize, a_pHash);
}


CUTILS_EXPORT CinternalDLLHashItem_t CInternalDLLHashFind(ConstCinternalDLLHash_t CPPUTILS_ARG_NN a_hashTbl, const void* a_key, size_t a_keySize)
{
	size_t unHash;
	return CInternalHashFindItemInline(a_hashTbl,a_key,a_keySize,&unHash);
}


CUTILS_EXPORT CinternalDLLHashItem_t CInternalDLLHashFirstItem(ConstCinternalDLLHash_t CPPUTILS_ARG_NN a_hashTbl)
{
	return CInternalDLLHashItemFromDLListIterator(a_hashTbl->first);
}


CUTILS_EXPORT CinternalDLLHashItem_t CInternalDLLHashLastItem(ConstCinternalDLLHash_t CPPUTILS_ARG_NN a_hashTbl)
{
	return CInternalDLLHashItemFromDLListIterator(a_hashTbl->last);
}


CUTILS_EXPORT bool CInternalDLLHashRemoveData(CinternalDLLHash_t CPPUTILS_ARG_NN a_hashTbl, const void* a_key, size_t a_keySize)
{
	size_t unHash;
	struct SCinternalDLLHashItem* pIterator = CInternalHashFindItemInline(a_hashTbl, a_key, a_keySize, &unHash);
	if (pIterator) {
		CInternalDLLHashRemoveDataEx(a_hashTbl, pIterator);
		return true;
	}
	return false;
}


CUTILS_EXPORT void CInternalDLLHashRemoveDataEx(CinternalDLLHash_t CPPUTILS_ARG_NN a_hashTbl, CinternalDLLHashItem_t CPPUTILS_ARG_NN a_iter)
{
	//CInternalListRemoveItertaorInline(&(a_hashTbl->ppTable[CInternalDLLHashItemFromListIterator(a_iter)->hash]), &(CInternalDLLHashItemFromListIterator(a_iter)->tbl));
	//CInternalDLListRemoveDataNoFreeInline(&(a_hashTbl->lst), a_iter);
	CInternalListRemoveItertaorInline1(&(a_hashTbl->ppTable[a_iter->hash]), &(a_iter->tbl));
	CInternalListRemoveItertaorInline1(&(a_hashTbl->first), CInternalDLListIteratorFromDLLHashItem(a_iter));

	(*(a_hashTbl->keyUnstore))(a_hashTbl->deallocator, a_iter->key, a_iter->keySize);
	(*(a_hashTbl->deallocator))(CPPUTILS_CONST_CAST(struct SCinternalDLLHashItem*, a_iter));
	--(a_hashTbl->m_size);
}


CUTILS_EXPORT size_t CInternalDLLHashSize(ConstCinternalDLLHash_t CPPUTILS_ARG_NN a_hashTbl)
{
	return a_hashTbl->m_size;
}


CUTILS_EXPORT void* CInternalLHashGetDefaultFunctions(int a_function)
{
	switch (a_function) {
	case CUTILS_HASH_DEFAULT_FUNC_MMEM_HASH:
		return (void*)(&cinternal_hash1_raw_mem);
	case CUTILS_HASH_DEFAULT_FUNC_SML_INT_HASH:
		return (void*)(&cinternal_hash1_small_int);
	default:
		return CPPUTILS_NULL;
	}  //  switch (a_function) {
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
