#
# file:			any_quick_test.pro
# path:			prj/tests/any_quick_test_qt/any_quick_test.pro
# created on:	2021 Mar 07
# created by:	Davit Kalantaryan
#

include ( "$${PWD}/../../common/common_qt/sys_common.pri" )
include ( "$${PWD}/../../common/common_qt/flags_common.pri" )


QT -= gui
QT -= core
QT -= widgets
CONFIG -= qt

LIBS += -pthread
LIBS += -ldl

INCLUDEPATH += "$${PWD}/../../../src/include"
DEFINES += CPPUTILS_USING_STATIC_LIB_OR_OBJECTS


#SOURCES += $$files($${PWD}/../../../src/core/*.c*,true)
SOURCES	+=		\
        "$${PWD}/../../../src/tools/freelib_on_remote_proc_by_handle/main_freelib_on_remote_proc_by_handle.c"   \
        "$${PWD}/../../../src/core/cinternal_core_parser_argparser01.c"                                         \
        "$${PWD}/../../../src/core/cinternal_core_loadfreelib_on_remote_process_unix.c"

COMMON_HDRS	= $$files($${cinternalRepoRoot}/include/*.h,true)
COMMON_HDRSPP	= $$files($${cinternalRepoRoot}/include/*.hpp,true)

HEADERS += $$COMMON_HDRS
HEADERS += $$COMMON_HDRSPP

OTHER_FILES += $$files($${PWD}/../freelib_on_remote_proc_by_handle_mkfl/*.Makefile,false)
