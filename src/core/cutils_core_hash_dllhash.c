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
#define cinternal_hash1_small_int_needed
#define CinternalIsMemoriesIdenticalSmallInt_needed
#define CinternalStoreKeySmallInt_needed
#define CinternalUnstoreKeySmallInt_needed
#define CinternalStoreKeyRawMemory_needed
#define CinternalUnstoreKeyRawMemory_needed
#define CinternalIsMemoriesIdenticalRawMemory_needed
//#define DefaultRemainingCleaner_needed
#define cinternal_hash1_raw_mem_needed
#include <cinternal/hash/functions.h>
#include <string.h>

#define CUTILS_HASH_DEFAULT_NUMBER_OF_BASKETS	4096


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
