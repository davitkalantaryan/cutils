//
// file:            argparser01.h
// path:			include/cinternal/parser/argparser01.h
// created on:		2023 Mar 16
// created by:		Davit Kalantaryan (davit.kalantaryan@desy.de)
//

#ifndef CINTERNAL_INCLUDE_CINTERNAL_PARSER_ARGPARSER01_H
#define CINTERNAL_INCLUDE_CINTERNAL_PARSER_ARGPARSER01_H


#include <cinternal/export_symbols.h>
#include <stdbool.h>


CPPUTILS_BEGIN_C


CINTERNAL_EXPORT const char* CInternalFindEndTakeArg(
	int* CPPUTILS_ARG_NONULL a_argc_p, char** CPPUTILS_ARG_NONULL a_argv, 
	const char* CPPUTILS_ARG_NONULL a_key, int* a_pLastArg, bool a_hasArg);


CPPUTILS_END_C


#endif  //  #ifndef CINTERNAL_INCLUDE_CINTERNAL_PARSER_ARGPARSER01_H
