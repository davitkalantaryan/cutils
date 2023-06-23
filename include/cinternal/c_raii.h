//
// file:            c_raii.h
// path:			include/cinternal/c_raii.h
// created on:		2023 Feb 25
// created by:		Davit Kalantaryan (davit.kalantaryan@desy.de)
//

#ifndef CINTERNAL_INCLUDE_CINTERNAL_C_RAII_H
#define CINTERNAL_INCLUDE_CINTERNAL_C_RAII_H

#include <cinternal/internal_header.h>

typedef void (*TypeCInternalCRaii)(void** CPPUTILS_ARG_NN);


#ifdef _MSC_VER

#define CINTERNAL_C_RAII_CODE_START(_func,_ud)	{const TypeCInternalCRaii ___funcToCall = _func; void* ___ud = (_ud); __try {
#define CINTERNAL_C_RAII_CODE_END				}__finally { (*___funcToCall)(&___ud); }}

#else

#define CINTERNAL_C_RAII_CODE_START(_func,_ud)	{ void* __attribute__ ((__cleanup__(_func))) ___ud = (_ud); CPPUTILS_STATIC_CAST(void,___ud);
#define CINTERNAL_C_RAII_CODE_END               }

#endif


#endif  // #ifndef CINTERNAL_INCLUDE_CINTERNAL_DISABLE_COMPILER_WARNINGS_H
