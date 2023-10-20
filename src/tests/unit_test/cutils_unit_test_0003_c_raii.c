//
// repo:            cutils
// file:			cutils_unit_test_0003_c_raii.c
// path:			src/tests/unit_test/cutils_unit_test_0003_c_raii.c
// created on:		2023 Jun 20
// created by:		Davit Kalantaryan (davit.kalantaryan@gmail.com)
//

#include <cinternal/unit_test.h>
#include <cinternal/c_raii.h>
#include <stddef.h>



static int  s_nRaiiResult = 0;

static void dummy_c_raii_test(int a_nIncrement);


CPPUTILS_UTEST_ALL(f_0003_c_raii, t_0001) {

    s_nRaiiResult = 0;
    dummy_c_raii_test(1);
    dummy_c_raii_test(2);
    CinternalUnitTestAssertCheckOpt(s_nRaiiResult == 3);
}



CPPUTILS_UTEST_ALL(f_0003_c_raii, t_0002) {

    s_nRaiiResult = 0;
    dummy_c_raii_test(1);
    dummy_c_raii_test(2);
    dummy_c_raii_test(5);
    CinternalUnitTestAssertCheckOpt(s_nRaiiResult == 8);
}


static void cleanup_func(void** CPPUTILS_ARG_NN a_ppData) {
    // perform cleanup actions here
    const int cnIncrement = (int)((size_t)(*a_ppData));
    s_nRaiiResult += cnIncrement;
}


static void dummy_c_raii_test(int a_nIncrement)
{
    // let's check if even after early return cleanup is called
    CINTERNAL_C_RAII_CODE_START(cleanup_func, (void*)((size_t)a_nIncrement)) {
        return;
    }CINTERNAL_C_RAII_CODE_END
}
