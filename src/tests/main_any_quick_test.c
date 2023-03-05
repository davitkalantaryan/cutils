//
// file:            main_any_quick_test.c
// path:			src/tests/main_any_quick_test.c
// created on:		2023 Feb 25
// created by:		Davit Kalantaryan (davit.kalantaryan@desy.de)
//


#include <cinternal/export_symbols.h>
#include <cinternal/flagshelper.h>
#include <cinternal/insert_info_to_bin.h>
#include <stdint.h>
#include <stdio.h>
#include <assert.h>

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

	return 0;
}
