#
# file:			any_quick_test.pro
# path:			prj/tests/any_quick_test_qt/any_quick_test.pro
# created on:	2021 Mar 07
# created by:	Davit Kalantaryan
#

message("!!! $${_PRO_FILE_}")
include ( "$${PWD}/../../common/common_qt/flagsandsys_common_private.pri" )


QT -= gui
QT -= core
QT -= widgets
CONFIG -= qt
CONFIG += console

win32{
} else {
	LIBS += -pthread
	LIBS += -ldl
}


SOURCES	+=		\
        "$${PWD}/../../../src/tools/free_libs_by_names_on_remote_proc/main_free_libs_by_names_on_remote_proc.c"     \
	"$${PWD}/../../../src/core/cutils_core_parser_argparser01.c"                                             \
	"$${PWD}/../../../src/core/cutils_core_loadfreelib_on_remote_process_unix.c"                             \
	"$${PWD}/../../../src/core/cutils_core_loadfreelib_on_remote_process_windows.c"								\
	"$${PWD}/../../../src/core/cutils_core_list_dllist.c"                                                     \
	"$${PWD}/../../../src/intern/cutils_core_intern_tokenizer02_common.c"                                    \
	"$${PWD}/../../../src/core/cutils_core_parser_tokenizer01.c"


HEADERS += $$files($${cutilsRepoRoot}/include/*.h,true)

OTHER_FILES += $$files($${PWD}/../free_libs_by_names_on_remote_proc_mkfl/*.Makefile,false)
