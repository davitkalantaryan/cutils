//
// file:            cinternal_core_replace_function_windows.c
// path:			src/core/windows/cinternal_core_replace_function_windows.c
// created on:		2023 Mar 08
// created by:		Davit Kalantaryan (davit.kalantaryan@desy.de)
//


#include <cinternal/internal_header.h>

#ifdef _WIN32

#include <cinternal/load_lib_on_remote_process_sys.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <cinternal/disable_compiler_warnings.h>
#include <Psapi.h>


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


CINTERNAL_EXPORT bool CInternalLoadLibOnRemoteProcessSys(HANDLE a_hProcess, const char* a_libraryName)
{
	return CInternalLoadLibOnRemoteProcessSysInline(a_hProcess, a_libraryName) ? true : false;
}


CINTERNAL_EXPORT HMODULE CInternalLoadLibOnRemoteProcessAnGetModuleSys(HANDLE a_hProcess, const char* a_libraryName)
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
				if (_strcmpi(a_libraryName, vcModuleNameBuff) == 0) {
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


CINTERNAL_EXPORT bool CInternalFreeLibOnRemoteProcessSys(HANDLE a_hProcess, HMODULE a_module)
{
	SIZE_T szWritten;
	DWORD dwThreadId;
	HANDLE hThread;
	void* pRemoteMem;
	const SIZE_T cunSizeToAlloc = sizeof(HMODULE);

	pRemoteMem = VirtualAllocEx(a_hProcess, CPPUTILS_NULL, cunSizeToAlloc, MEM_COMMIT, PAGE_READWRITE);
	if (!pRemoteMem) {
		return false;
	}

	if (!WriteProcessMemory(a_hProcess, pRemoteMem, &a_module, cunSizeToAlloc, &szWritten)) {
		VirtualFreeEx(a_hProcess, pRemoteMem, 0, MEM_RELEASE);
		return false;
	}

	hThread = CreateRemoteThread(a_hProcess, CPPUTILS_NULL, 0, (LPTHREAD_START_ROUTINE)((void*)LoadLibraryA), pRemoteMem, 0, &dwThreadId);
	if (!hThread) {
		VirtualFreeEx(a_hProcess, pRemoteMem, 0, MEM_RELEASE);
		return false;
	}

	WaitForSingleObject(hThread, INFINITE);
	GetExitCodeThread(hThread, &dwThreadId);
	CloseHandle(hThread);
	VirtualFreeEx(a_hProcess, pRemoteMem, 0, MEM_RELEASE);

	return dwThreadId ? true : false; // dwThreadId is the return from FreeLibrary
}


CPPUTILS_END_C


#endif  //  #ifdef _WIN32
