//
// file:            cinternal_core_replace_function_windows.c
// path:			src/core/windows/cinternal_core_replace_function_windows.c
// created on:		2023 Mar 08
// created by:		Davit Kalantaryan (davit.kalantaryan@desy.de)
//


#include <cinternal/internal_header.h>

#ifdef _WIN32

#include <cinternal/freelib_on_remote_process_sys.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <cinternal/disable_compiler_warnings.h>
#include <Psapi.h>


CPPUTILS_BEGIN_C


static inline bool CInternalFreeLibOnRemoteProcessSysInline(HANDLE a_hProcess, HMODULE a_libraryModule) {
	DWORD dwThreadId;
	HANDLE hThread;

	hThread = CreateRemoteThread(a_hProcess, CPPUTILS_NULL, 0, (LPTHREAD_START_ROUTINE)((void*)FreeLibrary), a_libraryModule, 0, &dwThreadId);
	if (!hThread) {
		return false;
	}

	WaitForSingleObject(hThread, INFINITE);
	GetExitCodeThread(hThread, &dwThreadId);
	CloseHandle(hThread);

	return true;
}


static inline const char* FileNameFromFilePathInline(const char* a_path) {
	const char* cpcRet = strrchr(a_path, '\\');
	if (cpcRet) {
		return cpcRet+1;
	}
	else {
		cpcRet = strrchr(a_path, '/');
		if (cpcRet) {return cpcRet+1;}
	}

	return a_path;
}


CINTERNAL_EXPORT bool CInternalFreeLibOnRemoteProcessByModuleSys(HANDLE a_hProcess, HMODULE a_libraryModule)
{
	return CInternalFreeLibOnRemoteProcessSysInline(a_hProcess, a_libraryModule);
}


CINTERNAL_EXPORT bool CInternalFreeLibOnRemoteProcessSys(HANDLE a_hProcess, const char* a_libraryName)
{
	bool bRet = false;
	char vcModulePath[1024];
	DWORD dwNameLenRet;
	DWORD dwFinalSize, i;
	DWORD cbNeededIn, cbNeededOut;
	HMODULE hMod;
	HMODULE* pMods;
	const HANDLE curProcHeap = GetProcessHeap();

	if (!EnumProcessModules(a_hProcess, &hMod, 0, &cbNeededIn)) {
		return false;
	}

	pMods = HeapAlloc(curProcHeap, 0, (SIZE_T)cbNeededIn);
	if (!pMods) {
		return false;
	}

	if (!EnumProcessModules(a_hProcess, pMods, cbNeededIn, &cbNeededOut)) {
		return false;
	}

	dwFinalSize = (cbNeededIn < cbNeededOut) ? (cbNeededIn / sizeof(HMODULE)) : (cbNeededOut / sizeof(HMODULE));

	for (i = 0; i < dwFinalSize; ++i) {
		dwNameLenRet = GetModuleFileNameExA(a_hProcess, pMods[i], vcModulePath, 1023);
		if ((dwNameLenRet > 0) && (dwNameLenRet < 1023)) {
			if (_stricmp(a_libraryName, FileNameFromFilePathInline(vcModulePath)) == 0) {
				bRet = CInternalFreeLibOnRemoteProcessSysInline(a_hProcess, pMods[i]);
				break;
			}  //  if (stricmp(a_libraryName, vcModulePath) == 0) {
		}  //  if ((dwNameLenRet > 0) && (dwNameLenRet < 1023)) {
	}  //  for (i = 0; i < dwFinalSize; ++i) {

	HeapFree(curProcHeap, 0, pMods);
	return bRet;
}


CPPUTILS_END_C


#endif  //  #ifdef _WIN32
