//
// file:			main_c_raii_test.c
// path:			src/tests/c_raii_test/main_c_raii_test.c
// created on:		2023 Feb 25
// created by:		Davit Kalantaryan (davit.kalantaryan@desy.de)
//


#include <cinternal/c_raii.h>
#include <stdio.h>


extern void dummy_c_raii_test(void);

void cleanup_func(void** CPPUTILS_ARG_NO_NULL a_ppData) {
    // perform cleanup actions here
    printf("%s, a_pData=%p\n", __FUNCTION__, *a_ppData);
}

int main(void) 
{
    printf("%s 1\n", __FUNCTION__);

#ifdef _MSC_VER

    CINTERNAL_C_RAII_ANY_CLEAN_CODE_START
        // guarded code
        dummy_c_raii_test();
    CINTERNAL_C_RAII_ANY_CLEAN_CODE_END
        // termination code
        cleanup_func(NULL);
    CINTERNAL_C_RAII_ANY_CLEAN_END

    printf("%s 2\n", __FUNCTION__);

#endif  //  #ifdef _MSC_VER

    CINTERNAL_C_RAII_CODE_START(cleanup_func, NULL) {
        dummy_c_raii_test();
    }CINTERNAL_C_RAII_CODE_END


    printf("%s 3\n", __FUNCTION__);

    return 0;
}
