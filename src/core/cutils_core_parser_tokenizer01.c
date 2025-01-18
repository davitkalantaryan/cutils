//
// repo:			cutils
// file:            cutils_core_parser_tokenizer01.c
// path:			src/core/cutils_core_parser_tokenizer01.c
// created on:		2023 Mar 16
// created by:		Davit Kalantaryan (davit.kalantaryan@desy.de)
//

#include <cutils/parser/tokenizer01.h>
#include <cinternal/disable_compiler_warnings.h>
#include <string.h>
#include <stddef.h>
#include <cinternal/undisable_compiler_warnings.h>

CPPUTILS_BEGIN_C


CUTILS_EXPORT int CInternalTokenizer01a(char* CPPUTILS_ARG_NONULL a_pcBuffer, char a_delimeter, TypeCinternalTokenizer01a CPPUTILS_ARG_NONULL a_clbk, void* a_clbkData)
{
	int nRet = -1;
	ptrdiff_t strLen;
	char *pcTemp, *pcNext;

	pcNext = a_pcBuffer;
	pcTemp = strchr(pcNext, a_delimeter);
	while (pcTemp) {
		strLen = (pcTemp - pcNext);
		if (strLen > 0) {
			*pcTemp = 0;
			nRet = (*a_clbk)(a_clbkData, pcNext);
			if (nRet) {
				return nRet;
			}  //  if (nRet) {
		}  //  if (strLen > 0) {
		pcNext = pcTemp + 1;
		pcTemp = strchr(pcNext, a_delimeter);
	}  //  while (pcTemp) {

	if (*pcNext) {
		// let's handle last library
		nRet = (*a_clbk)(a_clbkData, pcNext);
	}  // if (strlen(pcNext) > 0) {

	return nRet;
}


CPPUTILS_END_C
