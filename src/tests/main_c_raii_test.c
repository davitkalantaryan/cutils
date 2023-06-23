//
// file:			main_c_raii_test.c
// path:			src/tests/c_raii_test/main_c_raii_test.c
// created on:		2023 Feb 25
// created by:		Davit Kalantaryan (davit.kalantaryan@desy.de)
//


#include <cinternal/c_raii.h>
#include <stdio.h>


static void cleanup_func(void** CPPUTILS_ARG_NN a_ppData) {
    // perform cleanup actions here
    printf("%s, a_pData=%p\n", __FUNCTION__, *a_ppData);
}

static void dummy_c_raii_test1(void);
static void dummy_c_raii_test2(void);
static void dummy_c_raii_test3(void);


int main(void) 
{
    printf("%s 1\n", __FUNCTION__);


    CINTERNAL_C_RAII_CODE_START(cleanup_func, NULL) {
        dummy_c_raii_test1();
    }CINTERNAL_C_RAII_CODE_END

    dummy_c_raii_test2();
    dummy_c_raii_test3();


    printf("%s 3\n", __FUNCTION__);

    return 0;
}


static void dummy_c_raii_test1(void)
{
    // let's check if even after early return cleanup is called
    CINTERNAL_C_RAII_CODE_START(cleanup_func, (void*)1) {
        return;
    }CINTERNAL_C_RAII_CODE_END
}


static void dummy_c_raii_test2(void)
{
    // let's check if even after early return cleanup is called
    CINTERNAL_C_RAII_CODE_START(cleanup_func, NULL) {
        return;
    }CINTERNAL_C_RAII_CODE_END
}


static void dummy_c_raii_test3(void)
{
    // let's check if even after early return cleanup is called
    CINTERNAL_C_RAII_CODE_START(cleanup_func, NULL) {
        return;
    }CINTERNAL_C_RAII_CODE_END
}
