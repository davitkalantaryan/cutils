//
// file:			insert_custom_info_into_bin_test.c
// path:			src/tests/insert_custom_info_into_bin_test/insert_custom_info_into_bin_test.c
// created on:		2023 Feb 28
// created by:		Davit Kalantaryan (davit.kalantaryan@desy.de)
//



#include <cinternal/insert_info_to_bin.h>


#define COMMIT_ID	e6ae7a2e4e7100532b6884d1534f4c8399067413

CPPUTILS_INSERT_COMMENT_TO_BIN_RAW(".cintr", "__commit-id=" CPPUTILS_STRVAL(COMMIT_ID))
