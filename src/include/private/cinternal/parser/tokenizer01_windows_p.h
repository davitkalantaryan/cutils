//
// file:            tokenizer01_windows_p.h
// path:			src/include/private/cinternal/parser/tokenizer01_windows_p.h
// created on:		2023 Mar 16
// created by:		Davit Kalantaryan (davit.kalantaryan@desy.de)
//

#ifndef CINTERNAL_SRC_INCLUDE_PRIVATE_CINTERNAL_PARSER_TOKENIZER01_WINDOWS_P_H
#define CINTERNAL_SRC_INCLUDE_PRIVATE_CINTERNAL_PARSER_TOKENIZER01_WINDOWS_P_H


#include <cinternal/internal_header.h>
#include <cinternal/disable_compiler_warnings.h>
#include <WinSock2.h>
#include <WS2tcpip.h>
#include <Windows.h>


CPPUTILS_BEGIN_C


CPPUTILS_DLL_PRIVATE int CInternalTokenizerWindows01a(char* CPPUTILS_ARG_NONULL a_pcBuffer, HANDLE a_hProcess);


CPPUTILS_END_C


#endif  //  #ifndef CINTERNAL_SRC_INCLUDE_PRIVATE_CINTERNAL_PARSER_TOKENIZER01_WINDOWS_P_H
