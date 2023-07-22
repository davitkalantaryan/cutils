//
// repo:			cutils
// file:			cutils_core_lw_mutex_recursive.c
// path:			src/core/cutils_core_lw_mutex_recursive.c
// created on:		2023 Jun 20
// created by:		Davit Kalantaryan (davit.kalantaryan@desy.de)
//

#include <cutils/lw_mutex_recursive.h>

CPPUTILS_BEGIN_C


CUTILS_EXPORT int cinternal_lw_recursive_mutex_create(cinternal_lw_recursive_mutex_t* a_pMutex)
{
#ifdef _WIN32
	InitializeCriticalSection(a_pMutex);
	return 0;
#else
	int nRet;
	pthread_mutexattr_t attr;
	if ( (nRet = pthread_mutexattr_init(&attr)) ) {
		return nRet;
	}
	pthread_mutexattr_settype(&attr, PTHREAD_MUTEX_RECURSIVE);

	nRet = pthread_mutex_init(a_pMutex, &attr);
	pthread_mutexattr_destroy(&attr);
	return nRet;
#endif
}


CUTILS_EXPORT void cinternal_lw_recursive_mutex_destroy(cinternal_lw_recursive_mutex_t* a_pMutex)
{
#ifdef _WIN32
	DeleteCriticalSection(a_pMutex);
#else
	pthread_mutex_destroy(a_pMutex);
#endif
}


CUTILS_EXPORT int cinternal_lw_recursive_mutex_lock(cinternal_lw_recursive_mutex_t* a_pMutex)
{
#ifdef _WIN32
	EnterCriticalSection(a_pMutex);
	return 0;
#else
	return pthread_mutex_lock(a_pMutex);
#endif
}


CUTILS_EXPORT void cinternal_lw_recursive_mutex_unlock(cinternal_lw_recursive_mutex_t* a_pMutex)
{
#ifdef _WIN32
	LeaveCriticalSection(a_pMutex);
#else
	pthread_mutex_unlock(a_pMutex);
#endif
}


CPPUTILS_END_C
