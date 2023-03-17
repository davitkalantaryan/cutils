//
// file:            cinternal_core_intern_tokenizer01_windows.c
// path:			src/intern/cinternal_core_intern_tokenizer01_windows.c
// created on:		2023 Mar 16
// created by:		Davit Kalantaryan (davit.kalantaryan@desy.de)
//


#include <private/cinternal/parser/tokenizer01_windows_p.h>
#include <cinternal/parser/tokenizer01.h>
#include <cinternal/load_lib_on_remote_process_sys.h>


CPPUTILS_BEGIN_C


static int CinternalTokenizerForWindowsDllInject01a(void* a_clbkData, const char* a_cpcNextString)
{
	const HANDLE hProcess = (HANDLE)a_clbkData;
	return CInternalLoadLibOnRemoteProcessSys(hProcess, a_cpcNextString)?0:-2;
}


CPPUTILS_DLL_PRIVATE int CInternalTokenizerWindows01a(char* CPPUTILS_ARG_NONULL a_pcBuffer, HANDLE a_hProcess)
{
	return CInternalTokenizer01a(a_pcBuffer, ';', &CinternalTokenizerForWindowsDllInject01a,a_hProcess);
}



CPPUTILS_END_C
