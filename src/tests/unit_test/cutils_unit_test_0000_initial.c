//
// repo:			cutils
// file:			cutils_unit_test_0000_initial.c
// path:			src/tests/unit_test/cutils_unit_test_0000_initial.c
// created on:		2023 May 19
// created by:		Davit Kalantaryan (davit.kalantaryan@gmail.com)
//


#include <cinternal/unit_test.h>
#include <stdbool.h>


CPPUTILS_EXTERN_C CPPUTILS_DLL_PRIVATE int s_nMagicNumber = 0;


CPPUTILS_UTEST_BEFORE_MAIN(f_0000_initial, t_0001) {
	CinternalUnitTestAssertCheck(true);
}


CPPUTILS_UTEST_AFTER_MAIN(f_0000_initial, t_0002_testing_weak_functions) {
	CinternalUnitTestAssertCheck(s_nMagicNumber == 1);
	CinternalUnitTestAssertCheck(true);
}


CPPUTILS_UTEST_ALL(f_0000_initial, t_0003) {
	CinternalUnitTestAssertCheck(true);
}
