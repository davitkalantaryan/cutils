//
// file:            main_app_to_hack.c
// path:			src/tests/main_app_to_hack.c
// created on:		2023 Mar 16
// created by:		Davit Kalantaryan (davit.kalantaryan@desy.de)
//


#include <stdio.h>
#ifdef _WIN32
#include <WinSock2.h>
#include <WS2tcpip.h>
#include <Windows.h>
#define CINT_APP_TO_HACK_GETPID()	(int)GetCurrentProcessId()
#define CIntrSleepExIntrp(_x)       SleepEx((DWORD)(_x),TRUE)
#else
#include <signal.h>
#include <unistd.h>
#define CINT_APP_TO_HACK_GETPID()	(int)getpid()
#define CIntrSleepExIntrp(_x)       usleep((useconds_t)(_x)*1000)
#endif

int main(void)
{
    //int nCounter = 0;

#ifdef _WIN32
#else
	sigset_t mask;
	sigemptyset(&mask);
#endif
	
    printf("App to hack version 06 started. Pid is: %d  . Going to infinite loop\n", CINT_APP_TO_HACK_GETPID());

#ifdef _WIN32
    SleepEx(INFINITE, TRUE);
#else
    //sigsuspend(&mask);
    while(1){
        //printf("nCounter = %d\n",++nCounter);
        CIntrSleepExIntrp(20000);
    }
#endif


	return 0;
}
