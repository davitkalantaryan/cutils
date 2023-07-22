//
// repo:			cutils
// file:            cutils_core_intern_tokenizer01_common.c
// path:			src/intern/cutils_core_intern_tokenizer01_common.c
// created on:		2023 Mar 18
// created by:		Davit Kalantaryan (davit.kalantaryan@desy.de)
//


#include <private/cutils/parser/tokenizer01_common_p.h>
#include <cutils/parser/tokenizer01.h>
#include <cutils/loadfreelib_on_remote_process.h>
#include <stddef.h>
#include <stdio.h>


CPPUTILS_BEGIN_C


static int CinternalTokenizerForDllInject01b(void* a_clbkData, const char* a_cpcNextString) CPPUTILS_NOEXCEPT
{
	const int pid = (int)((size_t)a_clbkData);
    void* pModule = CInternalLoadLibOnRemoteProcessAndGetModule(pid, a_cpcNextString);
	if (pModule) {
		printf("libName:\"%s\", moduleAddr: %p\n", a_cpcNextString, pModule);
		return 0;
	}
	fprintf(stderr,"Unable to load library with the name:\"%s\" into the process %d\n", a_cpcNextString, pid);
	return -2;
}


CPPUTILS_DLL_PRIVATE int CInternalTokenizer01b(char* CPPUTILS_ARG_NONULL a_pcBuffer, int a_pid)
{
	return CInternalTokenizer01a(a_pcBuffer, ';', &CinternalTokenizerForDllInject01b,(void*)((size_t)a_pid));
}



CPPUTILS_END_C
