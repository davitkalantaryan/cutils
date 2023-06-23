//
// file:			c_raii_test_cpp01.cpp
// path:			src/tests/c_raii_test/c_raii_test_cpp01.cpp
// created on:		2023 Feb 25
// created by:		Davit Kalantaryan (davit.kalantaryan@desy.de)
//


#include <cinternal/internal_header.h>
#include <stdio.h>


static void dummy_c_raii_test_static(void)
{
	printf("%s\n", __FUNCTION__);
	throw "Hi";
}

CPPUTILS_BEGIN_C


void dummy_c_raii_test(void)
{
	printf("%s\n", __FUNCTION__);
	dummy_c_raii_test_static();
}


CPPUTILS_END_C
