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


CPPUTILS_BEGIN_C

typedef size_t(*TypeCinternalHasher)(const void* key, size_t keySize);
typedef void(*TypeCinternalDeallocator)(void*);
typedef void*(*TypeCinternalAllocator)(size_t);


CPPUTILS_END_C


#endif  // #ifndef CINTERNAL_INCLUDE_CINTERNAL_COMMON_DATA01_H
