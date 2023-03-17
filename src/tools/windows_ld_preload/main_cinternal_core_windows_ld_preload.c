//
// file:            main_cinternal_core_windows_ld_preload.c
// path:			src/tests/main_cinternal_core_windows_ld_preload.c
// created on:		2023 Mar 09
// created by:		Davit Kalantaryan (davit.kalantaryan@desy.de)
//


//#define CINTERNAL_WINDOWS_LD_PRELOAD_WAIT_FOR_DEBUGGER		1

#include <cinternal/export_symbols.h>
#include <cinternal/load_lib_on_remote_process_sys.h>
#include <cinternal/parser/argparser01.h>
#include <private/cinternal/parser/tokenizer01_windows_p.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <signal.h>
#include <assert.h>
#include <fcntl.h>
#include <io.h>


#define MAX_BUFFER_SIZE		4095

static HANDLE	s_mainThreadHandle;

static void SignalHandler(int a_signal);



CPPUTILS_CODE_INITIALIZER(main_cinternal_core_windows_ld_preload_init) {
	DWORD vdwProcList[16];
	DWORD dwRet = GetConsoleProcessList(vdwProcList, 16);
	if (dwRet < 2) {
		FreeConsole();
	}

	//FILE* fpFile;
	//FreeConsole();
	//AttachConsole(ATTACH_PARENT_PROCESS);
	//if (GetConsoleWindow()) {
	//	freopen_s(&fpFile, "CONOUT$", "w", stdout); // redirect stdout to console
	//	freopen_s(&fpFile, "CONOUT$", "w", stderr); // redirect stderr to console
	//	freopen_s(&fpFile, "CONIN$", "r", stdin); // redirect stdin to console
	//}
}


int main(int a_argc, char* a_argv[])
{
	int nArgc = a_argc - 1;
	char** ppcArgv = a_argv + 1;
	DWORD dwEnvLen;
	char vcLdPreloadEnvBuffer[1024];
	const char *cpcAppToStart, *cpcNextArg;
	bool bShouldWaitForProcess;
	BOOL bCrtPrcRet;
	int ind, nRet;
	size_t unOffset = 0;
	char vcCmdLine[MAX_BUFFER_SIZE + 1];
	STARTUPINFOA aStartInfo;
	PROCESS_INFORMATION aProcInf = { 0 };

#if defined(CINTERNAL_WINDOWS_LD_PRELOAD_WAIT_FOR_DEBUGGER)
	fprintf(stdout, "Press any key then enter to continue "); fflush(stdout);
	nRet = getchar();
	CPPUTILS_STATIC_CAST(void, nRet);
	//while (!IsDebuggerPresent()) {
	//	Sleep(1000);
	//}
#endif

	cpcNextArg = CInternalFindEndTakeArg(&nArgc, ppcArgv, "---no-wait", &nRet,false);
	bShouldWaitForProcess = (cpcNextArg == CPPUTILS_NULL);

	if (a_argc < 1) {
		fprintf(stderr, "name of application to start is not specified!\n");
		return 1;
	}
	//else 
	{
		cpcAppToStart = ppcArgv[0];
	}

	vcCmdLine[0] = 0;

	for (ind = 1; ind < nArgc; ++ind) {
		nRet = snprintf(vcCmdLine + unOffset, MAX_BUFFER_SIZE - unOffset, " %s", ppcArgv[ind]);
		unOffset += CPPUTILS_STATIC_CAST(size_t, nRet);
		if (unOffset >= MAX_BUFFER_SIZE) {
			break;
		}
	}  //  for (i = 2; i < a_argc; ++i) {


	ZeroMemory(&aStartInfo, sizeof(aStartInfo));
	aStartInfo.wShowWindow = SW_SHOWNOACTIVATE;

	bCrtPrcRet = CreateProcessA(
		cpcAppToStart,			// lpApplicationName
		vcCmdLine,			// lpCommandLine
		CPPUTILS_NULL,		// lpProcessAttributes
		CPPUTILS_NULL,		// lpThreadAttributes
		FALSE,				// bInheritHandles   => todo: think on this
		CREATE_SUSPENDED,	// dwCreationFlags   => todo: maybe I'll switch this to 0
		CPPUTILS_NULL,		// lpEnvironment
		CPPUTILS_NULL,		// lpCurrentDirectory
		&aStartInfo,		// lpStartupInfo
		&aProcInf			// lpProcessInformation
	);
	if (!bCrtPrcRet) {
		fprintf(stderr, "Unable to create process with the name %s\n", cpcAppToStart);
		return 1;
	}



	{
		// before resuming thread/process we should read 'LD_PRELOAD' and preload all libraries
		dwEnvLen = GetEnvironmentVariableA("LD_PRELOAD", vcLdPreloadEnvBuffer, 1023);
		if ((dwEnvLen > 0) && (dwEnvLen < 1023)) {
			CInternalTokenizerWindows01a(vcLdPreloadEnvBuffer, aProcInf.hProcess);
		}  //  if ((dwEnvLen > 0) && (dwEnvLen < 1023)) {
	}



	ResumeThread(aProcInf.hThread);
	if (bShouldWaitForProcess) {
		DWORD dwWaitResult;
		s_mainThreadHandle = GetCurrentThread();
		signal(SIGINT, &SignalHandler);
		dwWaitResult = WaitForSingleObjectEx(aProcInf.hProcess, INFINITE, TRUE);
		switch (dwWaitResult) {
		case WAIT_IO_COMPLETION:
			TerminateProcess(aProcInf.hProcess, 1);
			break;
		default:
			break;
		}
	}
	CloseHandle(aProcInf.hThread);
	CloseHandle(aProcInf.hProcess);


	return 0;
}


static VOID NTAPI InterruptFunctionStatic(_In_ ULONG_PTR a_parameter)
{
	CPPUTILS_STATIC_CAST(void, a_parameter);
}


static void SignalHandler(int a_signal)
{
	assert(a_signal == SIGINT);
	CPPUTILS_STATIC_CAST(void, a_signal);
	QueueUserAPC(&InterruptFunctionStatic, s_mainThreadHandle, 0);
}
