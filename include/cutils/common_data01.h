//
// file:            common_data01.h
// path:			include/cinternal/common_data01.h
// created on:		2023 Feb 25
// created by:		Davit Kalantaryan (davit.kalantaryan@desy.de)
//

#ifndef CINTERNAL_INCLUDE_CINTERNAL_COMMON_DATA01_H
#define CINTERNAL_INCLUDE_CINTERNAL_COMMON_DATA01_H

#include <cinternal/export_symbols.h>
#include <stddef.h>
#include <stdbool.h>

#if defined(_MSC_VER)
#pragma warning(disable: 4152)  // this will help to keep functions pointers also in the containers
#else
#endif


CPPUTILS_BEGIN_C


typedef void(*TypeCinternalDeallocator)(void*);
typedef void* (*TypeCinternalAllocator)(size_t);
typedef size_t(*TypeCinternalHasher)(const void* key, size_t keySize);
typedef bool(*TypeCinternalIsMemoriesIdentical)(const void* key1, size_t keySize1, const void* key2, size_t keySize2);
typedef bool(*TypeCinternalStoreKey)(TypeCinternalAllocator a_allocator, void** a_pKeyStore, size_t* a_pKeySizeStore, const void* key, size_t keySize);
typedef void(*TypeCinternalUnstoreKey)(TypeCinternalDeallocator a_deallocator, void* key, size_t keySize);


CPPUTILS_END_C



#endif  // #ifndef CINTERNAL_INCLUDE_CINTERNAL_COMMON_DATA01_H
