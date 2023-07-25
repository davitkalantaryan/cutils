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

LIBS += -pthread

SOURCES	+=		\
        "$${PWD}/../../../src/tests/main_lhash_test.c"              \
	"$${PWD}/../../../src/core/cutils_core_hash_dllhash.c"   \
	"$${cinternalRepoRoot}/src/core/cinternal_core_unit_test_tools_and_main.c"	\
	"$${cinternalRepoRoot}/src/core/cinternal_core_logger.c"

HEADERS += $$files($${cutilsRepoRoot}/include/*.h,true)

OTHER_FILES += $$files($${PWD}/../lhash_test_mkfl/*.Makefile,false)
