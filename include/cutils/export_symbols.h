//
// repo:			cutils
// file:			export_symbols.h
// path:			include/cutils/export_symbols.h
// created on:		2023 Feb 25
// created by:		Davit Kalantaryan (davit.kalantaryan@gmail.com)
//

#ifndef CUTILS_INCLUDE_CUTILS_EXPORT_SYMBOLS_H
#define CUTILS_INCLUDE_CUTILS_EXPORT_SYMBOLS_H

#include <cinternal/internal_header.h>


#ifndef CUTILS_EXPORT
#if defined(CUTILS_COMPILING_SHARED_LIB)
#define CUTILS_EXPORT CPPUTILS_DLL_PUBLIC
#elif defined(CUTILS_USING_STATIC_LIB_OR_OBJECTS)
#define CUTILS_EXPORT
#elif defined(CUTILS_LOAD_FROM_DLL)
#define CUTILS_EXPORT CPPUTILS_IMPORT_FROM_DLL
#else
#define CUTILS_EXPORT CPPUTILS_DLL_PRIVATE
#endif
#endif


#endif  // #ifndef CUTILS_INCLUDE_CUTILS_EXPORT_SYMBOLS_H
