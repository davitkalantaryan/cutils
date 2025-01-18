//
// repo:			cutils
// file:            freelib_on_remote_process.h
// path:			include/cutils/freelib_on_remote_process.h
// created on:		2023 Mar 18
// created by:		Davit Kalantaryan (davit.kalantaryan@desy.de)
//

#ifndef CUTILS_INCLUDE_CUTILS_FREELIB_ON_REMOTE_PROCESS_H
#define CUTILS_INCLUDE_CUTILS_FREELIB_ON_REMOTE_PROCESS_H

#include <cutils/export_symbols.h>
#include <cinternal/disable_compiler_warnings.h>
#include <stdbool.h>
#include <cinternal/undisable_compiler_warnings.h>


CPPUTILS_BEGIN_C


CUTILS_EXPORT bool	CInternalLoadLibOnRemoteProcess(int a_pid, const char* a_libraryName);
CUTILS_EXPORT void*  CInternalLoadLibOnRemoteProcessAndGetModule(int a_pid, const char* a_libraryName);
CUTILS_EXPORT bool   CInternalFreeLibOnRemoteProcessByName(int a_pid, const char* a_libraryName);
CUTILS_EXPORT bool   CInternalFreeLibOnRemoteProcessByHandle(int a_pid, void* a_libraryHandle);


CPPUTILS_END_C


#endif  // #ifndef CUTILS_INCLUDE_CUTILS_FREELIB_ON_REMOTE_PROCESS_H
