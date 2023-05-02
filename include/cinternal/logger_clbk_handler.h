//
// file:			logger_clbk_handler.h
// path:			include/cinternal/logger_clbk_handler.h
// created on:		2023 Mar 30
// created by:		Davit Kalantaryan (davit.kalantaryan@desy.de)
//

#ifndef CINTERNAL_INCLUDE_CINTERNAL_LOGGER_CLBK_HANDLER_H
#define CINTERNAL_INCLUDE_CINTERNAL_LOGGER_CLBK_HANDLER_H

#include <cinternal/export_symbols.h>
#include <stdarg.h>


CPPUTILS_BEGIN_C


enum CinternalLogTypes { CinternalLogTypeError, CinternalLogTypeWarning, CinternalLogTypeInfo, CinternalLogTypeDebug };
typedef void (*TypeCinternalLogger)(void* a_userData, enum CinternalLogTypes a_type, const char* a_fmtStr, va_list alist);

CINTERNAL_EXPORT void CinternalInstallLogger(void* a_userData, TypeCinternalLogger a_clbk);
CINTERNAL_EXPORT void CinternalGetLogger(void** a_pUserData, TypeCinternalLogger* a_pClbk);


CPPUTILS_END_C


#endif  // #ifndef CINTERNAL_INCLUDE_CINTERNAL_LOGGER_CLBK_HANDLER_H
