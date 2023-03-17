//
// file:            main_any_quick_test.c
// path:			src/tests/main_any_quick_test.c
// created on:		2023 Feb 25
// created by:		Davit Kalantaryan (davit.kalantaryan@desy.de)
//


#include <cinternal/export_symbols.h>
#include <cinternal/flagshelper.h>
#include <cinternal/insert_info_to_bin.h>
#include <cinternal/parser/tokenizer01.h>
#include <stdint.h>
#include <stdio.h>
#include <assert.h>

#ifdef _WIN32
#include <cinternal/disable_compiler_warnings.h>
#include <WinSock2.h>
#include <WS2tcpip.h>
#include <Windows.h>
#define CintrSleepMsIntr(_x)	SleepEx(_x,TRUE)
#else
#include <unistd.h>
#define CintrSleepMsIntr(_x)	usleep(CPPUTILS_STATIC_CAST(useconds_t,1000*(_x)))
#endif

#define CINTERNALS_GLB_CONS_DSGN_VAL	1


CPPUTILS_INSERT_COMMENT_TO_BIN_RAW(".cintr","test comment 01")
CPPUTILS_INSERT_COMMENT_TO_BIN_RAW(".cintr", "test comment 02")

static int s_nData = 0;

CPPUTILS_CODE_INITIALIZER(code_init) {
    printf("Hello from C global constructor\n");
	s_nData = CINTERNALS_GLB_CONS_DSGN_VAL;
}

int main(void)
{
	int nCounter = 0;
	CPPUTILS_FLAGS_UN(nm1, nm2)flags;
	//union {
	//	uint64_t all;
	//	struct {
	//		uint64_t nm1_true : 1;
	//		uint64_t nm1_false : 1;
	//	}b;
	//}flags;
	
	assert(s_nData == CINTERNALS_GLB_CONS_DSGN_VAL);
	printf("s_nData = %d\n", s_nData);

	flags.all = CPPUTILS_INIT_BITS;
	assert(flags.b.nm1_false == 1);
	printf("flags.b.nm1_false = %d\n", (int)flags.b.nm1_false);

	flags.b2.nm1_both = CPPUTILS_MAKE_BITS_TRUE;
	assert(flags.b.nm1_false == 0);
	printf("flags.b.nm1_false = %d\n", (int)flags.b.nm1_false);

	while (nCounter < 1000) {
		CintrSleepMsIntr(1000);
		printf("nCounter = %d\n",++nCounter);
	}

	return 0;
}
