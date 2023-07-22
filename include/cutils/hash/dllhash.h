//
// file:            dllhash.h
// path:			include/cinternal/hash/dllhash.h
// created on:		2023 Feb 25
// created by:		Davit Kalantaryan (davit.kalantaryan@desy.de)
//

#ifndef CINTERNAL_INCLUDE_CINTERNAL_HASH_DLLHASH_H
#define CINTERNAL_INCLUDE_CINTERNAL_HASH_DLLHASH_H

#include <cinternal/export_symbols.h>
#include <cinternal/common_data01.h>
#include <cinternal/common_data02.h>
#include <stdbool.h>


CPPUTILS_BEGIN_C

#define CINTERNAL_HASH_DEFAULT_FUNC_MMEM_HASH		1
#define CINTERNAL_HASH_DEFAULT_FUNC_SML_INT_HASH	2

struct SCinternalDLLHash;
struct SCinternalDLLHashItem {
	struct SCinternalDLListIterator			lst;
	struct SCinternalDLListIterator			tbl;
	void*									data;
	void*									key;
	size_t									keySize;
	size_t									hash;
};

typedef const struct SCinternalDLLHashItem*	CinternalDLLHashItem_t;
typedef struct SCinternalDLLHash* CinternalDLLHash_t;
typedef const struct SCinternalDLLHash* ConstCinternalDLLHash_t;

#define CInternalDLListIteratorFromDLLHashItem(_item_ptr)	(&((_item_ptr)->lst))
#define CInternalDLLHashItemFromDLListIterator(_iter_ptr)	cpputils_container_of(_iter_ptr,const struct SCinternalDLLHashItem,lst)



CINTERNAL_EXPORT CinternalDLLHash_t CInternalDLLHashCreateExAny(size_t a_numberOfBaskets,
	TypeCinternalHasher CPPUTILS_ARG_NN a_hasher, TypeCinternalIsMemoriesIdentical CPPUTILS_ARG_NN a_isEq,
	TypeCinternalStoreKey CPPUTILS_ARG_NN a_keyStore, TypeCinternalUnstoreKey CPPUTILS_ARG_NN a_keyUnstore,
	TypeCinternalAllocator a_allocator, TypeCinternalDeallocator a_deallocator);
CINTERNAL_EXPORT CinternalDLLHash_t CInternalDLLHashCreateExAnyDefRawMem(size_t a_numberOfBaskets,
	TypeCinternalHasher a_hasher, TypeCinternalIsMemoriesIdentical a_isEq,
	TypeCinternalStoreKey a_keyStore, TypeCinternalUnstoreKey a_keyUnstore,
	TypeCinternalAllocator a_allocator, TypeCinternalDeallocator a_deallocator);
CINTERNAL_EXPORT CinternalDLLHash_t CInternalDLLHashCreateExAnyDefSmlInt(size_t a_numberOfBaskets,
	TypeCinternalHasher a_hasher, TypeCinternalIsMemoriesIdentical a_isEq,
	TypeCinternalStoreKey a_keyStore, TypeCinternalUnstoreKey a_keyUnstore,
	TypeCinternalAllocator a_allocator, TypeCinternalDeallocator a_deallocator);
CINTERNAL_EXPORT CinternalDLLHash_t CInternalDLLHashCreateExRawMem(size_t a_numberOfBaskets, TypeCinternalAllocator a_allocator, TypeCinternalDeallocator a_deallocator);
CINTERNAL_EXPORT CinternalDLLHash_t CInternalDLLHashCreateExSmlInt(size_t a_numberOfBaskets,TypeCinternalAllocator a_allocator, TypeCinternalDeallocator a_deallocator);
CINTERNAL_EXPORT void	CInternalDLLHashDestroyEx(CinternalDLLHash_t CPPUTILS_ARG_NN a_hashTbl, TypeCinternalDeallocator a_remainingDataCleaner);
CINTERNAL_EXPORT CinternalDLLHashItem_t CInternalDLLHashAddDataIfNotExists(CinternalDLLHash_t CPPUTILS_ARG_NN a_hashTbl, const void* a_data, const void* a_key, size_t a_keySize);
CINTERNAL_EXPORT CinternalDLLHashItem_t CInternalDLLHashAddDataEvenIfExist(CinternalDLLHash_t CPPUTILS_ARG_NN a_hashTbl, const void* a_data, const void* a_key, size_t a_keySize);
CINTERNAL_EXPORT CinternalDLLHashItem_t CInternalDLLHashAddDataWithKnownHash(CinternalDLLHash_t CPPUTILS_ARG_NN a_hashTbl, const void* a_data, const void* a_key, size_t a_keySize, size_t a_hash);
CINTERNAL_EXPORT CinternalDLLHashItem_t CInternalDLLHashFindEx(ConstCinternalDLLHash_t CPPUTILS_ARG_NN a_hashTbl, const void* a_key, size_t a_keySize,size_t* CPPUTILS_ARG_NN a_pHash);
CINTERNAL_EXPORT CinternalDLLHashItem_t CInternalDLLHashFind(ConstCinternalDLLHash_t CPPUTILS_ARG_NN a_hashTbl, const void* a_key, size_t a_keySize);
CINTERNAL_EXPORT CinternalDLLHashItem_t CInternalDLLHashFirstItem(ConstCinternalDLLHash_t CPPUTILS_ARG_NN a_hashTbl);
CINTERNAL_EXPORT CinternalDLLHashItem_t CInternalDLLHashLastItem(ConstCinternalDLLHash_t CPPUTILS_ARG_NN a_hashTbl);
CINTERNAL_EXPORT void	CInternalDLLHashRemoveDataEx(CinternalDLLHash_t CPPUTILS_ARG_NN a_hashTbl, CinternalDLLHashItem_t CPPUTILS_ARG_NN a_iterator);
CINTERNAL_EXPORT bool	CInternalDLLHashRemoveData(CinternalDLLHash_t CPPUTILS_ARG_NN a_hashTbl, const void* a_key, size_t a_keySize);
CINTERNAL_EXPORT size_t CInternalDLLHashSize(ConstCinternalDLLHash_t CPPUTILS_ARG_NN a_hashTbl);


CINTERNAL_EXPORT void* CInternalLHashGetDefaultFunctions(int a_function);


CPPUTILS_END_C

#define CInternalDLLHashCreateRawMem(_size)										CInternalDLLHashCreateExRawMem(_size,CPPUTILS_NULL,CPPUTILS_NULL)
#define CInternalDLLHashCreateSmlInt(_size)										CInternalDLLHashCreateExSmlInt(_size,CPPUTILS_NULL,CPPUTILS_NULL)
#define CInternalDLLHashDestroy(_hashTbl)										CInternalDLLHashDestroyEx(_hashTbl,CPPUTILS_NULL)
#define CInternalStrKeyPairFn(_str)												(_str),strlen(_str)  // to use this string.h should be included
#define CInternalSmallIntHPairFn(_key)											((void*)((size_t)(_key))), 0
#define CInternalDLLHashAddDataIfNotExistsSmlInt(_hashTbl,_data,_key)			CInternalDLLHashAddDataIfNotExists(_hashTbl,_data,((void*)((size_t)(_key))),0)
#define CInternalDLLHashAddDataEvenIfExistSmlInt(_hashTbl,_data,_key)			CInternalDLLHashAddDataEvenIfExist(_hashTbl,_data,((void*)((size_t)(_key))),0)
#define CInternalDLLHashAddDataWithKnownHashSmlInt(_hashTbl,_data,_key,_hash)	CInternalDLLHashAddDataWithKnownHash(_hashTbl,_data,((void*)((size_t)(_key))),0,_hash)


#endif  // #ifndef CINTERNAL_INCLUDE_CINTERNAL_HASH_DLLHASH_H
