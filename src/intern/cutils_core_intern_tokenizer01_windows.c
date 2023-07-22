//
// repo:			cutils
// file:            cutils_core_intern_tokenizer01_windows.c
// path:			src/intern/cutils_core_intern_tokenizer01_windows.c
// created on:		2023 Mar 16
// created by:		Davit Kalantaryan (davit.kalantaryan@desy.de)
//

#include <private/cutils/parser/tokenizer01_windows_p.h>
#include <cutils/parser/tokenizer01.h>
#include <cutils/loadfreelib_on_remote_process_sys.h>
#include <stdio.h>


CPPUTILS_BEGIN_C


static int CinternalTokenizerForWindowsDllInject01a(void* a_clbkData, const char* a_cpcNextString) CPPUTILS_NOEXCEPT
{
	const HANDLE hProcess = (HANDLE)a_clbkData;
	if (CInternalLoadLibOnRemoteProcessSys(hProcess, a_cpcNextString)) {
		return 0;
	}
	fprintf(stderr, "Unable to load library with the name:\"%s\"\n", a_cpcNextString);
	return -2;
}


CPPUTILS_DLL_PRIVATE int CInternalTokenizerWindows01a(char* CPPUTILS_ARG_NONULL a_pcBuffer, HANDLE a_hProcess)
{
	return CInternalTokenizer01a(a_pcBuffer, ';', &CinternalTokenizerForWindowsDllInject01a,a_hProcess);
}



CPPUTILS_END_C
