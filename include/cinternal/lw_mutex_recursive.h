//
// file:            lw_mutex_recursive.h
// path:			include/cinternal/lw_mutex_recursive.h
// created on:		2023 Feb 25
// created by:		Davit Kalantaryan (davit.kalantaryan@desy.de)
//

#ifndef CINTERNAL_INCLUDE_CINTERNAL_LW_MUTEX_RECURSIVE_H
#define CINTERNAL_INCLUDE_CINTERNAL_LW_MUTEX_RECURSIVE_H

#include <cinternal/export_symbols.h>
#include <cinternal/disable_compiler_warnings.h>
#ifdef _WIN32
#include <WinSock2.h>
#include <WS2tcpip.h>
#include <Windows.h>
#else
#include <pthread.h>
#endif
#include <cinternal/undisable_compiler_warnings.h>


CPPUTILS_BEGIN_C


#ifdef _WIN32
typedef CRITICAL_SECTION	cinternal_lw_recursive_mutex_t;
#else
typedef pthread_mutex_t		cinternal_lw_recursive_mutex_t;
#endif

CINTERNAL_EXPORT int  cinternal_lw_recursive_mutex_create(cinternal_lw_recursive_mutex_t* a_pMutex);
CINTERNAL_EXPORT void cinternal_lw_recursive_mutex_destroy(cinternal_lw_recursive_mutex_t* a_pMutex);
CINTERNAL_EXPORT int  cinternal_lw_recursive_mutex_lock(cinternal_lw_recursive_mutex_t* a_pMutex);
CINTERNAL_EXPORT void cinternal_lw_recursive_mutex_unlock(cinternal_lw_recursive_mutex_t* a_pMutex);


CPPUTILS_END_C


#endif  // #ifndef CINTERNAL_INCLUDE_CINTERNAL_LW_MUTEX_RECURSIVE_H
