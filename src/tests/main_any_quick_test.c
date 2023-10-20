//
// file:            main_any_quick_test.c
// path:			src/tests/main_any_quick_test.c
// created on:		2023 Feb 25
// created by:		Davit Kalantaryan (davit.kalantaryan@desy.de)
//


#include <cutils/export_symbols.h>
#include <cutils/parser/tokenizer01.h>
#include <cinternal/bistateflags.h>
#include <cinternal/insert_info_to_bin.h>
#include <stdint.h>
#include <stdio.h>
#include <assert.h>
#include <cinternal/disable_compiler_warnings.h>
#ifdef _WIN32
#include <WinSock2.h>
#include <WS2tcpip.h>
#include <Windows.h>
#define CintrSleepMsIntr(_x)	SleepEx(_x,TRUE)
#else
#include <unistd.h>
#define CintrSleepMsIntr(_x)	usleep(CPPUTILS_STATIC_CAST(useconds_t,1000*(_x)))
#endif
#include <cinternal/undisable_compiler_warnings.h>



int main(void)
{
	return 0;
}
