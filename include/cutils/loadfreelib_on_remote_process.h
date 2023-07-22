//
// file:            freelib_on_remote_process.h
// path:			include/cinternal/freelib_on_remote_process.h
// created on:		2023 Mar 18
// created by:		Davit Kalantaryan (davit.kalantaryan@desy.de)
//

#ifndef CINTERNAL_INCLUDE_CINTERNAL_FREELIB_ON_REMOTE_PROCESS_H
#define CINTERNAL_INCLUDE_CINTERNAL_FREELIB_ON_REMOTE_PROCESS_H

#include <cinternal/export_symbols.h>
#include <stdbool.h>


CPPUTILS_BEGIN_C


CINTERNAL_EXPORT bool	CInternalLoadLibOnRemoteProcess(int a_pid, const char* a_libraryName);
CINTERNAL_EXPORT void*  CInternalLoadLibOnRemoteProcessAndGetModule(int a_pid, const char* a_libraryName);
CINTERNAL_EXPORT bool   CInternalFreeLibOnRemoteProcessByName(int a_pid, const char* a_libraryName);
CINTERNAL_EXPORT bool   CInternalFreeLibOnRemoteProcessByHandle(int a_pid, void* a_libraryHandle);


CPPUTILS_END_C


#endif  // #ifndef CINTERNAL_INCLUDE_CINTERNAL_FREELIB_ON_REMOTE_PROCESS_H
