#
# file:			any_quick_test.pro
# path:			prj/tests/any_quick_test_qt/any_quick_test.pro
# created on:	2021 Mar 07
# created by:	Davit Kalantaryan
#

TEMPLATE = lib

message("!!! $${_PRO_FILE_}")
include ( "$${PWD}/../../common/common_qt/flagsandsys_common.pri" )

DESTDIR     = "$${artifactRoot}/sys/$${CODENAME}/$$CONFIGURATION/test"

QT -= gui
QT -= core
QT -= widgets
CONFIG -= qt

win32{
} else {
	LIBS += -pthread
}


SOURCES	+=		\
        "$${PWD}/../../../src/tests/entry_test_lib01.cpp"

HEADERS += $$files($${cinternalRepoRoot}/include/*.h,true)

OTHER_FILES += $$files($${PWD}/../test_lib01_mkfl/*.Makefile,false)
