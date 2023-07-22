#
# file:			any_quick_test.pro
# path:			prj/tests/any_quick_test_qt/any_quick_test.pro
# created on:	2021 Mar 07
# created by:	Davit Kalantaryan
#

message("!!! $${_PRO_FILE_}")
include ( "$${PWD}/../../common/common_qt/flagsandsys_common.pri" )


QT -= gui
QT -= core
QT -= widgets
CONFIG -= qt

LIBS += -pthread
LIBS += -ldl

SOURCES	+=		\
        "$${PWD}/../../../src/tools/freelib_on_remote_proc_by_handle/main_freelib_on_remote_proc_by_handle.c"   \
	"$${PWD}/../../../src/core/cutils_core_parser_argparser01.c"                                         \
	"$${PWD}/../../../src/core/cutils_core_loadfreelib_on_remote_process_unix.c"

HEADERS += $$files($${cutilsRepoRoot}/include/*.h,true)

OTHER_FILES += $$files($${PWD}/../freelib_on_remote_proc_by_handle_mkfl/*.Makefile,false)
