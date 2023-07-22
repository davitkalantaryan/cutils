//
// repo:			cutils
// file:            tokenizer01.h
// path:			include/cinternal/parser/tokenizer01.h
// created on:		2023 Mar 16
// created by:		Davit Kalantaryan (davit.kalantaryan@desy.de)
//

#ifndef CUTILS_INCLUDE_CUTILS_PARSER_TOKENIZER01_H
#define CUTILS_INCLUDE_CUTILS_PARSER_TOKENIZER01_H


#include <cutils/export_symbols.h>


CPPUTILS_BEGIN_C


typedef int (*TypeCinternalTokenizer01a)(void* a_clbkData, const char* a_cpcNextString);

CUTILS_EXPORT int CInternalTokenizer01a(char* CPPUTILS_ARG_NONULL a_pcBuffer, char a_delimeter, TypeCinternalTokenizer01a CPPUTILS_ARG_NONULL a_clbk, void* a_clbkData);


CPPUTILS_END_C


#endif  //  #ifndef CUTILS_INCLUDE_CUTILS_PARSER_TOKENIZER01_H
