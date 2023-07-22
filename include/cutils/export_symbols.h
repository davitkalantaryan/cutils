//
// file:			export_symbols.h
// path:			include/cinternal/export_symbols.h
// created on:		2023 Feb 25
// created by:		Davit Kalantaryan (davit.kalantaryan@gmail.com)
//

#ifndef CINTERNAL_INCLUDE_CINTERNAL_EXPORT_SYMBOLS_H
#define CINTERNAL_INCLUDE_CINTERNAL_EXPORT_SYMBOLS_H

#include <cinternal/internal_header.h>


#ifndef CINTERNAL_EXPORT
#if defined(CINTERNAL_COMPILING_SHARED_LIB)
#define CINTERNAL_EXPORT CPPUTILS_DLL_PUBLIC
#elif defined(CINTERNAL_USING_STATIC_LIB_OR_OBJECTS)
#define CINTERNAL_EXPORT
#elif defined(CINTERNAL_LOAD_FROM_DLL)
#define CINTERNAL_EXPORT CPPUTILS_IMPORT_FROM_DLL
#else
#define CINTERNAL_EXPORT CPPUTILS_DLL_PRIVATE
#endif
#endif


#endif  // #ifndef CINTERNAL_INCLUDE_CINTERNAL_EXPORT_SYMBOLS_H
