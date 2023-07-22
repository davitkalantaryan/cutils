//
// repo:			cutils
// file:            unit_test.h
// path:			include/cutils/tool/unit_test.h
// created on:		2023 May 19
// created by:		Davit Kalantaryan (davit.kalantaryan@desy.de)
// explanation:		tools for unit test
//

#ifndef CUTILS_INCLUDE_CUTILS_TOOL_UNIT_TEST_TOOLS_H
#define CUTILS_INCLUDE_CUTILS_TOOL_UNIT_TEST_TOOLS_H


#include <cinternal/internal_header.h>

CPPUTILS_BEGIN_C

#ifndef CPPUTILS_UNIT_TEST_NOEXCEPT
#define CPPUTILS_UNIT_TEST_NOEXCEPT CPPUTILS_NOEXCEPT
#endif


CPPUTILS_DLL_PRIVATE void CinternalAddUnitTestFunction(void (*a_function)(void));


#define CPPUTILS_UTEST_BEFORE_MAIN(_maj,_min)	CPPUTILS_CODE_INITIALIZER(cinternal_unit_test_bm_ ## _maj ## _min)

#define CPPUTILS_UTEST(_maj,_min)	static void cinternal_unit_test_ ## _maj ## _min (void) CPPUTILS_UNIT_TEST_NOEXCEPT;	\
	CPPUTILS_CODE_INITIALIZER(cinternal_unit_test_adder_ ## _maj ## _min){						\
		CinternalAddUnitTestFunction(& cinternal_unit_test_ ## _maj ## _min);					\
	}																							\
	static void cinternal_unit_test_ ## _maj ## _min (void) CPPUTILS_UNIT_TEST_NOEXCEPT


#define CPPUTILS_UTEST_ALL(_maj,_min)	static void cinternal_unit_test_ ## _maj ## _min (void) CPPUTILS_UNIT_TEST_NOEXCEPT;\
	CPPUTILS_CODE_INITIALIZER(cinternal_unit_test_adder_ ## _maj ## _min){						\
		CinternalAddUnitTestFunction(& cinternal_unit_test_ ## _maj ## _min);					\
		cinternal_unit_test_ ## _maj ## _min ();												\
	}																							\
	static void cinternal_unit_test_ ## _maj ## _min (void) CPPUTILS_UNIT_TEST_NOEXCEPT 



CPPUTILS_END_C


#endif  //  #ifndef CUTILS_INCLUDE_CUTILS_TOOL_UNIT_TEST_TOOLS_H
