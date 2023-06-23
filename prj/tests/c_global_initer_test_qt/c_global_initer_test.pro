#
# file:			any_quick_test.pro
# path:			prj/tests/any_quick_test_qt/any_quick_test.pro
# created on:	2021 Mar 07
# created by:	Davit Kalantaryan
#

include ( "$${PWD}/../../common/common_qt/sys_common.pri" )
include ( "$${PWD}/../../common/common_qt/flags_common.pri" )

DESTDIR     = "$${artifactRoot}/$${SYSTEM_PATH}/$$CONFIGURATION/test"

QT -= gui
QT -= core
QT -= widgets
CONFIG -= qt

LIBS += -pthread

DEFINES += CPPUTILS_USING_STATIC_LIB_OR_OBJECTS

SOURCES	+=		\
        "$${PWD}/../../../src/tests/main_c_global_initer_test.c"

COMMON_HDRS	= $$files($${cinternalRepoRoot}/include/*.h,true)
COMMON_HDRSPP	= $$files($${cinternalRepoRoot}/include/*.hpp,true)

HEADERS += $$COMMON_HDRS
HEADERS += $$COMMON_HDRSPP

OTHER_FILES += $$files($${PWD}/../c_global_initer_test_mkfl/*.Makefile,false)
