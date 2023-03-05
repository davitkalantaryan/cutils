//
// file:            lhash.h
// path:			include/cinternal/hash/lhash.h
// created on:		2023 Feb 25
// created by:		Davit Kalantaryan (davit.kalantaryan@desy.de)
//

#ifndef CINTERNAL_INCLUDE_CINTERNAL_HASH_LHASH_H
#define CINTERNAL_INCLUDE_CINTERNAL_HASH_LHASH_H

#include <cinternal/export_symbols.h>
#include <cinternal/common_data01.h>
#include <stdbool.h>


CPPUTILS_BEGIN_C

struct SCinternalLHashItem {
	struct SCinternalLHashItem* prevInTbl, * nextInTbl, * prevIList, * nextInList;
	void*				data;
	void*				key;
	size_t				keySize;
	size_t				hash;
};

typedef const struct SCinternalLHashItem* CInternalLHashIterator;
typedef struct SCinternalLHash* CinternalLHash_t;
typedef const struct SCinternalLHash* ConstCinternalLHash_t;


CINTERNAL_EXPORT CinternalLHash_t CInternalLHashCreateEx(size_t a_numberOfBaskets, TypeCinternalHasher a_hasher, TypeCinternalAllocator a_allocator, TypeCinternalDeallocator a_deallocator);
CINTERNAL_EXPORT void	CInternalLHashDestroyEx(CinternalLHash_t a_hashTbl, TypeCinternalDeallocator a_remainingDataCleaner);
CINTERNAL_EXPORT CInternalLHashIterator CInternalLHashAddDataEvenIfExist(CinternalLHash_t a_hashTbl, const void* a_data, const void* a_key, size_t a_keySize);
CINTERNAL_EXPORT CInternalLHashIterator CInternalLHashAddDataIfNotExists(CinternalLHash_t a_hashTbl, const void* a_data, const void* a_key, size_t a_keySize);
CINTERNAL_EXPORT CInternalLHashIterator CInternalLHashAddDataWithKnownHash(CinternalLHash_t a_hashTbl, const void* a_data, const void* a_key, size_t a_keySize, size_t a_hash);
CINTERNAL_EXPORT CInternalLHashIterator CInternalLHashFindEx(ConstCinternalLHash_t a_hashTbl, const void* a_key, size_t a_keySize,size_t* CPPUTILS_ARG_NO_NULL a_pHash);
CINTERNAL_EXPORT CInternalLHashIterator CInternalLHashFind(ConstCinternalLHash_t a_hashTbl, const void* a_key, size_t a_keySize);
CINTERNAL_EXPORT CInternalLHashIterator CInternalLHashFirstItem(ConstCinternalLHash_t a_hashTbl);
CINTERNAL_EXPORT void	CInternalLHashRemoveDataEx(CinternalLHash_t a_hashTbl, CInternalLHashIterator a_iterator);
CINTERNAL_EXPORT bool	CInternalLHashRemoveData(CinternalLHash_t a_hashTbl, const void* a_key, size_t a_keySize);
CINTERNAL_EXPORT size_t CInternalLHashSize(ConstCinternalLHash_t a_hashTbl);


CPPUTILS_END_C

#define CInternalLHashCreate(_size)			CInternalLHashCreateEx(_size,CPPUTILS_NULL,CPPUTILS_NULL,CPPUTILS_NULL)
#define CInternalLHashDestroy(_hashTbl)		CInternalLHashDestroyEx(_hashTbl,CPPUTILS_NULL)
#define CInternalStringKeyPair(_string)		(_string),strlen(_string)  // to use this string.h should be included
#define CInternalAnyDataHPair(_data)		(&(_data)), sizeof(_data)


#endif  // #ifndef CINTERNAL_INCLUDE_CINTERNAL_HASH_LHASH_H
