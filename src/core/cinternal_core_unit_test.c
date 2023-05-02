//
// file:			cinternal_core_unit_test.c
// path:			src/core/cinternal_core_unit_test.c
// created on:		2023 Apr 15
// created by:		Davit Kalantaryan (davit.kalantaryan@desy.de)
//

#include <cinternal/unit_test.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>


#ifdef _WIN32
#define CINTERNAL_FILE_DELIM01	'\\'
#define CINTERNAL_FILE_DELIM02	'/'
#else
#define CINTERNAL_FILE_DELIM01	'/'
#define CINTERNAL_FILE_DELIM02	'/'
#endif

CPPUTILS_BEGIN_C


static inline const char* FileNameFromPossiblePathInline(const char* a_cpcSrcPath) {
	const char* cpcTerm = strrchr(a_cpcSrcPath,CINTERNAL_FILE_DELIM01);
	if (cpcTerm) { return cpcTerm + 1; }
	cpcTerm = strrchr(a_cpcSrcPath, CINTERNAL_FILE_DELIM02);
	if (cpcTerm) { return cpcTerm + 1; }
	return a_cpcSrcPath;
}


static inline void PrintSourceInformationInline(FILE* a_file, const char* a_cpcSrcPath, int a_line) {
	if (a_cpcSrcPath[0]) {
		const char* cpcReturn = FileNameFromPossiblePathInline(a_cpcSrcPath);
		fprintf(a_file, "src_fl: \"%s\" ", cpcReturn);
	}
	if (a_line >= 0) {
		fprintf(a_file, "src_ln: %d ", a_line);
	}
}


CINTERNAL_EXPORT int CinternalUnitTestCheckRawFn(bool a_condition, const char* a_testName, int a_subtestNumber, const char* a_cpcSrcPath, int a_line)
{
	if (a_condition) {
		switch (a_subtestNumber) {
		case CINTERNAL_UNIT_TEST_SPECIAL_SUBTEST_NUMBER:
			a_testName = FileNameFromPossiblePathInline(a_cpcSrcPath);
			a_subtestNumber = a_line;
			break;
		default:
			PrintSourceInformationInline(stdout, a_cpcSrcPath, a_line);
			break;
		}  //  switch (a_subtestNumber) {
		fprintf(stdout,"OK      => test: \"%s\", subTestNumber: %d\n", a_testName, a_subtestNumber);
		fflush(stdout);
		return 0;
	}
	
	switch (a_subtestNumber) {
	case CINTERNAL_UNIT_TEST_SPECIAL_SUBTEST_NUMBER:
		a_testName = FileNameFromPossiblePathInline(a_cpcSrcPath);
		a_subtestNumber = a_line;
		break;
	default:
		PrintSourceInformationInline(stderr, a_cpcSrcPath, a_line);
		break;
	}  //  switch (a_subtestNumber) {
	fprintf(stderr, "FAILURE => test: \"%s\", subTestNumber: %d is ok\n", a_testName, a_subtestNumber);
	fflush(stderr);
	return 1;
}


CINTERNAL_EXPORT void CinternalUnitTestAssertCheckRawFn(bool a_condition, const char* a_testName, int a_subtestNumber, const char* a_cpcSrcPath, int a_line)
{
	if (a_condition) {
		switch (a_subtestNumber) {
		case CINTERNAL_UNIT_TEST_SPECIAL_SUBTEST_NUMBER:
			a_testName = FileNameFromPossiblePathInline(a_cpcSrcPath);
			a_subtestNumber = a_line;
			break;
		default:
			PrintSourceInformationInline(stdout, a_cpcSrcPath, a_line);
			break;
		}  //  switch (a_subtestNumber) {
		fprintf(stdout, "OK      => test: \"%s\", subTestNumber: %d\n", a_testName, a_subtestNumber);
		fflush(stdout);
		return;
	}

	switch (a_subtestNumber) {
	case CINTERNAL_UNIT_TEST_SPECIAL_SUBTEST_NUMBER:
		a_testName = FileNameFromPossiblePathInline(a_cpcSrcPath);
		a_subtestNumber = a_line;
		break;
	default:
		PrintSourceInformationInline(stderr, a_cpcSrcPath, a_line);
		break;
	}  //  switch (a_subtestNumber) {
	fprintf(stderr, "FAILURE => test: \"%s\", subTestNumber: %d is ok\n", a_testName, a_subtestNumber);
	fflush(stderr);
	exit(1);
}


CPPUTILS_END_C
