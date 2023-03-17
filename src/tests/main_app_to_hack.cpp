//
// file:            main_app_to_hack.c
// path:			src/tests/main_app_to_hack.c
// created on:		2023 Mar 16
// created by:		Davit Kalantaryan (davit.kalantaryan@desy.de)
//


#include <cinternal/disable_compiler_warnings.h>
#include <stdio.h>
#ifdef _WIN32
#include <WinSock2.h>
#include <WS2tcpip.h>
#include <Windows.h>
#define CINT_APP_TO_HACK_GETPID()	(int)GetCurrentProcessId()
#else
#include <signal.h>
#include <unistd.h>
#define CINT_APP_TO_HACK_GETPID()	(int)getpid()
#endif

int main(void)
{
#ifdef _WIN32
#else
	sigset_t mask;
	sigemptyset(&mask);
#endif
	
	printf("App to hack started. Pid is: %d. Going to infinite loop\n", CINT_APP_TO_HACK_GETPID());

#ifdef _WIN32
	SleepEx(INFINITE, TRUE);
#else
	sigsuspend(&mask);
#endif

	return 0;
}
