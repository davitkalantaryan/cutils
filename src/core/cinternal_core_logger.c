//
// file:			cinternal_core_logger.c
// path:			src/core/cinternal_core_logger.c
// created on:		2023 Mar 30
// created by:		Davit Kalantaryan (davit.kalantaryan@desy.de)
//

#include <cinternal/logger.h>
#include <string.h>
#include <stdio.h>


CPPUTILS_BEGIN_C


#ifdef _MSC_VER
#define URL_CAPT_API_FILE_DELIMER0	'\\'
#define URL_CAPT_API_FILE_DELIMER1	'/'
#else
#define URL_CAPT_API_FILE_DELIMER0	'/'
#define URL_CAPT_API_FILE_DELIMER1	'\\'
#endif

#ifdef _MSC_VER
#pragma warning (disable:4061)
#endif

static void CinternalDefaultLoggerFunction(void* a_userData, enum CinternalLogTypes a_type, const char* a_fmtStr, va_list a_argptr);


static void*                    s_userData = CPPUTILS_NULL;
static TypeCinternalLogger      s_loggerClbk = &CinternalDefaultLoggerFunction;


static void CinternalDefaultLoggerFunction(void* a_userData, enum CinternalLogTypes a_type, const char* a_fmtStr, va_list a_argptr)
{
    CPPUTILS_STATIC_CAST(void, a_userData);
    switch (a_type) {
    case CinternalLogTypeInfo:
        vprintf(a_fmtStr, a_argptr);
        break;
    case CinternalLogTypeDebug:
#if defined(NDEBUG) || (defined(CINTERNAL_NO_DEBUG_LOGS) && defined(CINTERNAL_NO_DEBUG_LOGS_FOR_LIB))
        CPPUTILS_STATIC_CAST(void, a_userData);
#else
        vprintf(a_fmtStr, a_argptr);
#endif
        break;
    default:
        vfprintf(stderr, a_fmtStr, a_argptr);
        break;
    }  //  switch (a_type) {
}


CINTERNAL_EXPORT void CinternalInstallLogger(void* a_userData, TypeCinternalLogger a_clbk)
{
    s_userData = a_userData;
    s_loggerClbk = a_clbk ? a_clbk : (&CinternalDefaultLoggerFunction);
}


CINTERNAL_EXPORT void CinternalGetLogger(void** a_pUserData, TypeCinternalLogger* a_pClbk)
{
    if (a_pUserData) { *a_pUserData = s_userData; }
    if (a_pClbk) { *a_pClbk = s_loggerClbk; }
}


static void CinternalMakeLogPrivate(enum CinternalLogTypes a_type, const char* a_fmtStr, ...)
{
	va_list argptr;
	va_start(argptr, a_fmtStr);
	(*s_loggerClbk)(s_userData, a_type,a_fmtStr, argptr);
	va_end(argptr);
}


CINTERNAL_EXPORT const char* CInternalFileNameFromPath(const char* a_fullPath)
{
	const char* cpcDelim = strrchr(a_fullPath, URL_CAPT_API_FILE_DELIMER0);
	if (cpcDelim) { return cpcDelim+1; }
	cpcDelim = strrchr(a_fullPath, URL_CAPT_API_FILE_DELIMER1);
	if (cpcDelim) { return cpcDelim+1; }
	return a_fullPath;
}


CINTERNAL_EXPORT void CinternalMakeLog(const char* a_src, int a_line, enum CinternalLogTypes a_type, const char* a_fmtStr, ...)
{
	va_list argptr;

    CinternalMakeLogPrivate(a_type, "src:\"%s\",ln:%d - ", a_src, a_line);
	va_start(argptr, a_fmtStr);
	(*s_loggerClbk)(s_userData, a_type, a_fmtStr, argptr);
	va_end(argptr);
    CinternalMakeLogPrivate(a_type, "\n");
}


CPPUTILS_CODE_INITIALIZER(cinternal_core_logger_initialize) {
    s_userData = CPPUTILS_NULL;
    s_loggerClbk = &CinternalDefaultLoggerFunction;
}


CPPUTILS_END_C
