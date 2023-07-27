#
# file:			any_quick_test.pro
# path:			prj/tests/any_quick_test_qt/any_quick_test.pro
# created on:	2021 Mar 07
# created by:	Davit Kalantaryan
#

message("!!! $${_PRO_FILE_}")
include ( "$${PWD}/../../common/common_qt/flagsandsys_common_private.pri" )

DESTDIR     = "$${artifactRoot}/sys/$${CODENAME}/$$CONFIGURATION/test"


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
        "$${PWD}/../../../src/tools/ld_postload/main_cutils_tools_ld_postload.c"     \
	"$${PWD}/../../../src/core/cutils_core_parser_tokenizer01.c"                 \
	"$${PWD}/../../../src/core/cutils_core_list_dllist.c"                         \
	"$${PWD}/../../../src/core/cutils_core_parser_argparser01.c"                 \
	"$${PWD}/../../../src/intern/cutils_core_intern_tokenizer01_common.c"        \
	"$${PWD}/../../../src/core/cutils_core_loadfreelib_on_remote_process_unix.c"	\
	"$${PWD}/../../../src/core/cutils_core_loadfreelib_on_remote_process_windows.c"

HEADERS += $$files($${cutilsRepoRoot}/include/*.h,true)

OTHER_FILES += $$files($${PWD}/../ld_postload_mkfl/*.Makefile,false)
