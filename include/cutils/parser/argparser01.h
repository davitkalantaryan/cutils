//
// repo:			cutils
// file:            argparser01.h
// path:			include/cutils/parser/argparser01.h
// created on:		2023 Mar 16
// created by:		Davit Kalantaryan (davit.kalantaryan@desy.de)
//

#ifndef CUTILS_INCLUDE_CUTILS_PARSER_ARGPARSER01_H
#define CUTILS_INCLUDE_CUTILS_PARSER_ARGPARSER01_H

#include <cutils/export_symbols.h>
#include <stdbool.h>


CPPUTILS_BEGIN_C


CUTILS_EXPORT const char* CInternalFindEndTakeArg(
	int* CPPUTILS_ARG_NONULL a_argc_p, char** CPPUTILS_ARG_NONULL a_argv, 
	const char* CPPUTILS_ARG_NONULL a_key, int* a_pLastArg, bool a_hasArg);


CPPUTILS_END_C


#endif  //  #ifndef CUTILS_INCLUDE_CUTILS_PARSER_ARGPARSER01_H
