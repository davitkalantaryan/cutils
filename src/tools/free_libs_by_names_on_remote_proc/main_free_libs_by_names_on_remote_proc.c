//
// file:            main_free_library_by_name_on_remote.c
// path:			src/tools/free_libs_by_names_on_remote_proc/main_free_library_by_name_on_remote.c
// created on:		2023 Mar 17
// created by:		Davit Kalantaryan (davit.kalantaryan@desy.de)
//

//#define CINTERNAL_WINDOWS_LD_POSTFREE_WAIT_FOR_DEBUGGER

#include <cinternal/export_symbols.h>
#include <cinternal/load_lib_on_remote_process_sys.h>
#include <cinternal/parser/argparser01.h>
#include <cinternal/list/llist.h>
#include <private/cinternal/parser/tokenizer02_windows_p.h>
#include <stdlib.h>
#include <stdio.h>


int main(int a_argc, char* a_argv[])
{
	int nArgc = a_argc - 1;
	char** ppcArgv = a_argv + 1;
	char** ppcArgvTmp;
	int nArgcTmp, nArgcTmpTmp;
	DWORD dwEnvLen;
	char vcLdPpostloadEnvBuffer[1024];
	const char* cpcNextArg;
	CinternalLList_t aList;
	CInternalLListIterator listIter;
	HANDLE hProcess;
	DWORD dwPid = 0;
	int nRet;

#if defined(CINTERNAL_WINDOWS_LD_POSTFREE_WAIT_FOR_DEBUGGER)
	fprintf(stdout, "Press any key then enter to continue "); fflush(stdout);
	nRet = getchar();
	CPPUTILS_STATIC_CAST(void, nRet);
	//while (!IsDebuggerPresent()) {
	//	Sleep(1000);
	//}
#endif

	aList = CInternalLListCreate();
	if (!aList) {
		fprintf(stderr, "Unable create a list\n");
		return 1;
	}

	cpcNextArg = CInternalFindEndTakeArg(&nArgc, ppcArgv, "---pid", &nRet, true);
	if (cpcNextArg) {
		dwPid = CPPUTILS_STATIC_CAST(DWORD, atoi(cpcNextArg));
	}

	ppcArgvTmp = ppcArgv;
	nArgcTmp = nArgc;

	while (nArgcTmp > 0) {
		nArgcTmpTmp = nArgcTmp;
		cpcNextArg = CInternalFindEndTakeArg(&nArgcTmp, ppcArgvTmp, "--libs", &nRet, true);
		if (cpcNextArg) {
			CInternalLListAddDataToFront(aList, cpcNextArg);
			nArgc -= (nArgcTmpTmp - nArgcTmp);
			ppcArgvTmp += nRet;
			nArgcTmp -= nRet;
		}
		else {
			break;
		}
	}  //  while (nArgc > 0) {


	if (dwPid < 1) {
		if (nArgc < 1) {
			CInternalLListDestroy(aList);
			fprintf(stderr, "PID of running application to inject DLL is not specified!\n");
			return 1;
		}
		dwPid = CPPUTILS_STATIC_CAST(DWORD, atoi(ppcArgv[0]));
		if (dwPid < 1) {
			CInternalLListDestroy(aList);
			fprintf(stderr, "PID of running application to inject DLL is not specified!\n");
			return 1;
		}
	}  //  if (dwPid < 1) {

	hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, dwPid);
	if (!hProcess) {
		CInternalLListDestroy(aList);
		fprintf(stderr, "Unable to access process with the PID: %d!\n", (int)dwPid);
		return 1;
	}

	listIter = CInternalLListFirstItem(aList);
	while (listIter) {
		CInternalTokenizerWindows02a((char*)(listIter->data), hProcess);
		listIter = listIter->nextInList;
	}
	CInternalLListDestroy(aList);

	dwEnvLen = GetEnvironmentVariableA("LD_POSTFREE", vcLdPpostloadEnvBuffer, 1023);
	if ((dwEnvLen > 0) && (dwEnvLen < 1023)) {
		CInternalTokenizerWindows02a(vcLdPpostloadEnvBuffer, hProcess);
	}  //  if ((dwEnvLen > 0) && (dwEnvLen < 1023)) {

	CloseHandle(hProcess);
	return 0;
}
