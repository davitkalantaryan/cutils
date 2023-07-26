#
# repo:         cutils
# file:			cutils_unit_test.pro
# path:			prj/tests/cutils_unit_test_mult/cutils_unit_test.pro
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

LIBS += -ldl
LIBS += -pthread

HEADERS += $$files($${cutilsRepoRoot}/include/*.h,true)
HEADERS += $$files($${cutilsRepoRoot}/src/*.h,true)

SOURCES += $$files($${cutilsRepoRoot}/src/tests/unit_test/*.c,true)
SOURCES += $$files($${cutilsRepoRoot}/src/tests/unit_test/*.cpp,true)
SOURCES += \
    "$${cutilsRepoRoot}/src/core/cutils_core_hash_dllhash.c"				\
    "$${cutilsRepoRoot}/src/core/cutils_core_list_dllist.c"				\
    "$${cutilsRepoRoot}/src/core/cutils_core_unit_test_add_remove_functions_example.c"	\
    "$${cinternalRepoRoot}/src/core/cinternal_core_logger.c"				\
    "$${cinternalRepoRoot}/src/core/cinternal_core_unit_test_tools_and_main.c"

OTHER_FILES += $$files($${PWD}/*.Makefile,false)
