//
// repo:			cutils
// file:            main_cutils_core_windows_ld_preload.c
// path:			src/tests/main_cutils_core_windows_ld_preload.c
// created on:		2023 Mar 09
// created by:		Davit Kalantaryan (davit.kalantaryan@desy.de)
//


//#define CINTERNAL_WINDOWS_LD_PRELOAD_WAIT_FOR_DEBUGGER		1

#include <cutils/loadfreelib_on_remote_process_sys.h>
#include <private/cutils/parser/tokenizer01_windows_p.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <signal.h>
#include <assert.h>
#include <fcntl.h>
#include <io.h>

#define CINTR_MAX_ENV_LEN					1023
#define CINTR_MAX_CMD_LINE_BUFFER_SIZE		4095
#define CINTR_LD_PRELOAD_ENV_NAME			"LD_PRELOAD"
#define CINTR_PROC_NO_WAIT					"CINTR_PROC_NO_WAIT"

static HANDLE	s_mainThreadHandle;

static void SignalHandler(int a_signal) CPPUTILS_NOEXCEPT;



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
	DWORD dwEnvLen;
	char vcEnvBuffer[CINTR_MAX_ENV_LEN + 1];
	int nShouldWaitForProcess = 1;
	BOOL bCrtPrcRet;
	int ind, nRet;
	size_t unOffset = 0;
	char vcCmdLine[CINTR_MAX_CMD_LINE_BUFFER_SIZE + 1];
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

	if (a_argc < 1) {
		fprintf(stderr, "name of application to start is not specified!\n");
		return 1;
	}

	vcCmdLine[0] = 0;

	for (ind = 1; ind < a_argc; ++ind) {
		nRet = snprintf(vcCmdLine + unOffset, CINTR_MAX_CMD_LINE_BUFFER_SIZE - unOffset, " %s", a_argv[ind]);
		unOffset += CPPUTILS_STATIC_CAST(size_t, nRet);
		if (unOffset >= CINTR_MAX_CMD_LINE_BUFFER_SIZE) {
			break;
		}
	}  //  for (i = 2; i < a_argc; ++i) {


	ZeroMemory(&aStartInfo, sizeof(aStartInfo));
	aStartInfo.wShowWindow = SW_SHOWNOACTIVATE;

	bCrtPrcRet = CreateProcessA(
		a_argv[1],			// lpApplicationName
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
		fprintf(stderr, "Unable to create process with the name %s\n", a_argv[1]);
		return 1;
	}

	// let's check whether we should wait for child
	dwEnvLen = GetEnvironmentVariableA(CINTR_PROC_NO_WAIT, vcEnvBuffer, CINTR_MAX_ENV_LEN);
	if ((dwEnvLen > 0) && (dwEnvLen < CINTR_MAX_ENV_LEN)) {
		nShouldWaitForProcess = atoi(vcEnvBuffer);
	}  //  if ((dwEnvLen > 0) && (dwEnvLen < CINTR_MAX_ENV_LEN)) {

	// before resuming thread/process we should read 'LD_PRELOAD' and preload all libraries
	dwEnvLen = GetEnvironmentVariableA(CINTR_LD_PRELOAD_ENV_NAME, vcEnvBuffer, CINTR_MAX_ENV_LEN);
	if ((dwEnvLen > 0) && (dwEnvLen < CINTR_MAX_ENV_LEN)) {
		CInternalTokenizerWindows01a(vcEnvBuffer, aProcInf.hProcess);
	}  //  if ((dwEnvLen > 0) && (dwEnvLen < CINTR_MAX_ENV_LEN)) {

	// all necessary libs preloaded (or tried to preload), time to resume the process
	ResumeThread(aProcInf.hThread);
	if (nShouldWaitForProcess) {
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


static VOID NTAPI InterruptFunctionStatic(_In_ ULONG_PTR a_parameter) CPPUTILS_NOEXCEPT
{
	CPPUTILS_STATIC_CAST(void, a_parameter);
}


static void SignalHandler(int a_signal) CPPUTILS_NOEXCEPT
{
	assert(a_signal == SIGINT);
	CPPUTILS_STATIC_CAST(void, a_signal);
	QueueUserAPC(&InterruptFunctionStatic, s_mainThreadHandle, 0);
}
