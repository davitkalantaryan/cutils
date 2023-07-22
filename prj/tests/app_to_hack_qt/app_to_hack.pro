#
# file:			any_quick_test.pro
# path:			prj/tests/any_quick_test_qt/any_quick_test.pro
# created on:	2021 Mar 07
# created by:	Davit Kalantaryan
#

message("!!! $${_PRO_FILE_}")
include ( "$${PWD}/../../common/common_qt/flagsandsys_common.pri" )

DESTDIR     = "$${artifactRoot}/sys/$${CODENAME}/$$CONFIGURATION/test"

QT -= gui
QT -= core
QT -= widgets
CONFIG -= qt


SOURCES	+=		\
        "$${PWD}/../../../src/tests/main_app_to_hack.cpp"


HEADERS += $$files($${cutilsRepoRoot}/include/*.h,true)

OTHER_FILES += $$files($${PWD}/../app_to_hack_mkfl/*.Makefile,false)
