//
// repo:			cutils
// file:            replace_function_sys.h
// path:			include/cutils/replace_function_sys.h
// created on:		2023 Mar 16
// created by:		Davit Kalantaryan (davit.kalantaryan@desy.de)
//

#ifndef CUTILS_INCLUDE_CUTILS_REPLACE_FUNCTION_SYS_H
#define CUTILS_INCLUDE_CUTILS_REPLACE_FUNCTION_SYS_H

#include <cutils/export_symbols.h>
#include <cutils/replace_function.h>

#ifdef _WIN32

#include <cinternal/disable_compiler_warnings.h>
#include <WinSock2.h>
#include <WS2tcpip.h>
#include <Windows.h>
#include <cinternal/undisable_compiler_warnings.h>

CPPUTILS_BEGIN_C



CUTILS_EXPORT void CInternalReplaceFunctionsForModule(HMODULE a_hModule, size_t a_count, struct SCInternalReplaceFunctionData* a_replaceData);



CPPUTILS_END_C


#endif  //  #ifdef _WIN32


#endif  // #ifndef CUTILS_INCLUDE_CUTILS_REPLACE_FUNCTION_SYS_H
