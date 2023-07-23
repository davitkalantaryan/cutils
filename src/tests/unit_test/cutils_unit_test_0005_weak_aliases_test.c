//
// repo:            cutils
// file:			cutils_unit_test_0005_weak_aliases_test.c
// path:			src/tests/unit_test/cutils_unit_test_0005_weak_aliases_test.c
// created on:		2023 Jul 23
// created by:		Davit Kalantaryan (davit.kalantaryan@gmail.com)
//

#include <cinternal/unit_test_tools.h>
#include <cinternal/unit_test.h>
#include <stdlib.h>


static int s_nNumberOfFunctionCall = 0;


CPPUTILS_UTEST_ALL(cutils_unit_test_0005_weak_aliases_test, t_0001) {

    ++s_nNumberOfFunctionCall;
}


CPPUTILS_BEGIN_C


static void cutils_unit_test_0005_weak_aliases_test_clean(void) {
    CinternalUnitTestAssertCheck(s_nNumberOfFunctionCall==2);
}


CPPUTILS_C_CODE_INITIALIZER(cutils_unit_test_0005_weak_aliases_test_init) {

    s_nNumberOfFunctionCall = 0;
    atexit(&cutils_unit_test_0005_weak_aliases_test_clean);
}

CPPUTILS_END_C
