//
// file:			cinternal_unit_test_0002_fourstate_flags.c
// path:			src/tests/unit_test/cinternal_unit_test_0002_fourstate_flags.c
// created on:		2023 May 19
// created by:		Davit Kalantaryan (davit.kalantaryan@gmail.com)
//

#include <cinternal/internal_header.h>

#ifndef CINTERNAL_FLAGS_HELPER_VERSION
#define CINTERNAL_FLAGS_HELPER_VERSION	2
#endif

#include <cinternal/tool/unit_test_tools.h>
#include <cinternal/unit_test.h>
#include <cinternal/fourstateflags.h>
#include <stdbool.h>


#define CINTERNAL_UT_FOURSTATE_RESERVED_BITS		56

union FourstateFlags {
	uint64_t  wr_all;
	struct {
		CPPUTILS_FOURSTATE1(field1);
		CPPUTILS_FOURSTATE1(field2);
		uint64_t    reserved01 : CINTERNAL_UT_FOURSTATE_RESERVED_BITS;
	}rd1;
	struct {
		CPPUTILS_FOURSTATE2(field1);
		CPPUTILS_FOURSTATE2(field2);
		uint64_t    reserved01 : CINTERNAL_UT_FOURSTATE_RESERVED_BITS;
	}rd2;
	struct {
		CPPUTILS_FOURSTATE3a(field1);
		CPPUTILS_FOURSTATE3a(field2);
		uint64_t    reserved01 : CINTERNAL_UT_FOURSTATE_RESERVED_BITS;
	}rd3a;
	struct {
		CPPUTILS_FOURSTATE3b(field1);
		CPPUTILS_FOURSTATE3b(field2);
		uint64_t    reserved01 : CINTERNAL_UT_FOURSTATE_RESERVED_BITS;
	}rd3b;
	struct {
		CPPUTILS_FOURSTATE4(field1);
		CPPUTILS_FOURSTATE4(field2);
		uint64_t    reserved01 : CINTERNAL_UT_FOURSTATE_RESERVED_BITS;
	}wr;
};


CPPUTILS_UTEST_ALL(f_0002_fourstate_flags, t_0001) {
	CPPUTILS_FOURSTATE_FLAGS_UN(field1, field2) aFlags;

	aFlags.wr_all = CPPUTILS_FOURSTATE_MAKE_ALL_BITS_FALSE;
	CinternalUnitTestAssertCheck(aFlags.rd1.field1_true == 0);
	CinternalUnitTestAssertCheck(aFlags.rd1.field1_ongoing_false_to_true == 0);
	CinternalUnitTestAssertCheck(aFlags.rd1.field1_ongoing_true_to_false == 0);
	CinternalUnitTestAssertCheck(aFlags.rd1.field1_false == 1);
	CinternalUnitTestAssertCheck(aFlags.rd1.field2_true == 0);
	CinternalUnitTestAssertCheck(aFlags.rd1.field2_ongoing_false_to_true == 0);
	CinternalUnitTestAssertCheck(aFlags.rd1.field2_ongoing_true_to_false == 0);
	CinternalUnitTestAssertCheck(aFlags.rd1.field2_false == 1);

	aFlags.wr.field1 = CPPUTILS_FOURSTATE_MAKE_BITS_TRUE;
	CinternalUnitTestAssertCheck(aFlags.rd1.field1_true == 1);
	CinternalUnitTestAssertCheck(aFlags.rd1.field1_ongoing_false_to_true == 0);
	CinternalUnitTestAssertCheck(aFlags.rd1.field1_ongoing_true_to_false == 0);
	CinternalUnitTestAssertCheck(aFlags.rd1.field1_false == 0);
	CinternalUnitTestAssertCheck(aFlags.rd1.field2_true == 0);
	CinternalUnitTestAssertCheck(aFlags.rd1.field2_ongoing_false_to_true == 0);
	CinternalUnitTestAssertCheck(aFlags.rd1.field2_ongoing_true_to_false == 0);
	CinternalUnitTestAssertCheck(aFlags.rd1.field2_false == 1);

	aFlags.wr.field1 = CPPUTILS_FOURSTATE_MAKE_BITS_ONGOING_FT;
	CinternalUnitTestAssertCheck(aFlags.rd1.field1_true == 0);
	CinternalUnitTestAssertCheck(aFlags.rd1.field1_ongoing_false_to_true == 1);
	CinternalUnitTestAssertCheck(aFlags.rd1.field1_ongoing_true_to_false == 0);
	CinternalUnitTestAssertCheck(aFlags.rd1.field1_false == 0);
	CinternalUnitTestAssertCheck(aFlags.rd1.field2_true == 0);
	CinternalUnitTestAssertCheck(aFlags.rd1.field2_ongoing_false_to_true == 0);
	CinternalUnitTestAssertCheck(aFlags.rd1.field2_ongoing_true_to_false == 0);
	CinternalUnitTestAssertCheck(aFlags.rd1.field2_false == 1);

	aFlags.wr.field1 = CPPUTILS_FOURSTATE_MAKE_BITS_ONGOING_TF;
	CinternalUnitTestAssertCheck(aFlags.rd1.field1_true == 0);
	CinternalUnitTestAssertCheck(aFlags.rd1.field1_ongoing_false_to_true == 0);
	CinternalUnitTestAssertCheck(aFlags.rd1.field1_ongoing_true_to_false == 1);
	CinternalUnitTestAssertCheck(aFlags.rd1.field1_false == 0);
	CinternalUnitTestAssertCheck(aFlags.rd1.field2_true == 0);
	CinternalUnitTestAssertCheck(aFlags.rd1.field2_ongoing_false_to_true == 0);
	CinternalUnitTestAssertCheck(aFlags.rd1.field2_ongoing_true_to_false == 0);
	CinternalUnitTestAssertCheck(aFlags.rd1.field2_false == 1);

	aFlags.wr.field1 = CPPUTILS_FOURSTATE_MAKE_BITS_FALSE;
	CinternalUnitTestAssertCheck(aFlags.rd1.field1_true == 0);
	CinternalUnitTestAssertCheck(aFlags.rd1.field1_ongoing_false_to_true == 0);
	CinternalUnitTestAssertCheck(aFlags.rd1.field1_ongoing_true_to_false == 0);
	CinternalUnitTestAssertCheck(aFlags.rd1.field1_false == 1);
	CinternalUnitTestAssertCheck(aFlags.rd1.field2_true == 0);
	CinternalUnitTestAssertCheck(aFlags.rd1.field2_ongoing_false_to_true == 0);
	CinternalUnitTestAssertCheck(aFlags.rd1.field2_ongoing_true_to_false == 0);
	CinternalUnitTestAssertCheck(aFlags.rd1.field2_false == 1);

	// field2
	aFlags.wr.field2 = CPPUTILS_FOURSTATE_MAKE_BITS_TRUE;
	CinternalUnitTestAssertCheck(aFlags.rd1.field1_true == 0);
	CinternalUnitTestAssertCheck(aFlags.rd1.field1_ongoing_false_to_true == 0);
	CinternalUnitTestAssertCheck(aFlags.rd1.field1_ongoing_true_to_false == 0);
	CinternalUnitTestAssertCheck(aFlags.rd1.field1_false == 1);
	CinternalUnitTestAssertCheck(aFlags.rd1.field2_true == 1);
	CinternalUnitTestAssertCheck(aFlags.rd1.field2_ongoing_false_to_true == 0);
	CinternalUnitTestAssertCheck(aFlags.rd1.field2_ongoing_true_to_false == 0);
	CinternalUnitTestAssertCheck(aFlags.rd1.field2_false == 0);

	aFlags.wr.field2 = CPPUTILS_FOURSTATE_MAKE_BITS_ONGOING_FT;
	CinternalUnitTestAssertCheck(aFlags.rd1.field1_true == 0);
	CinternalUnitTestAssertCheck(aFlags.rd1.field1_ongoing_false_to_true == 0);
	CinternalUnitTestAssertCheck(aFlags.rd1.field1_ongoing_true_to_false == 0);
	CinternalUnitTestAssertCheck(aFlags.rd1.field1_false == 1);
	CinternalUnitTestAssertCheck(aFlags.rd1.field2_true == 0);
	CinternalUnitTestAssertCheck(aFlags.rd1.field2_ongoing_false_to_true == 1);
	CinternalUnitTestAssertCheck(aFlags.rd1.field2_ongoing_true_to_false == 0);
	CinternalUnitTestAssertCheck(aFlags.rd1.field2_false == 0);

	aFlags.wr.field2 = CPPUTILS_FOURSTATE_MAKE_BITS_ONGOING_TF;
	CinternalUnitTestAssertCheck(aFlags.rd1.field1_true == 0);
	CinternalUnitTestAssertCheck(aFlags.rd1.field1_ongoing_false_to_true == 0);
	CinternalUnitTestAssertCheck(aFlags.rd1.field1_ongoing_true_to_false == 0);
	CinternalUnitTestAssertCheck(aFlags.rd1.field1_false == 1);
	CinternalUnitTestAssertCheck(aFlags.rd1.field2_true == 0);
	CinternalUnitTestAssertCheck(aFlags.rd1.field2_ongoing_false_to_true == 0);
	CinternalUnitTestAssertCheck(aFlags.rd1.field2_ongoing_true_to_false == 1);
	CinternalUnitTestAssertCheck(aFlags.rd1.field2_false == 0);

	aFlags.wr.field2 = CPPUTILS_FOURSTATE_MAKE_BITS_FALSE;
	CinternalUnitTestAssertCheck(aFlags.rd1.field1_true == 0);
	CinternalUnitTestAssertCheck(aFlags.rd1.field1_ongoing_false_to_true == 0);
	CinternalUnitTestAssertCheck(aFlags.rd1.field1_ongoing_true_to_false == 0);
	CinternalUnitTestAssertCheck(aFlags.rd1.field1_false == 1);
	CinternalUnitTestAssertCheck(aFlags.rd1.field2_true == 0);
	CinternalUnitTestAssertCheck(aFlags.rd1.field2_ongoing_false_to_true == 0);
	CinternalUnitTestAssertCheck(aFlags.rd1.field2_ongoing_true_to_false == 0);
	CinternalUnitTestAssertCheck(aFlags.rd1.field2_false == 1);
}



CPPUTILS_UTEST_ALL(f_0002_fourstate_flags, t_0002) {
	union FourstateFlags aFlags;

	aFlags.wr_all = CPPUTILS_FOURSTATE_MAKE_ALL_BITS_FALSE;
	CinternalUnitTestAssertCheck(aFlags.rd1.field1_true == 0);
	CinternalUnitTestAssertCheck(aFlags.rd1.field1_ongoing_false_to_true == 0);
	CinternalUnitTestAssertCheck(aFlags.rd1.field1_ongoing_true_to_false == 0);
	CinternalUnitTestAssertCheck(aFlags.rd1.field1_false == 1);
	CinternalUnitTestAssertCheck(aFlags.rd1.field2_true == 0);
	CinternalUnitTestAssertCheck(aFlags.rd1.field2_ongoing_false_to_true == 0);
	CinternalUnitTestAssertCheck(aFlags.rd1.field2_ongoing_true_to_false == 0);
	CinternalUnitTestAssertCheck(aFlags.rd1.field2_false == 1);

	aFlags.wr.field1 = CPPUTILS_FOURSTATE_MAKE_BITS_TRUE;
	CinternalUnitTestAssertCheck(aFlags.rd1.field1_true == 1);
	CinternalUnitTestAssertCheck(aFlags.rd1.field1_ongoing_false_to_true == 0);
	CinternalUnitTestAssertCheck(aFlags.rd1.field1_ongoing_true_to_false == 0);
	CinternalUnitTestAssertCheck(aFlags.rd1.field1_false == 0);
	CinternalUnitTestAssertCheck(aFlags.rd1.field2_true == 0);
	CinternalUnitTestAssertCheck(aFlags.rd1.field2_ongoing_false_to_true == 0);
	CinternalUnitTestAssertCheck(aFlags.rd1.field2_ongoing_true_to_false == 0);
	CinternalUnitTestAssertCheck(aFlags.rd1.field2_false == 1);

	aFlags.wr.field1 = CPPUTILS_FOURSTATE_MAKE_BITS_ONGOING_FT;
	CinternalUnitTestAssertCheck(aFlags.rd1.field1_true == 0);
	CinternalUnitTestAssertCheck(aFlags.rd1.field1_ongoing_false_to_true == 1);
	CinternalUnitTestAssertCheck(aFlags.rd1.field1_ongoing_true_to_false == 0);
	CinternalUnitTestAssertCheck(aFlags.rd1.field1_false == 0);
	CinternalUnitTestAssertCheck(aFlags.rd1.field2_true == 0);
	CinternalUnitTestAssertCheck(aFlags.rd1.field2_ongoing_false_to_true == 0);
	CinternalUnitTestAssertCheck(aFlags.rd1.field2_ongoing_true_to_false == 0);
	CinternalUnitTestAssertCheck(aFlags.rd1.field2_false == 1);

	aFlags.wr.field1 = CPPUTILS_FOURSTATE_MAKE_BITS_ONGOING_TF;
	CinternalUnitTestAssertCheck(aFlags.rd1.field1_true == 0);
	CinternalUnitTestAssertCheck(aFlags.rd1.field1_ongoing_false_to_true == 0);
	CinternalUnitTestAssertCheck(aFlags.rd1.field1_ongoing_true_to_false == 1);
	CinternalUnitTestAssertCheck(aFlags.rd1.field1_false == 0);
	CinternalUnitTestAssertCheck(aFlags.rd1.field2_true == 0);
	CinternalUnitTestAssertCheck(aFlags.rd1.field2_ongoing_false_to_true == 0);
	CinternalUnitTestAssertCheck(aFlags.rd1.field2_ongoing_true_to_false == 0);
	CinternalUnitTestAssertCheck(aFlags.rd1.field2_false == 1);

	aFlags.wr.field1 = CPPUTILS_FOURSTATE_MAKE_BITS_FALSE;
	CinternalUnitTestAssertCheck(aFlags.rd1.field1_true == 0);
	CinternalUnitTestAssertCheck(aFlags.rd1.field1_ongoing_false_to_true == 0);
	CinternalUnitTestAssertCheck(aFlags.rd1.field1_ongoing_true_to_false == 0);
	CinternalUnitTestAssertCheck(aFlags.rd1.field1_false == 1);
	CinternalUnitTestAssertCheck(aFlags.rd1.field2_true == 0);
	CinternalUnitTestAssertCheck(aFlags.rd1.field2_ongoing_false_to_true == 0);
	CinternalUnitTestAssertCheck(aFlags.rd1.field2_ongoing_true_to_false == 0);
	CinternalUnitTestAssertCheck(aFlags.rd1.field2_false == 1);

	// field2
	aFlags.wr.field2 = CPPUTILS_FOURSTATE_MAKE_BITS_TRUE;
	CinternalUnitTestAssertCheck(aFlags.rd1.field1_true == 0);
	CinternalUnitTestAssertCheck(aFlags.rd1.field1_ongoing_false_to_true == 0);
	CinternalUnitTestAssertCheck(aFlags.rd1.field1_ongoing_true_to_false == 0);
	CinternalUnitTestAssertCheck(aFlags.rd1.field1_false == 1);
	CinternalUnitTestAssertCheck(aFlags.rd1.field2_true == 1);
	CinternalUnitTestAssertCheck(aFlags.rd1.field2_ongoing_false_to_true == 0);
	CinternalUnitTestAssertCheck(aFlags.rd1.field2_ongoing_true_to_false == 0);
	CinternalUnitTestAssertCheck(aFlags.rd1.field2_false == 0);

	aFlags.wr.field2 = CPPUTILS_FOURSTATE_MAKE_BITS_ONGOING_FT;
	CinternalUnitTestAssertCheck(aFlags.rd1.field1_true == 0);
	CinternalUnitTestAssertCheck(aFlags.rd1.field1_ongoing_false_to_true == 0);
	CinternalUnitTestAssertCheck(aFlags.rd1.field1_ongoing_true_to_false == 0);
	CinternalUnitTestAssertCheck(aFlags.rd1.field1_false == 1);
	CinternalUnitTestAssertCheck(aFlags.rd1.field2_true == 0);
	CinternalUnitTestAssertCheck(aFlags.rd1.field2_ongoing_false_to_true == 1);
	CinternalUnitTestAssertCheck(aFlags.rd1.field2_ongoing_true_to_false == 0);
	CinternalUnitTestAssertCheck(aFlags.rd1.field2_false == 0);

	aFlags.wr.field2 = CPPUTILS_FOURSTATE_MAKE_BITS_ONGOING_TF;
	CinternalUnitTestAssertCheck(aFlags.rd1.field1_true == 0);
	CinternalUnitTestAssertCheck(aFlags.rd1.field1_ongoing_false_to_true == 0);
	CinternalUnitTestAssertCheck(aFlags.rd1.field1_ongoing_true_to_false == 0);
	CinternalUnitTestAssertCheck(aFlags.rd1.field1_false == 1);
	CinternalUnitTestAssertCheck(aFlags.rd1.field2_true == 0);
	CinternalUnitTestAssertCheck(aFlags.rd1.field2_ongoing_false_to_true == 0);
	CinternalUnitTestAssertCheck(aFlags.rd1.field2_ongoing_true_to_false == 1);
	CinternalUnitTestAssertCheck(aFlags.rd1.field2_false == 0);

	aFlags.wr.field2 = CPPUTILS_FOURSTATE_MAKE_BITS_FALSE;
	CinternalUnitTestAssertCheck(aFlags.rd1.field1_true == 0);
	CinternalUnitTestAssertCheck(aFlags.rd1.field1_ongoing_false_to_true == 0);
	CinternalUnitTestAssertCheck(aFlags.rd1.field1_ongoing_true_to_false == 0);
	CinternalUnitTestAssertCheck(aFlags.rd1.field1_false == 1);
	CinternalUnitTestAssertCheck(aFlags.rd1.field2_true == 0);
	CinternalUnitTestAssertCheck(aFlags.rd1.field2_ongoing_false_to_true == 0);
	CinternalUnitTestAssertCheck(aFlags.rd1.field2_ongoing_true_to_false == 0);
	CinternalUnitTestAssertCheck(aFlags.rd1.field2_false == 1);
}
