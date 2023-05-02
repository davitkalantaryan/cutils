//
// file:            main_freelib_on_remote_proc_by_handle.c
// path:			src/tools/freelib_on_remote_proc_by_handle/main_freelib_on_remote_proc_by_handle.c
// created on:		2023 Mar 18
// created by:		Davit Kalantaryan (davit.kalantaryan@desy.de)
//


//#define CINTERNAL_FREE_LIB_ON_REMOTE_BY_HANDLE_WAIT_FOR_DEBUGGER

#include <cinternal/export_symbols.h>
#include <cinternal/parser/argparser01.h>
#include <cinternal/loadfreelib_on_remote_process.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stddef.h>


static inline size_t GetAddressFromStringInline(const char* a_cpcStr) {
	int nBase = 10;
	size_t szRet;
	char* pcEndPtr = CPPUTILS_NULL;
	const char* cpcTerm = strchr(a_cpcStr, 'X');
	if (cpcTerm) {
		nBase = 16;
	}
	else {
		cpcTerm = strchr(a_cpcStr, 'x');
		if (cpcTerm) {
			nBase = 16;
		}
	}

	szRet = CPPUTILS_STATIC_CAST(size_t,strtoll(a_cpcStr, &pcEndPtr, nBase));
	if (pcEndPtr == a_cpcStr) {
		return 0;
	}

	return szRet;
}


int main(int a_argc, char* a_argv[])
{
	int nArgc = a_argc - 1;
	char** ppcArgv = a_argv + 1;
	int nRet, nPid = 0;
	void* pModuleHandleAddress = CPPUTILS_NULL;
	const char* cpcNextArg;


#if defined(CINTERNAL_FREE_LIB_ON_REMOTE_BY_HANDLE_WAIT_FOR_DEBUGGER)
	fprintf(stdout, "Press any key then enter to continue "); fflush(stdout);
	nRet = getchar();
	CPPUTILS_STATIC_CAST(void, nRet);
	//while (!IsDebuggerPresent()) {
	//	Sleep(1000);
	//}
#endif

	cpcNextArg = CInternalFindEndTakeArg(&nArgc, ppcArgv, "--lib", &nRet, true);
	if (cpcNextArg) {
		pModuleHandleAddress = CPPUTILS_REINTERPRET_CAST(void*,GetAddressFromStringInline(cpcNextArg));
	}

	cpcNextArg = CInternalFindEndTakeArg(&nArgc, ppcArgv, "--pid", &nRet, true);
	if (cpcNextArg) {
		nPid = CPPUTILS_STATIC_CAST(int,GetAddressFromStringInline(cpcNextArg));
	}


	if (nPid < 1) {
		if (nArgc < 1) {
			fprintf(stderr, "PID of process for freeing library from it is not provided\n");
			return 1;
		}
		nPid = CPPUTILS_STATIC_CAST(int, GetAddressFromStringInline(ppcArgv[0]));
		if (nPid < 1) {
			fprintf(stderr, "PID of process for freeing library from it is not provided\n");
			return 1;
		}
		if (--nArgc) {
			memmove(&ppcArgv[0],&ppcArgv[1],CPPUTILS_STATIC_CAST(size_t, nArgc)*sizeof(char*));
		}
	}  //  if (nPid < 1) {

	if (!pModuleHandleAddress) {
		if (nArgc < 1) {
			fprintf(stderr, "Module address to unload from remote process is not provided\n");
			return 1;
		}
		pModuleHandleAddress = CPPUTILS_REINTERPRET_CAST(void*, GetAddressFromStringInline(ppcArgv[0]));
		if (!pModuleHandleAddress) {
			fprintf(stderr, "Module address to unload from remote process is not provided\n");
			return 1;
		}
	}  //  if (nPid < 1) {


	if (!CInternalFreeLibOnRemoteProcessByHandle(nPid, pModuleHandleAddress)) {
		fprintf(stderr, "Unable unload module %p from the peocess with the pid %d\n", pModuleHandleAddress, nPid);
		return 1;
	}

	return 0;
}
