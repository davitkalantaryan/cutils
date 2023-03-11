//
// file:            entry_test_lib01.c
// path:			src/tests/entry_test_lib01.c
// created on:		2023 Mar 10
// created by:		Davit Kalantaryan (davit.kalantaryan@desy.de)
//

#include <cinternal/export_symbols.h>
#include <stdio.h>


CPPUTILS_BEGIN_C


CPPUTILS_CODE_INITIALIZER(entry_test_lib01_init) {
	printf("file:%s, ln:%d, fn:%s\n",__FILE__,__LINE__,__FUNCTION__);
}


CPPUTILS_END_C
