//
// repo:			cutils
// file:			cutils_unit_test_0000_initial.c
// path:			src/tests/unit_test/cutils_unit_test_0000_initial.c
// created on:		2023 May 19
// created by:		Davit Kalantaryan (davit.kalantaryan@gmail.com)
//


#include <cutils/tool/unit_test_tools.h>
#include <cutils/unit_test.h>
#include <stdbool.h>


CPPUTILS_UTEST_BEFORE_MAIN(f_0000_initial, t_0001) {
	CinternalUnitTestAssertCheck(true);
}


CPPUTILS_UTEST(f_0000_initial, t_0002) {
	CinternalUnitTestAssertCheck(true);
}


CPPUTILS_UTEST_ALL(f_0000_initial, t_0003) {
	CinternalUnitTestAssertCheck(true);
}
