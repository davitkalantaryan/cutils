//
// repo:			cutils
// file:            cutil_core_hash_dllhash.c
// path:			src/core/cutils_core_hash_dllhash.c
// created on:		2023 Feb 25
// created by:		Davit Kalantaryan (davit.kalantaryan@desy.de)
//


#include <cutils/hash/dllhash.h>
#define CUTILS_SRC_CORE_CUTILS_CORE_LIST_DLLIST_IMPL_H_NEEDED
#define CUtilDLListAddCreatedIteratorFrontInline1_needed	1
#define	CUtilDLListAddCreatedIteratorFrontInline2_needed	1
#include "cutils_core_list_dllist.impl.h"
#define cinternal_hash1_raw_mem_inline_needed			    1
#include <cinternal/hash_functions.h>
#include <cinternal/wrapper.h>
#include <cinternal/disable_compiler_warnings.h>
#include <string.h>
#include <cinternal/undisable_compiler_warnings.h>

#define CUTILS_HASH_DEFAULT_NUMBER_OF_BASKETS	4096


CPPUTILS_BEGIN_C

#define CUtilDLLHashItemFromTableIterator(_iter_ptr)	cpputils_container_of(_iter_ptr,const struct SCutilDLLHashItem,tbl)


struct CPPUTILS_DLL_PRIVATE SCutilDLLHash {
	TypeCinternalAllocator				allocator;
	TypeCinternalDeallocator			deallocator;
	struct SCutilDLListIterator		*first,*last;
	size_t								m_size;
	
	struct SCutilDLListIterator**	ppTable;
	size_t								numberOfBaskets;
	TypeCinternalHasher					hasher;
	TypeCinternalIsMemoriesIdentical	isEq;
	TypeCinternalStoreKey				keyStore;
	TypeCinternalUnstoreKey				keyUnstore;
};

static bool CinternalIsMemoriesIdenticalRawMemory(const void* a_key1, size_t a_keySize1, const void* a_key2, size_t a_keySize2) CPPUTILS_NOEXCEPT;
static bool CinternalStoreKeyRawMemory(TypeCinternalAllocator a_allocator, void** a_pKeyStore, size_t* a_pKeySizeStore, const void* a_key, size_t a_keySize) CPPUTILS_NOEXCEPT;
static void CinternalUnstoreKeyRawMemory(TypeCinternalDeallocator a_deallocator, void* a_key, size_t a_keySize) CPPUTILS_NOEXCEPT;
static size_t cinternal_hash1_small_int(const void* a_key, size_t a_keySize) CPPUTILS_NOEXCEPT;
static bool CinternalIsMemoriesIdenticalSmallInt(const void* a_key1, size_t a_keySize1, const void* a_key2, size_t a_keySize2) CPPUTILS_NOEXCEPT;
static bool CinternalStoreKeySmallInt(TypeCinternalAllocator a_allocator, void** a_pKeyStore, size_t* a_pKeySizeStore, const void* a_key, size_t a_keySize) CPPUTILS_NOEXCEPT;
static void CinternalUnstoreKeySmallInt(TypeCinternalDeallocator a_deallocator, void* a_key, size_t a_keySize) CPPUTILS_NOEXCEPT;


CUTILS_EXPORT CutilDLLHash_t CUtilDLLHashCreateExAny(size_t a_numberOfBaskets,
	TypeCinternalHasher CPPUTILS_ARG_NN a_hasher, TypeCinternalIsMemoriesIdentical CPPUTILS_ARG_NN a_isEq,
	TypeCinternalStoreKey CPPUTILS_ARG_NN a_keyStore, TypeCinternalUnstoreKey CPPUTILS_ARG_NN a_keyUnstore,
	TypeCinternalAllocator a_allocator, TypeCinternalDeallocator a_deallocator)
{
	CutilDLLHash_t pRet;
	size_t tableMemorySize;

	a_allocator = a_allocator ? a_allocator : (&malloc);

	pRet = CPPUTILS_STATIC_CAST(CutilDLLHash_t, (*a_allocator)(sizeof(struct SCutilDLLHash)));
	if (!pRet) {
		return CPPUTILS_NULL;
	}

	// init the list
	//CUtilDLListInitializeInline(&(pRet->lst), a_allocator, a_deallocator);
	pRet->allocator = a_allocator;
	pRet->deallocator = a_deallocator ? a_deallocator : (&free);
	pRet->last = pRet->first = CPPUTILS_NULL;
	pRet->m_size = 0;

	pRet->numberOfBaskets = a_numberOfBaskets ? a_numberOfBaskets : CUTILS_HASH_DEFAULT_NUMBER_OF_BASKETS;

	tableMemorySize = pRet->numberOfBaskets * sizeof(struct SCutilDLListIterator*);
	pRet->ppTable = CPPUTILS_STATIC_CAST(struct SCutilDLListIterator**, (*a_allocator)(tableMemorySize));
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


CUTILS_EXPORT CutilDLLHash_t CUtilDLLHashCreateExAnyDefRawMem(size_t a_numberOfBaskets,
	TypeCinternalHasher a_hasher, TypeCinternalIsMemoriesIdentical a_isEq,
	TypeCinternalStoreKey a_keyStore, TypeCinternalUnstoreKey a_keyUnstore,
	TypeCinternalAllocator a_allocator, TypeCinternalDeallocator a_deallocator)
{
	return CUtilDLLHashCreateExAny(a_numberOfBaskets,
		a_hasher ? a_hasher : (&cinternal_hash1_raw_mem_inline), a_isEq ? a_isEq :(&CinternalIsMemoriesIdenticalRawMemory),
		a_keyStore ? a_keyStore : (&CinternalStoreKeyRawMemory), a_keyUnstore ? a_keyUnstore :(&CinternalUnstoreKeyRawMemory),
		a_allocator, a_deallocator);
}


CUTILS_EXPORT CutilDLLHash_t CUtilDLLHashCreateExAnyDefSmlInt(size_t a_numberOfBaskets,
	TypeCinternalHasher a_hasher, TypeCinternalIsMemoriesIdentical a_isEq,
	TypeCinternalStoreKey a_keyStore, TypeCinternalUnstoreKey a_keyUnstore,
	TypeCinternalAllocator a_allocator, TypeCinternalDeallocator a_deallocator)
{
	return CUtilDLLHashCreateExAny(a_numberOfBaskets,
		a_hasher ? a_hasher : (&cinternal_hash1_small_int), a_isEq ? a_isEq : (&CinternalIsMemoriesIdenticalSmallInt),
		a_keyStore ? a_keyStore : (&CinternalStoreKeySmallInt), a_keyUnstore ? a_keyUnstore : (&CinternalUnstoreKeySmallInt),
		a_allocator, a_deallocator);
}


CUTILS_EXPORT CutilDLLHash_t CUtilDLLHashCreateExRawMem(size_t a_numberOfBaskets, TypeCinternalAllocator a_allocator, TypeCinternalDeallocator a_deallocator)
{
	return CUtilDLLHashCreateExAny(a_numberOfBaskets,
		&cinternal_hash1_raw_mem_inline, &CinternalIsMemoriesIdenticalRawMemory,
		&CinternalStoreKeyRawMemory, &CinternalUnstoreKeyRawMemory,
		a_allocator, a_deallocator);
}


CUTILS_EXPORT CutilDLLHash_t CUtilDLLHashCreateExSmlInt(size_t a_numberOfBaskets, TypeCinternalAllocator a_allocator, TypeCinternalDeallocator a_deallocator)
{
	return CUtilDLLHashCreateExAny(a_numberOfBaskets,
		&cinternal_hash1_small_int, &CinternalIsMemoriesIdenticalSmallInt,
		&CinternalStoreKeySmallInt, &CinternalUnstoreKeySmallInt,
		a_allocator, a_deallocator);
}


static void CutilDLListItemExtraCleaner(void* a_container, struct SCutilDLListIterator* CPPUTILS_ARG_NN a_iter, TypeCinternalDeallocator CPPUTILS_ARG_NN a_remainingDataCleaner)
{
	struct SCutilDLLHash* pHashTbl = CPPUTILS_STATIC_CAST(struct SCutilDLLHash*, a_container);
	(*a_remainingDataCleaner)(CUtilDLLHashItemFromDLListIterator(a_iter)->data);
	(*(pHashTbl->keyUnstore))(pHashTbl->deallocator,
		CUtilDLLHashItemFromDLListIterator(a_iter)->key, CUtilDLLHashItemFromDLListIterator(a_iter)->keySize);
}


CUTILS_EXPORT void CUtilDLLHashDestroyEx(CutilDLLHash_t CPPUTILS_ARG_NN a_hashTbl, TypeCinternalDeallocator a_remainingDataCleaner)
{
	CInternalListCleanInline(a_hashTbl->first, a_hashTbl->deallocator, a_hashTbl, a_remainingDataCleaner, &CutilDLListItemExtraCleaner);
	(*(a_hashTbl->deallocator))(a_hashTbl->ppTable);
	(*(a_hashTbl->deallocator))(a_hashTbl);
}


CUTILS_EXPORT CutilDLLHashItem_t CUtilDLLHashAddDataEvenIfExist(CutilDLLHash_t CPPUTILS_ARG_NN a_hashTbl, const void* a_data, const void* a_key, size_t a_keySize)
{
	const size_t hash = ((*(a_hashTbl->hasher))(a_key, a_keySize)) % (a_hashTbl->numberOfBaskets);
	return CUtilDLLHashAddDataWithKnownHash(a_hashTbl, a_data, a_key, a_keySize, hash);
}


static inline struct SCutilDLLHashItem* CInternalHashFindItemInline(ConstCutilDLLHash_t CPPUTILS_ARG_NN a_hashTbl, const void* a_key, size_t a_keySize, size_t* CPPUTILS_ARG_NN a_pHash) {
	struct SCutilDLListIterator* pItem;
	*a_pHash = ((*(a_hashTbl->hasher))(a_key, a_keySize)) % (a_hashTbl->numberOfBaskets);
	pItem = a_hashTbl->ppTable[*a_pHash];
	while (pItem) {
		if ((*(a_hashTbl->isEq))(CUtilDLLHashItemFromTableIterator(pItem)->key, CUtilDLLHashItemFromTableIterator(pItem)->keySize, a_key, a_keySize)) {
			return CPPUTILS_CONST_CAST(struct SCutilDLLHashItem* ,CUtilDLLHashItemFromTableIterator(pItem));
		}
		pItem = pItem->next;
	}
	return CPPUTILS_NULL;
}


CUTILS_EXPORT CutilDLLHashItem_t CUtilDLLHashAddDataIfNotExists(CutilDLLHash_t CPPUTILS_ARG_NN a_hashTbl, const void* a_data, const void* a_key, size_t a_keySize)
{
	size_t unHash;
	if (CInternalHashFindItemInline(a_hashTbl, a_key, a_keySize,&unHash)) {
		return CPPUTILS_NULL;
	}
	return CUtilDLLHashAddDataWithKnownHash(a_hashTbl, a_data, a_key, a_keySize, unHash);
}



CUTILS_EXPORT CutilDLLHashItem_t CUtilDLLHashAddDataWithKnownHash(CutilDLLHash_t CPPUTILS_ARG_NN a_hashTbl, const void* a_data, const void* a_key, size_t a_keySize, size_t a_hash)
{
	struct SCutilDLLHashItem*const pNewItem = CPPUTILS_STATIC_CAST(struct SCutilDLLHashItem*, (*(a_hashTbl->allocator))(sizeof(struct SCutilDLLHashItem)));
	if (!pNewItem) {
		return CPPUTILS_NULL;
	}

	if (!(*(a_hashTbl->keyStore))(a_hashTbl->allocator, &(pNewItem->key), &(pNewItem->keySize), a_key, a_keySize)) {
		(*(a_hashTbl->deallocator))(pNewItem);
		return CPPUTILS_NULL;
	}

	pNewItem->data = CPPUTILS_CONST_CAST(void*, a_data);
	CUtilDLListAddCreatedIteratorFrontInline2(&(a_hashTbl->first), &(a_hashTbl->last), CUtilDLListIteratorFromDLLHashItem(pNewItem));
	CUtilDLListAddCreatedIteratorFrontInline1(&(a_hashTbl->ppTable[a_hash]), &(pNewItem->tbl));

	pNewItem->hash = a_hash;
	++(a_hashTbl->m_size);

	return pNewItem;
}


CUTILS_EXPORT CutilDLLHashItem_t CUtilDLLHashFindEx(ConstCutilDLLHash_t CPPUTILS_ARG_NN a_hashTbl, const void* a_key, size_t a_keySize, size_t* CPPUTILS_ARG_NN a_pHash)
{
	return CInternalHashFindItemInline(a_hashTbl, a_key, a_keySize, a_pHash);
}


CUTILS_EXPORT CutilDLLHashItem_t CUtilDLLHashFind(ConstCutilDLLHash_t CPPUTILS_ARG_NN a_hashTbl, const void* a_key, size_t a_keySize)
{
	size_t unHash;
	return CInternalHashFindItemInline(a_hashTbl,a_key,a_keySize,&unHash);
}


CUTILS_EXPORT CutilDLLHashItem_t CUtilDLLHashFirstItem(ConstCutilDLLHash_t CPPUTILS_ARG_NN a_hashTbl)
{
	return CUtilDLLHashItemFromDLListIterator(a_hashTbl->first);
}


CUTILS_EXPORT CutilDLLHashItem_t CUtilDLLHashLastItem(ConstCutilDLLHash_t CPPUTILS_ARG_NN a_hashTbl)
{
	return CUtilDLLHashItemFromDLListIterator(a_hashTbl->last);
}


CUTILS_EXPORT bool CUtilDLLHashRemoveData(CutilDLLHash_t CPPUTILS_ARG_NN a_hashTbl, const void* a_key, size_t a_keySize)
{
	size_t unHash;
	struct SCutilDLLHashItem* pIterator = CInternalHashFindItemInline(a_hashTbl, a_key, a_keySize, &unHash);
	if (pIterator) {
		CUtilDLLHashRemoveDataEx(a_hashTbl, pIterator);
		return true;
	}
	return false;
}


CUTILS_EXPORT void CUtilDLLHashRemoveDataEx(CutilDLLHash_t CPPUTILS_ARG_NN a_hashTbl, CutilDLLHashItem_t CPPUTILS_ARG_NN a_iter)
{
	//CInternalListRemoveItertaorInline(&(a_hashTbl->ppTable[CUtilDLLHashItemFromListIterator(a_iter)->hash]), &(CUtilDLLHashItemFromListIterator(a_iter)->tbl));
	//CUtilDLListRemoveDataNoFreeInline(&(a_hashTbl->lst), a_iter);
	CInternalListRemoveItertaorInline1(&(a_hashTbl->ppTable[a_iter->hash]), &(a_iter->tbl));
	CInternalListRemoveItertaorInline1(&(a_hashTbl->first), CUtilDLListIteratorFromDLLHashItem(a_iter));

	(*(a_hashTbl->keyUnstore))(a_hashTbl->deallocator, a_iter->key, a_iter->keySize);
	(*(a_hashTbl->deallocator))(CPPUTILS_CONST_CAST(struct SCutilDLLHashItem*, a_iter));
	--(a_hashTbl->m_size);
}


CUTILS_EXPORT size_t CUtilDLLHashSize(ConstCutilDLLHash_t CPPUTILS_ARG_NN a_hashTbl)
{
	return a_hashTbl->m_size;
}


CUTILS_EXPORT void* CInternalLHashGetDefaultFunctions(int a_function)
{
	switch (a_function) {
	case CUTILS_HASH_DEFAULT_FUNC_MMEM_HASH:
		return (void*)(&cinternal_hash1_raw_mem_inline);
	case CUTILS_HASH_DEFAULT_FUNC_SML_INT_HASH:
		return (void*)(&cinternal_hash1_small_int);
	default:
		return CPPUTILS_NULL;
	}  //  switch (a_function) {
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
    CinternalWrapperMemcpy(*a_pKeyStore, a_key, a_keySize);
    *a_pKeySizeStore = a_keySize;
    return true;
}


static void CinternalUnstoreKeyRawMemory(TypeCinternalDeallocator a_deallocator, void* a_key, size_t a_keySize) CPPUTILS_NOEXCEPT
{
    CPPUTILS_STATIC_CAST(void, a_keySize);
    (*a_deallocator)(a_key);
}


static size_t cinternal_hash1_small_int(const void* a_key, size_t a_keySize) CPPUTILS_NOEXCEPT
{
    CPPUTILS_STATIC_CAST(void, a_keySize);
    return CPPUTILS_REINTERPRET_CAST(size_t, a_key);
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
    *a_pKeyStore = CPPUTILS_CONST_CAST(void*, a_key);
    return true;
}


static void CinternalUnstoreKeySmallInt(TypeCinternalDeallocator a_deallocator, void* a_key, size_t a_keySize) CPPUTILS_NOEXCEPT
{
    CPPUTILS_STATIC_CAST(void, a_deallocator);
    CPPUTILS_STATIC_CAST(void, a_key);
    CPPUTILS_STATIC_CAST(void, a_keySize);
}


CPPUTILS_END_C
