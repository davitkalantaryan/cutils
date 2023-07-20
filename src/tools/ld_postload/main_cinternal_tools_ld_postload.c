//
// file:            main_cinternal_core_windows_ld_postload.c
// path:			src/tools/windows_ld_postload/main_cinternal_core_windows_ld_postload.c
// created on:		2023 Mar 16
// created by:		Davit Kalantaryan (davit.kalantaryan@desy.de)
//


//#define CINTERNAL_LD_POSTLOAD_WAIT_FOR_DEBUGGER		1

#include <cinternal/export_symbols.h>
#include <cinternal/loadfreelib_on_remote_process.h>
#include <cinternal/parser/argparser01.h>
#include <cinternal/list/dllist.h>
#include <private/cinternal/parser/tokenizer01_common_p.h>
#include <stddef.h>
#include <cinternal/disable_compiler_warnings.h>
#ifdef _WIN32
#include <WinSock2.h>
#include <WS2tcpip.h>
#include <Windows.h>
#include <stdlib.h>
#include <stdio.h>
static char* GetEnvironmentVariableACint(const char* a_cpcName, char* a_pBuffer, size_t a_bufLen, size_t* a_pBytesReturned)
{
	*a_pBytesReturned = (size_t)GetEnvironmentVariableA(a_cpcName, a_pBuffer, (DWORD)a_bufLen);
	return a_pBuffer;
}
#else
#ifndef _GNU_SOURCE
#define _GNU_SOURCE
#endif
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
static char* GetEnvironmentVariableACint(const char* a_cpcName, char* a_pBuffer, size_t a_bufLen, size_t* a_pBytesReturned)
{
    //char* pRet = secure_getenv(a_cpcName);
    char* pRet = getenv(a_cpcName);
	if (!pRet) {
		*a_pBytesReturned = 0;
		return CPPUTILS_NULL;
	}

	(void)a_pBuffer;
	*a_pBytesReturned = strlen(pRet);
	if ((*a_pBytesReturned) > 0) {
		(*a_pBytesReturned) = a_bufLen - 1;
	}

	return pRet;
}
#endif
#include <cinternal/undisable_compiler_warnings.h>



int main(int a_argc, char* a_argv[])
{
	int nArgc = a_argc - 1;
	char** ppcArgv = a_argv + 1;
	char** ppcArgvTmp;
	int nArgcTmp, nArgcTmpTmp;
	char* pcEnvVar;
	size_t szEnvLen;
	char vcLdPpostloadEnvBuffer[1024];
	const char* cpcNextArg;
	CinternalDLList_t aList;
	CinternalDLListItem_t pItem;
	int nPid = 0;
	int nRet;

#if defined(CINTERNAL_LD_POSTLOAD_WAIT_FOR_DEBUGGER)
	fprintf(stdout, "Press any key then enter to continue "); fflush(stdout);
	nRet = getchar();
	CPPUTILS_STATIC_CAST(void, nRet);
	//while (!IsDebuggerPresent()) {
	//	Sleep(1000);
	//}
#endif

	aList = CInternalDLListCreate();
	if (!aList) {
		fprintf(stderr,"Unable create a list\n");
		return 1;
	}

	cpcNextArg = CInternalFindEndTakeArg(&nArgc, ppcArgv, "---pid", &nRet, true);
	if (cpcNextArg) {
		nPid = atoi(cpcNextArg);
	}

	ppcArgvTmp = ppcArgv;
	nArgcTmp = nArgc;

	while (nArgcTmp > 0) {
		nArgcTmpTmp = nArgcTmp;
		cpcNextArg = CInternalFindEndTakeArg(&nArgcTmp, ppcArgvTmp, "--libs", &nRet, true);
		if (cpcNextArg) {
			CInternalDLListAddDataToFront(aList, cpcNextArg);
			nArgc -= (nArgcTmpTmp - nArgcTmp);
			ppcArgvTmp += nRet;
			nArgcTmp -= nRet;
		}
		else {
			break;
		}
	}  //  while (nArgc > 0) {


	if (nPid < 1) {
		if (nArgc < 1) {
			CInternalDLListDestroy(aList);
			fprintf(stderr, "PID of running application to inject DLL is not specified!\n");
			return 1;
		}
		nPid = atoi(ppcArgv[0]);
		if (nPid < 1) {
			CInternalDLListDestroy(aList);
			fprintf(stderr, "PID of running application to inject DLL is not specified!\n");
			return 1;
		}
	}  //  if (dwPid < 1) {

	pItem = CInternalDLListFirstItem(aList);
	while (pItem) {
		CInternalTokenizer01b((char*)(pItem->data), nPid);
		pItem = CInternalDLListItemFromDLListIterator(CInternalDLListIteratorFromDLListItem(pItem)->next);
	}
	CInternalDLListDestroy(aList);

	pcEnvVar = GetEnvironmentVariableACint("LD_POSTLOAD", vcLdPpostloadEnvBuffer, 1023,&szEnvLen);
	if ((szEnvLen > 0) && (szEnvLen < 1023)) {
        CInternalTokenizer01b(pcEnvVar, nPid);
	}  //  if ((szEnvLen > 0) && (szEnvLen < 1023)) {

	return 0;
}
