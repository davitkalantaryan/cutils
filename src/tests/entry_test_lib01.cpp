//
// file:            entry_test_lib01.c
// path:			src/tests/entry_test_lib01.c
// created on:		2023 Mar 10
// created by:		Davit Kalantaryan (davit.kalantaryan@desy.de)
//

#include <cinternal/export_symbols.h>
#include <stdio.h>
#include <stdlib.h>


CPPUTILS_BEGIN_C


static int entry_test_lib01_clean(void)
{
	printf("file:%s, ln:%d, fn:%s\n", __FILE__, __LINE__, __FUNCTION__);
	return 0;
}


CPPUTILS_CODE_INITIALIZER(entry_test_lib01_init) {
	printf("file:%s, ln:%d, fn:%s\n",__FILE__,__LINE__,__FUNCTION__);
	_onexit(&entry_test_lib01_clean);
}


CPPUTILS_END_C
