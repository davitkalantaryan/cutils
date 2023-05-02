//
// file:            unit_test.h
// path:			include/cinternal/unit_test.h
// created on:		2023 Apr 15
// created by:		Davit Kalantaryan (davit.kalantaryan@desy.de)
//

#ifndef CINTERNAL_INCLUDE_CINTERNAL_UNIT_TEST_H
#define CINTERNAL_INCLUDE_CINTERNAL_UNIT_TEST_H

#include <cinternal/export_symbols.h>
#include <stdbool.h>

#define CINTERNAL_UNIT_TEST_SPECIAL_SUBTEST_NUMBER		(-11)

CPPUTILS_BEGIN_C


CINTERNAL_EXPORT int  CinternalUnitTestCheckRawFn(bool a_condition, const char* a_testName, int a_subtestNumber, const char* a_cpcSrcPath, int a_line);
CINTERNAL_EXPORT void CinternalUnitTestAssertCheckRawFn(bool a_condition, const char* a_testName, int a_subtestNumber, const char* a_cpcSrcPath, int a_line);


CPPUTILS_END_C


#define CinternalUnitTestCheckRaw(_condition,_testName,_subtestNumber,_cpcSrcPath,_line)	CinternalUnitTestCheckRawFn((_condition)?true:false,_testName,_subtestNumber,_cpcSrcPath,_line)
#define CinternalUnitTestCheck(_condition)	CinternalUnitTestCheckRaw(_condition,"",CINTERNAL_UNIT_TEST_SPECIAL_SUBTEST_NUMBER,__FILE__,__LINE__)
#define CinternalUnitTestAssertCheckRaw(_condition,_testName,_subtestNumber,_cpcSrcPath,_line)	CinternalUnitTestAssertCheckRawFn((_condition)?true:false,_testName,_subtestNumber,_cpcSrcPath,_line)
#define CinternalUnitTestAssertCheck(_condition)	CinternalUnitTestAssertCheckRaw(_condition,"",CINTERNAL_UNIT_TEST_SPECIAL_SUBTEST_NUMBER,__FILE__,__LINE__)


#endif  // #ifndef CINTERNAL_INCLUDE_CINTERNAL_UNIT_TEST_H
