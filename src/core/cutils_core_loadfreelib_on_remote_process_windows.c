//
// repo:			cutils
// file:            cutils_core_replace_function_windows.c
// path:			src/core/windows/cutils_core_replace_function_windows.c
// created on:		2023 Mar 08
// created by:		Davit Kalantaryan (davit.kalantaryan@desy.de)
//

#include <cinternal/internal_header.h>

#ifdef _WIN32

#include <cutils/loadfreelib_on_remote_process_sys.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <cinternal/disable_compiler_warnings.h>
#include <Psapi.h>
#include <cinternal/undisable_compiler_warnings.h>


CPPUTILS_BEGIN_C


static inline DWORD CInternalLoadLibOnRemoteProcessSysInline(HANDLE a_hProcess, const char* a_libraryName) {
	DWORD dwThreadId;
	HANDLE hThread;
	SIZE_T szWritten;
	void* pRemoteMem;
	const size_t cunDllNameLenPlus1 = strlen(a_libraryName) + 1;


	pRemoteMem = VirtualAllocEx(a_hProcess, CPPUTILS_NULL, CPPUTILS_STATIC_CAST(SIZE_T, cunDllNameLenPlus1), MEM_COMMIT, PAGE_READWRITE);
	if (!pRemoteMem) {
		return 0;
	}

	if (!WriteProcessMemory(a_hProcess, pRemoteMem, a_libraryName, CPPUTILS_STATIC_CAST(SIZE_T, cunDllNameLenPlus1), &szWritten)) {
		VirtualFreeEx(a_hProcess, pRemoteMem, 0, MEM_RELEASE);
		return 0;
	}

	hThread = CreateRemoteThread(a_hProcess, CPPUTILS_NULL, 0, (LPTHREAD_START_ROUTINE)((void*)LoadLibraryA), pRemoteMem, 0, &dwThreadId);
	if (!hThread) {
		VirtualFreeEx(a_hProcess, pRemoteMem, 0, MEM_RELEASE);
		return 0;
	}

	WaitForSingleObject(hThread, INFINITE);
	GetExitCodeThread(hThread, &dwThreadId);
	CloseHandle(hThread);
	VirtualFreeEx(a_hProcess, pRemoteMem, 0, MEM_RELEASE);

	return dwThreadId;  // return code is somehow HMODULE of LoadLibrary
}


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

	return dwThreadId?true:false;
}


static inline const char* FileNameFromFilePathInline(const char* a_path) {
	const char* cpcRet = strrchr(a_path, '\\');
	if (cpcRet) {
		return cpcRet + 1;
	}
	else {
		cpcRet = strrchr(a_path, '/');
		if (cpcRet) { return cpcRet + 1; }
	}

	return a_path;
}


CUTILS_EXPORT bool CInternalLoadLibOnRemoteProcessSys(HANDLE a_hProcess, const char* a_libraryName)
{
	return CInternalLoadLibOnRemoteProcessSysInline(a_hProcess, a_libraryName) ? true : false;
}


CUTILS_EXPORT HMODULE CInternalLoadLibOnRemoteProcessAndGetModuleSys(HANDLE a_hProcess, const char* a_libraryName)
{
	char vcModuleNameBuff[1024];
	BOOL secondEnumRes;
	DWORD dwHmoduleOnremoteLow;
	DWORD i, cbNeeded;
	HMODULE hModule;
	HMODULE* pMods;
	const DWORD dwThreadId = CInternalLoadLibOnRemoteProcessSysInline(a_hProcess,a_libraryName);
	if (!dwThreadId) {
		return CPPUTILS_STATIC_CAST(HMODULE,0);
	}

	if (!EnumProcessModules(a_hProcess, &hModule, 0, &cbNeeded)){
		return CPPUTILS_STATIC_CAST(HMODULE, 0);
	}

	pMods = CPPUTILS_STATIC_CAST(HMODULE*, malloc(CPPUTILS_STATIC_CAST(size_t, cbNeeded)));
	if (!pMods) {
		return CPPUTILS_STATIC_CAST(HMODULE, 0);
	}

	
	secondEnumRes = EnumProcessModules(a_hProcess, pMods, cbNeeded, &cbNeeded);
	assert(secondEnumRes);
	cbNeeded /= sizeof(HMODULE);

	for (i = 0; i < cbNeeded; ++i) {
		dwHmoduleOnremoteLow = (DWORD)((size_t)pMods[i]);
		if (dwHmoduleOnremoteLow == dwThreadId) {
			if (GetModuleFileNameExA(a_hProcess, pMods[i], vcModuleNameBuff, 1023) > 0) {
				if (   (_strcmpi(a_libraryName, vcModuleNameBuff) == 0) ||
					   (_strcmpi(a_libraryName, FileNameFromFilePathInline(vcModuleNameBuff)) == 0)   ) 
				{
					hModule = pMods[i];
					free(pMods);
					return hModule;
				}
			}  //  if (GetModuleFileNameExA(a_hProcess, pMods[i], vcModuleNameBuff, 1023) > 0) {
		}  //  if (dwHmoduleOnremoteLow == dwThreadId) {
	}  //  for (i = 0; i < cbNeeded; ++i) {

	free(pMods);
	return CPPUTILS_STATIC_CAST(HMODULE, 0);
}


CUTILS_EXPORT bool CInternalLoadLibOnRemoteProcess(int a_pid, const char* a_libraryName)
{
	bool bRet;
	const HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, (DWORD)a_pid);
	if (!hProcess) {
		return false;
	}
	bRet = CInternalLoadLibOnRemoteProcessSysInline(hProcess, a_libraryName) ? true : false;
	CloseHandle(hProcess);
	return bRet;
}


CUTILS_EXPORT void* CInternalLoadLibOnRemoteProcessAndGetModule(int a_pid, const char* a_libraryName)
{
	void* pRet;
	const HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, (DWORD)a_pid);
	if (!hProcess) {
		return CPPUTILS_NULL;
	}
	pRet = CInternalLoadLibOnRemoteProcessAndGetModuleSys(hProcess, a_libraryName);
	CloseHandle(hProcess);
	return pRet;
}


CUTILS_EXPORT bool CInternalFreeLibOnRemoteProcessByName(int a_pid, const char* a_libraryName)
{
	bool bRet;
	const HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, (DWORD)a_pid);
	if (!hProcess) {
		return false;
	}
	bRet = CInternalFreeLibOnRemoteProcessSys(hProcess, a_libraryName);
	CloseHandle(hProcess);
	return bRet;
}


CUTILS_EXPORT bool CInternalFreeLibOnRemoteProcessByHandle(int a_pid, void* a_libraryHandle)
{
	bool bRet;
	const HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, (DWORD)a_pid);
	if (!hProcess) {
		return false;
	}
	bRet = CInternalFreeLibOnRemoteProcessSysInline(hProcess, (HMODULE)a_libraryHandle);
	CloseHandle(hProcess);
	return bRet;
}


CUTILS_EXPORT bool CInternalFreeLibOnRemoteProcessByModuleSys(HANDLE a_hProcess, HMODULE a_libraryModule)
{
	return CInternalFreeLibOnRemoteProcessSysInline(a_hProcess, a_libraryModule);
}


CUTILS_EXPORT bool CInternalFreeLibOnRemoteProcessSys(HANDLE a_hProcess, const char* a_libraryName)
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

	pMods = (HMODULE*)HeapAlloc(curProcHeap, 0, (SIZE_T)cbNeededIn);
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
