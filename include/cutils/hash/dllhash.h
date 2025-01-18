//
// repo:			cutils
// file:            dllhash.h
// path:			include/cutils/hash/dllhash.h
// created on:		2023 Feb 25
// created by:		Davit Kalantaryan (davit.kalantaryan@desy.de)
//

#ifndef CUTILS_INCLUDE_CUTILS_HASH_DLLHASH_H
#define CUTILS_INCLUDE_CUTILS_HASH_DLLHASH_H

#include <cutils/export_symbols.h>
#include <cutils/common_data02.h>
#include <cinternal/hash.h>
#include <cinternal/common_data01.h>
#include <cinternal/disable_compiler_warnings.h>
#include <stdbool.h>
#include <cinternal/undisable_compiler_warnings.h>


CPPUTILS_BEGIN_C

#define CUTILS_HASH_DEFAULT_FUNC_MMEM_HASH		1
#define CUTILS_HASH_DEFAULT_FUNC_SML_INT_HASH	2

struct SCutilDLLHash;
struct SCutilDLLHashItem {
	struct SCutilDLListIterator			lst;
	struct SCutilDLListIterator			tbl;
	void*									data;
	void*									key;
	size_t									keySize;
	size_t									hash;
};

typedef const struct SCutilDLLHashItem*	CutilDLLHashItem_t;
typedef struct SCutilDLLHash* CutilDLLHash_t;
typedef const struct SCutilDLLHash* ConstCutilDLLHash_t;

#define CUtilDLListIteratorFromDLLHashItem(_item_ptr)	(&((_item_ptr)->lst))
#define CUtilDLLHashItemFromDLListIterator(_iter_ptr)	cpputils_container_of(_iter_ptr,const struct SCutilDLLHashItem,lst)



CUTILS_EXPORT CutilDLLHash_t CUtilDLLHashCreateExAny(size_t a_numberOfBaskets,
	TypeCinternalHasher CPPUTILS_ARG_NN a_hasher, TypeCinternalIsMemoriesIdentical CPPUTILS_ARG_NN a_isEq,
	TypeCinternalStoreKey CPPUTILS_ARG_NN a_keyStore, TypeCinternalUnstoreKey CPPUTILS_ARG_NN a_keyUnstore,
	TypeCinternalAllocator a_allocator, TypeCinternalDeallocator a_deallocator);
CUTILS_EXPORT CutilDLLHash_t CUtilDLLHashCreateExAnyDefRawMem(size_t a_numberOfBaskets,
	TypeCinternalHasher a_hasher, TypeCinternalIsMemoriesIdentical a_isEq,
	TypeCinternalStoreKey a_keyStore, TypeCinternalUnstoreKey a_keyUnstore,
	TypeCinternalAllocator a_allocator, TypeCinternalDeallocator a_deallocator);
CUTILS_EXPORT CutilDLLHash_t CUtilDLLHashCreateExAnyDefSmlInt(size_t a_numberOfBaskets,
	TypeCinternalHasher a_hasher, TypeCinternalIsMemoriesIdentical a_isEq,
	TypeCinternalStoreKey a_keyStore, TypeCinternalUnstoreKey a_keyUnstore,
	TypeCinternalAllocator a_allocator, TypeCinternalDeallocator a_deallocator);
CUTILS_EXPORT CutilDLLHash_t CUtilDLLHashCreateExRawMem(size_t a_numberOfBaskets, TypeCinternalAllocator a_allocator, TypeCinternalDeallocator a_deallocator);
CUTILS_EXPORT CutilDLLHash_t CUtilDLLHashCreateExSmlInt(size_t a_numberOfBaskets,TypeCinternalAllocator a_allocator, TypeCinternalDeallocator a_deallocator);
CUTILS_EXPORT void	CUtilDLLHashDestroyEx(CutilDLLHash_t CPPUTILS_ARG_NN a_hashTbl, TypeCinternalDeallocator a_remainingDataCleaner);
CUTILS_EXPORT CutilDLLHashItem_t CUtilDLLHashAddDataIfNotExists(CutilDLLHash_t CPPUTILS_ARG_NN a_hashTbl, const void* a_data, const void* a_key, size_t a_keySize);
CUTILS_EXPORT CutilDLLHashItem_t CUtilDLLHashAddDataEvenIfExist(CutilDLLHash_t CPPUTILS_ARG_NN a_hashTbl, const void* a_data, const void* a_key, size_t a_keySize);
CUTILS_EXPORT CutilDLLHashItem_t CUtilDLLHashAddDataWithKnownHash(CutilDLLHash_t CPPUTILS_ARG_NN a_hashTbl, const void* a_data, const void* a_key, size_t a_keySize, size_t a_hash);
CUTILS_EXPORT CutilDLLHashItem_t CUtilDLLHashFindEx(ConstCutilDLLHash_t CPPUTILS_ARG_NN a_hashTbl, const void* a_key, size_t a_keySize,size_t* CPPUTILS_ARG_NN a_pHash);
CUTILS_EXPORT CutilDLLHashItem_t CUtilDLLHashFind(ConstCutilDLLHash_t CPPUTILS_ARG_NN a_hashTbl, const void* a_key, size_t a_keySize);
CUTILS_EXPORT CutilDLLHashItem_t CUtilDLLHashFirstItem(ConstCutilDLLHash_t CPPUTILS_ARG_NN a_hashTbl);
CUTILS_EXPORT CutilDLLHashItem_t CUtilDLLHashLastItem(ConstCutilDLLHash_t CPPUTILS_ARG_NN a_hashTbl);
CUTILS_EXPORT void	CUtilDLLHashRemoveDataEx(CutilDLLHash_t CPPUTILS_ARG_NN a_hashTbl, CutilDLLHashItem_t CPPUTILS_ARG_NN a_iterator);
CUTILS_EXPORT bool	CUtilDLLHashRemoveData(CutilDLLHash_t CPPUTILS_ARG_NN a_hashTbl, const void* a_key, size_t a_keySize);
CUTILS_EXPORT size_t CUtilDLLHashSize(ConstCutilDLLHash_t CPPUTILS_ARG_NN a_hashTbl);


CUTILS_EXPORT void* CInternalLHashGetDefaultFunctions(int a_function);


CPPUTILS_END_C

#define CUtilDLLHashCreateRawMem(_size)										CUtilDLLHashCreateExRawMem(_size,CPPUTILS_NULL,CPPUTILS_NULL)
#define CUtilDLLHashCreateSmlInt(_size)										CUtilDLLHashCreateExSmlInt(_size,CPPUTILS_NULL,CPPUTILS_NULL)
#define CUtilDLLHashDestroy(_hashTbl)										CUtilDLLHashDestroyEx(_hashTbl,CPPUTILS_NULL)
#define CUtilDLLHashAddDataIfNotExistsSmlInt(_hashTbl,_data,_key)			CUtilDLLHashAddDataIfNotExists(_hashTbl,_data,((void*)((size_t)(_key))),0)
#define CUtilDLLHashAddDataEvenIfExistSmlInt(_hashTbl,_data,_key)			CUtilDLLHashAddDataEvenIfExist(_hashTbl,_data,((void*)((size_t)(_key))),0)
#define CUtilDLLHashAddDataWithKnownHashSmlInt(_hashTbl,_data,_key,_hash)	CUtilDLLHashAddDataWithKnownHash(_hashTbl,_data,((void*)((size_t)(_key))),0,_hash)


#endif  // #ifndef CUTILS_INCLUDE_CUTILS_HASH_DLLHASH_H
