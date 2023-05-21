//
// file:			cinternal_unit_test_0000_initial.c
// path:			src/tests/unit_test/cinternal_unit_test_0000_initial.c
// created on:		2023 May 19
// created by:		Davit Kalantaryan (davit.kalantaryan@gmail.com)
//

#include <cinternal/internal_header.h>

#ifndef CINTERNAL_FLAGS_HELPER_VERSION
#define CINTERNAL_FLAGS_HELPER_VERSION	2
#endif

#include <cinternal/tool/unit_test_tools.h>
#include <cinternal/unit_test.h>
#include <cinternal/flagshelper.h>
#include <stdbool.h>

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


CPPUTILS_UTEST_ALL(f_0001_bistate_flags, t_0001) {
	CPPUTILS_FLAGS_UN(field1,field2) aFlags;

	aFlags.wr_all = CPPUTILS_INIT_BITS;
	CinternalUnitTestAssertCheck(aFlags.rd.field1_true == 0);
	CinternalUnitTestAssertCheck(aFlags.rd.field1_false == 1);
	CinternalUnitTestAssertCheck(aFlags.rd.field2_true == 0);
	CinternalUnitTestAssertCheck(aFlags.rd.field2_false == 1);

	aFlags.wr.field1 = CPPUTILS_MAKE_BITS_TRUE;
	CinternalUnitTestAssertCheck(aFlags.rd.field1_true == 1);
	CinternalUnitTestAssertCheck(aFlags.rd.field1_false == 0);
	CinternalUnitTestAssertCheck(aFlags.rd.field2_true == 0);
	CinternalUnitTestAssertCheck(aFlags.rd.field2_false == 1);

	aFlags.wr.field2 = CPPUTILS_MAKE_BITS_TRUE;
	CinternalUnitTestAssertCheck(aFlags.rd.field1_true == 1);
	CinternalUnitTestAssertCheck(aFlags.rd.field1_false == 0);
	CinternalUnitTestAssertCheck(aFlags.rd.field2_true == 1);
	CinternalUnitTestAssertCheck(aFlags.rd.field2_false == 0);

	aFlags.wr.field1 = CPPUTILS_MAKE_BITS_FALSE;
	CinternalUnitTestAssertCheck(aFlags.rd.field1_true == 0);
	CinternalUnitTestAssertCheck(aFlags.rd.field1_false == 1);
	CinternalUnitTestAssertCheck(aFlags.rd.field2_true == 1);
	CinternalUnitTestAssertCheck(aFlags.rd.field2_false == 0);

	aFlags.wr.field2 = CPPUTILS_MAKE_BITS_FALSE;
	CinternalUnitTestAssertCheck(aFlags.rd.field1_true == 0);
	CinternalUnitTestAssertCheck(aFlags.rd.field1_false == 1);
	CinternalUnitTestAssertCheck(aFlags.rd.field2_true == 0);
	CinternalUnitTestAssertCheck(aFlags.rd.field2_false == 1);
}


CPPUTILS_UTEST_ALL(f_0001_bistate_flags, t_0002) {
	CPPUTILS_FLAGS_UN(field1, field2) aFlags;

	aFlags.wr_all = CPPUTILS_BISTATE_MAKE_ALL_BITS_TRUE;
	CinternalUnitTestAssertCheck(aFlags.rd.field1_true == 1);
	CinternalUnitTestAssertCheck(aFlags.rd.field1_false == 0);
	CinternalUnitTestAssertCheck(aFlags.rd.field2_true == 1);
	CinternalUnitTestAssertCheck(aFlags.rd.field2_false == 0);
}


CPPUTILS_UTEST_ALL(f_0001_bistate_flags, t_0003) {
	CPPUTILS_FLAGS_UN(field1, field2) aFlags;

	aFlags.wr_all = CPPUTILS_BISTATE_MAKE_ALL_BITS_FALSE;
	CinternalUnitTestAssertCheck(aFlags.rd.field1_true == 0);
	CinternalUnitTestAssertCheck(aFlags.rd.field1_false == 1);
	CinternalUnitTestAssertCheck(aFlags.rd.field2_true == 0);
	CinternalUnitTestAssertCheck(aFlags.rd.field2_false == 1);
}


CPPUTILS_UTEST_ALL(f_0001_bistate_flags, t_0004) {
	union BistateFlags aFlags;

	aFlags.wr_all = CPPUTILS_INIT_BITS;
	CinternalUnitTestAssertCheck(aFlags.rd.field1_true == 0);
	CinternalUnitTestAssertCheck(aFlags.rd.field1_false == 1);
	CinternalUnitTestAssertCheck(aFlags.rd.field2_true == 0);
	CinternalUnitTestAssertCheck(aFlags.rd.field2_false == 1);

	aFlags.wr.field1 = CPPUTILS_MAKE_BITS_TRUE;
	CinternalUnitTestAssertCheck(aFlags.rd.field1_true == 1);
	CinternalUnitTestAssertCheck(aFlags.rd.field1_false == 0);
	CinternalUnitTestAssertCheck(aFlags.rd.field2_true == 0);
	CinternalUnitTestAssertCheck(aFlags.rd.field2_false == 1);

	aFlags.wr.field2 = CPPUTILS_MAKE_BITS_TRUE;
	CinternalUnitTestAssertCheck(aFlags.rd.field1_true == 1);
	CinternalUnitTestAssertCheck(aFlags.rd.field1_false == 0);
	CinternalUnitTestAssertCheck(aFlags.rd.field2_true == 1);
	CinternalUnitTestAssertCheck(aFlags.rd.field2_false == 0);

	aFlags.wr.field1 = CPPUTILS_MAKE_BITS_FALSE;
	CinternalUnitTestAssertCheck(aFlags.rd.field1_true == 0);
	CinternalUnitTestAssertCheck(aFlags.rd.field1_false == 1);
	CinternalUnitTestAssertCheck(aFlags.rd.field2_true == 1);
	CinternalUnitTestAssertCheck(aFlags.rd.field2_false == 0);

	aFlags.wr.field2 = CPPUTILS_MAKE_BITS_FALSE;
	CinternalUnitTestAssertCheck(aFlags.rd.field1_true == 0);
	CinternalUnitTestAssertCheck(aFlags.rd.field1_false == 1);
	CinternalUnitTestAssertCheck(aFlags.rd.field2_true == 0);
	CinternalUnitTestAssertCheck(aFlags.rd.field2_false == 1);
}
