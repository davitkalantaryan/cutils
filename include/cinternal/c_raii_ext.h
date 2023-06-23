//
// file:            c_raii.h
// path:			include/cinternal/c_raii.h
// created on:		2023 Feb 25
// created by:		Davit Kalantaryan (davit.kalantaryan@desy.de)
//
// todo:            This implementation is incomplete
//

#ifndef CINTERNAL_INCLUDE_CINTERNAL_C_RAII_EXT_H
#define CINTERNAL_INCLUDE_CINTERNAL_C_RAII_EXT_H

#include <cinternal/internal_header.h>
#ifdef _MSC_VER
#include <excpt.h>
#endif


#ifdef _MSC_VER

#define CINTERNAL_C_RAII_ANY_CLEAN_CODE_START	__try { __try {
#define CINTERNAL_C_RAII_ANY_CLEAN_CODE_END     }__finally {
#define CINTERNAL_C_RAII_ANY_CLEAN_END          }} __except (EXCEPTION_EXECUTE_HANDLER) {}

#else


#endif


#endif  // #ifndef CINTERNAL_INCLUDE_CINTERNAL_C_RAII_EXT_H
