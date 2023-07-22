//
// file:            replace_function.h
// path:			include/cinternal/replace_function.h
// created on:		2023 Feb 25
// created by:		Davit Kalantaryan (davit.kalantaryan@desy.de)
//

#ifndef CINTERNAL_INCLUDE_CINTERNAL_REPLACE_FUNCTION_H
#define CINTERNAL_INCLUDE_CINTERNAL_REPLACE_FUNCTION_H

#include <cinternal/export_symbols.h>
#include <stddef.h>
#include <stdbool.h>

#if defined(_MSC_VER)
#pragma warning(disable: 4191)
#pragma warning(disable: 4232)
#else
#endif

#ifdef _WIN32


CPPUTILS_BEGIN_C


struct SCInternalReplaceFunctionData {
	const char* funcname;
	const void* newFuncAddress;
	const void* replaceIfAddressIs;  // In the case of NULL in any case case this will be replaced and old address will be put here
	bool bFound;
	bool reserved[sizeof(void*)-sizeof(bool)];
};


CINTERNAL_EXPORT void CInternalReplaceFunctions(size_t a_count, struct SCInternalReplaceFunctionData* a_replaceData);
CINTERNAL_EXPORT void CInternalReplaceFunctionsAllModules(size_t a_count, struct SCInternalReplaceFunctionData* a_replaceData);


CPPUTILS_END_C


#endif  //  #ifdef _WIN32


#endif  // #ifndef CINTERNAL_INCLUDE_CINTERNAL_REPLACE_FUNCTION_H
