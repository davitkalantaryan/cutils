//
// repo:			cutils
// file:            cutils_core_intern_tokenizer02_windows.c
// path:			src/intern/cutils_core_intern_tokenizer02_windows.c
// created on:		2023 Mar 17
// created by:		Davit Kalantaryan (davit.kalantaryan@desy.de)
//


#include <private/cutils/parser/tokenizer02_windows_p.h>
#include <cutils/parser/tokenizer01.h>
#include <cutils/loadfreelib_on_remote_process_sys.h>


CPPUTILS_BEGIN_C


static int CinternalTokenizerForWindowsDllUnload02a(void* a_clbkData, const char* a_cpcNextString)
{
	const HANDLE hProcess = (HANDLE)a_clbkData;
	return CInternalFreeLibOnRemoteProcessSys(hProcess, a_cpcNextString)?0:-2;
}


CPPUTILS_DLL_PRIVATE int CInternalTokenizerWindows02a(char* CPPUTILS_ARG_NONULL a_pcBuffer, HANDLE a_hProcess)
{
	return CInternalTokenizer01a(a_pcBuffer, ';', &CinternalTokenizerForWindowsDllUnload02a,a_hProcess);
}



CPPUTILS_END_C
