//
// file:            flagshelper.h
// path:			include/cinternal/flagshelper.h
// created on:		2021 Nov 13
// created by:		Davit Kalantaryan (davit.kalantaryan@gmail.com)
//
// if CPPUTILS_FLAGS_UN_RAW macros is used, then for uint64_t include #include <stdint.h>
//

#ifndef CINTERNAL_INCLUDE_CINTERNAL_FLAGSHELPER_H
#define CINTERNAL_INCLUDE_CINTERNAL_FLAGSHELPER_H

#include <cinternal/internal_header.h>

#ifndef CINTERNAL_FLAGS_HELPER_VERSION
#if defined(USING_CINTERNA_FLAGS_HELPER_VERSION2) || defined(USING_CINTERNAL_FLAGS_HELPER_VERSION2)
#define CINTERNAL_FLAGS_HELPER_VERSION      2
#else
#define CINTERNAL_FLAGS_HELPER_VERSION      1
#endif
#endif


#if CINTERNAL_FLAGS_HELPER_VERSION == 1
#include <cinternal/flagshelper01.h>
#elif CINTERNAL_FLAGS_HELPER_VERSION == 2
#include <cinternal/flagshelper02.h>
#else
#error this version of flags helper is not implemented
#endif


#endif  // #ifndef CINTERNAL_INCLUDE_CINTERNAL_FLAGSHELPER_H
