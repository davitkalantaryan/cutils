//
// repo:			cutils
// file:			logger.h
// path:			src/include/cutils/logger.h
// created on:		2023 Mar 30
// created by:		Davit Kalantaryan (davit.kalantaryan@desy.de)
//

#ifndef CUTILS_INCLUDE_CUTILS_LOGGER_H
#define CUTILS_INCLUDE_CUTILS_LOGGER_H

#include <cutils/export_symbols.h>
#include <stdarg.h>
#include <stdbool.h>


CPPUTILS_BEGIN_C


enum CinternalLogTypes { CinternalLogTypeError, CinternalLogTypeWarning, CinternalLogTypeInfo, CinternalLogTypeDebug };
typedef void (*TypeCinternalLogger)(void* a_userData, enum CinternalLogTypes a_type, bool a_bSync, const char* a_fmtStr, va_list alist);

CUTILS_EXPORT void CinternalInstallLogger(void* a_userData, TypeCinternalLogger a_clbk);
CUTILS_EXPORT void CinternalGetLogger(void** a_pUserData, TypeCinternalLogger* a_pClbk);
CUTILS_EXPORT void CinternalMakeLog(const char* a_src, int a_line, enum CinternalLogTypes a_type, const char* a_fmtStr, ...);
CUTILS_EXPORT const char* CInternalFileNameFromPath(const char* a_fullPath);
CUTILS_EXPORT void CinternalMakeLogNoExtraData(enum CinternalLogTypes a_type, bool a_bSync, const char* a_fmtStr, ...);
CUTILS_EXPORT void CinternalLogPrintDateAndTime(enum CinternalLogTypes a_type, bool a_bSync);


#define CInternalLogError(...)		CinternalMakeLog(CInternalFileNameFromPath(__FILE__),__LINE__,CinternalLogTypeError,__VA_ARGS__)
#define CInternalLogWarning(...)	CinternalMakeLog(CInternalFileNameFromPath(__FILE__),__LINE__,CinternalLogTypeWarning,__VA_ARGS__)
#define CInternalLogInfo(...)		CinternalMakeLog(CInternalFileNameFromPath(__FILE__),__LINE__,CinternalLogTypeInfo,__VA_ARGS__)
#if defined(NDEBUG) || defined(CUTILS_NO_DEBUG_LOGS)
#define CInternalLogDebug(...)
#else
#define CInternalLogDebug(...)		CinternalMakeLog(CInternalFileNameFromPath(__FILE__),__LINE__,CinternalLogTypeDebug,__VA_ARGS__)
#endif


CPPUTILS_END_C


#endif  // #ifndef CUTILS_INCLUDE_CUTILS_LOGGER_H
