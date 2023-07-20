//
// file:            disable_compiler_warnings.h
// path:			include/cinternal/disable_compiler_warnings.h
// created on:		2021 Nov 15
// created by:		Davit Kalantaryan (davit.kalantaryan@desy.de)
//

#ifndef CINTERNAL_INCLUDE_CINTERNAL_DISABLE_COMPILER_WARNINGS_H
#define CINTERNAL_INCLUDE_CINTERNAL_DISABLE_COMPILER_WARNINGS_H
#include <cinternal/internal_header.h>
// disable some warnings, those are assumed as errors
#if defined(_MSC_VER)
#pragma warning(disable:5031)  //  #pragma warning(pop): likely mismatch, popping warning state pushed in different file
#pragma warning (disable:4061)  // enumerator 'MonAppHiderEventNone' in switch of enum
#pragma warning (disable:4820)  // enumerator 'MonAppHiderEventNone' in switch of enum
#elif defined(CPPUTILS_GCC_FAMILY)
#pragma GCC diagnostic ignored "-Wattributes"
#endif  //  #if defined(_MSC_VER)
#endif  //  #ifndef CINTERNAL_INCLUDE_CINTERNAL_DISABLE_COMPILER_WARNINGS_H

#ifndef CINTERNAL_COMPILER_WARNINGS_DISABLED
#define CINTERNAL_COMPILER_WARNINGS_DISABLED	1

#ifdef CPPUTILS_COMPILER_WARNINGS_PUSH_POP
CPPUTILS_WARNINGS_PUSH
#define CPPUTILS_COMPILER_WARNINGS_PUSHED
#endif


#if defined(_MSC_VER)

#pragma warning(disable: 4191)
#pragma warning(disable:4710)
#pragma warning(disable:4711)
#pragma warning(disable:4668)
#pragma warning(disable:4820)
#pragma warning(disable:5039) // 'TpSetCallbackCleanupGroup': pointer or reference to potentially throwing function
#pragma warning (disable:4365)
#pragma warning (disable:4574)  //  winnt.h(1229,1): warning C4574: '__has_builtin' is defined to be '0': did you mean to use '#if __has_builtin'?
#ifndef __cplusplus
#pragma warning(disable:4255)
#endif
#if (_MSC_VER>=1929) && (_MSC_FULL_VER>192930100)
#pragma warning(disable:5246)
#endif

#elif defined(CPPUTILS_GCC_FAMILY) 

#pragma GCC diagnostic ignored "-Wattributes"

#endif


#endif  //  #ifndef CINTERNAL_COMPILER_WARNINGS_DISABLED
