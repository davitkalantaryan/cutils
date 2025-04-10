//
// repo:			cutils
// file:			cutils_unit_test_0000_initial.c
// path:			src/tests/unit_test/cutils_unit_test_0000_initial.c
// created on:		2023 May 19
// created by:		Davit Kalantaryan (davit.kalantaryan@gmail.com)
//

#include <cinternal/unit_test.h>
#include <cinternal/bistateflags.h>
#include <cinternal/disable_compiler_warnings.h>
#include <stdbool.h>
#include <cinternal/undisable_compiler_warnings.h>

#define CINTERNAL_UT_BISTATE_RESERVED_BITS		60

union BistateFlags {
	uint64_t  wr_all;
	struct {
		CPPUTILS_BISTATE1(field1);
		CPPUTILS_BISTATE1(field2);
		uint64_t    reserved01 : CINTERNAL_UT_BISTATE_RESERVED_BITS;
	}rd;
	struct {
		CPPUTILS_BISTATE2(field1);
		CPPUTILS_BISTATE2(field2);
		uint64_t    reserved01 : CINTERNAL_UT_BISTATE_RESERVED_BITS;
	}wr;
};


// below is defination of type, se usage of it below
CPPUTILS_BISTATE_FLAGS_UN_NM(DataTypeName, field1, field2);


CPPUTILS_UTEST_ALL(f_0001_bistate_flags, t_0001) {
	union DataTypeName aFlags;

	aFlags.wr_all = CPPUTILS_BISTATE_MAKE_ALL_BITS_FALSE;
	CinternalUnitTestAssertCheckOpt(aFlags.rd.field1_true == 0);
	CinternalUnitTestAssertCheckOpt(aFlags.rd.field1_false == 1);
	CinternalUnitTestAssertCheckOpt(aFlags.rd.field2_true == 0);
	CinternalUnitTestAssertCheckOpt(aFlags.rd.field2_false == 1);

	aFlags.wr.field1 = CPPUTILS_BISTATE_MAKE_BITS_TRUE;
	CinternalUnitTestAssertCheckOpt(aFlags.rd.field1_true == 1);
	CinternalUnitTestAssertCheckOpt(aFlags.rd.field1_false == 0);
	CinternalUnitTestAssertCheckOpt(aFlags.rd.field2_true == 0);
	CinternalUnitTestAssertCheckOpt(aFlags.rd.field2_false == 1);

	aFlags.wr.field2 = CPPUTILS_BISTATE_MAKE_BITS_TRUE;
	CinternalUnitTestAssertCheckOpt(aFlags.rd.field1_true == 1);
	CinternalUnitTestAssertCheckOpt(aFlags.rd.field1_false == 0);
	CinternalUnitTestAssertCheckOpt(aFlags.rd.field2_true == 1);
	CinternalUnitTestAssertCheckOpt(aFlags.rd.field2_false == 0);

	aFlags.wr.field1 = CPPUTILS_BISTATE_MAKE_BITS_FALSE;
	CinternalUnitTestAssertCheckOpt(aFlags.rd.field1_true == 0);
	CinternalUnitTestAssertCheckOpt(aFlags.rd.field1_false == 1);
	CinternalUnitTestAssertCheckOpt(aFlags.rd.field2_true == 1);
	CinternalUnitTestAssertCheckOpt(aFlags.rd.field2_false == 0);

	aFlags.wr.field2 = CPPUTILS_BISTATE_MAKE_BITS_FALSE;
	CinternalUnitTestAssertCheckOpt(aFlags.rd.field1_true == 0);
	CinternalUnitTestAssertCheckOpt(aFlags.rd.field1_false == 1);
	CinternalUnitTestAssertCheckOpt(aFlags.rd.field2_true == 0);
	CinternalUnitTestAssertCheckOpt(aFlags.rd.field2_false == 1);
}


CPPUTILS_UTEST_ALL(f_0001_bistate_flags, t_0002) {
	CPPUTILS_BISTATE_FLAGS_UN(field1, field2) aFlags;

	aFlags.wr_all = CPPUTILS_BISTATE_MAKE_ALL_BITS_FALSE;
	CinternalUnitTestAssertCheckOpt(aFlags.rd.field1_true == 0);
	CinternalUnitTestAssertCheckOpt(aFlags.rd.field1_false == 1);
	CinternalUnitTestAssertCheckOpt(aFlags.rd.field2_true == 0);
	CinternalUnitTestAssertCheckOpt(aFlags.rd.field2_false == 1);

	aFlags.wr.field1 = CPPUTILS_BISTATE_MAKE_BITS_TRUE;
	CinternalUnitTestAssertCheckOpt(aFlags.rd.field1_true == 1);
	CinternalUnitTestAssertCheckOpt(aFlags.rd.field1_false == 0);
	CinternalUnitTestAssertCheckOpt(aFlags.rd.field2_true == 0);
	CinternalUnitTestAssertCheckOpt(aFlags.rd.field2_false == 1);

	aFlags.wr.field2 = CPPUTILS_BISTATE_MAKE_BITS_TRUE;
	CinternalUnitTestAssertCheckOpt(aFlags.rd.field1_true == 1);
	CinternalUnitTestAssertCheckOpt(aFlags.rd.field1_false == 0);
	CinternalUnitTestAssertCheckOpt(aFlags.rd.field2_true == 1);
	CinternalUnitTestAssertCheckOpt(aFlags.rd.field2_false == 0);

	aFlags.wr.field1 = CPPUTILS_BISTATE_MAKE_BITS_FALSE;
	CinternalUnitTestAssertCheckOpt(aFlags.rd.field1_true == 0);
	CinternalUnitTestAssertCheckOpt(aFlags.rd.field1_false == 1);
	CinternalUnitTestAssertCheckOpt(aFlags.rd.field2_true == 1);
	CinternalUnitTestAssertCheckOpt(aFlags.rd.field2_false == 0);

	aFlags.wr.field2 = CPPUTILS_BISTATE_MAKE_BITS_FALSE;
	CinternalUnitTestAssertCheckOpt(aFlags.rd.field1_true == 0);
	CinternalUnitTestAssertCheckOpt(aFlags.rd.field1_false == 1);
	CinternalUnitTestAssertCheckOpt(aFlags.rd.field2_true == 0);
	CinternalUnitTestAssertCheckOpt(aFlags.rd.field2_false == 1);
}


CPPUTILS_UTEST_ALL(f_0001_bistate_flags, t_0003) {
	CPPUTILS_BISTATE_FLAGS_UN(field1, field2) aFlags;

	aFlags.wr_all = CPPUTILS_BISTATE_MAKE_ALL_BITS_TRUE;
	CinternalUnitTestAssertCheckOpt(aFlags.rd.field1_true == 1);
	CinternalUnitTestAssertCheckOpt(aFlags.rd.field1_false == 0);
	CinternalUnitTestAssertCheckOpt(aFlags.rd.field2_true == 1);
	CinternalUnitTestAssertCheckOpt(aFlags.rd.field2_false == 0);
}


CPPUTILS_UTEST_ALL(f_0001_bistate_flags, t_0004) {
	CPPUTILS_BISTATE_FLAGS_UN(field1, field2) aFlags;

	aFlags.wr_all = CPPUTILS_BISTATE_MAKE_ALL_BITS_FALSE;
	CinternalUnitTestAssertCheckOpt(aFlags.rd.field1_true == 0);
	CinternalUnitTestAssertCheckOpt(aFlags.rd.field1_false == 1);
	CinternalUnitTestAssertCheckOpt(aFlags.rd.field2_true == 0);
	CinternalUnitTestAssertCheckOpt(aFlags.rd.field2_false == 1);
}


CPPUTILS_UTEST_ALL(f_0001_bistate_flags, t_0005) {
	union BistateFlags aFlags;

	aFlags.wr_all = CPPUTILS_BISTATE_MAKE_ALL_BITS_FALSE;
	CinternalUnitTestAssertCheckOpt(aFlags.rd.field1_true == 0);
	CinternalUnitTestAssertCheckOpt(aFlags.rd.field1_false == 1);
	CinternalUnitTestAssertCheckOpt(aFlags.rd.field2_true == 0);
	CinternalUnitTestAssertCheckOpt(aFlags.rd.field2_false == 1);

	aFlags.wr.field1 = CPPUTILS_BISTATE_MAKE_BITS_TRUE;
	CinternalUnitTestAssertCheckOpt(aFlags.rd.field1_true == 1);
	CinternalUnitTestAssertCheckOpt(aFlags.rd.field1_false == 0);
	CinternalUnitTestAssertCheckOpt(aFlags.rd.field2_true == 0);
	CinternalUnitTestAssertCheckOpt(aFlags.rd.field2_false == 1);

	aFlags.wr.field2 = CPPUTILS_BISTATE_MAKE_BITS_TRUE;
	CinternalUnitTestAssertCheckOpt(aFlags.rd.field1_true == 1);
	CinternalUnitTestAssertCheckOpt(aFlags.rd.field1_false == 0);
	CinternalUnitTestAssertCheckOpt(aFlags.rd.field2_true == 1);
	CinternalUnitTestAssertCheckOpt(aFlags.rd.field2_false == 0);

	aFlags.wr.field1 = CPPUTILS_BISTATE_MAKE_BITS_FALSE;
	CinternalUnitTestAssertCheckOpt(aFlags.rd.field1_true == 0);
	CinternalUnitTestAssertCheckOpt(aFlags.rd.field1_false == 1);
	CinternalUnitTestAssertCheckOpt(aFlags.rd.field2_true == 1);
	CinternalUnitTestAssertCheckOpt(aFlags.rd.field2_false == 0);

	aFlags.wr.field2 = CPPUTILS_BISTATE_MAKE_BITS_FALSE;
	CinternalUnitTestAssertCheckOpt(aFlags.rd.field1_true == 0);
	CinternalUnitTestAssertCheckOpt(aFlags.rd.field1_false == 1);
	CinternalUnitTestAssertCheckOpt(aFlags.rd.field2_true == 0);
	CinternalUnitTestAssertCheckOpt(aFlags.rd.field2_false == 1);
}
