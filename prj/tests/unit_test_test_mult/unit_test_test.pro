

CONFIG -= qt

message("!!! $${_PRO_FILE_}")
include ( "$${PWD}/../../common/common_qt/flagsandsys_common.pri" )


LIBS += -ldl
LIBS += -pthread

HEADERS += $$files($${cutilsRepoRoot}/include/*.h,true)
HEADERS += $$files($${cutilsRepoRoot}/src/*.h,true)

SOURCES += $$files($${cutilsRepoRoot}/src/tests/unit_test/*.c,true)
SOURCES += $$files($${cutilsRepoRoot}/src/tests/unit_test/*.cpp,true)
SOURCES += $$files($${cutilsRepoRoot}/src/core/*.c,true)
SOURCES += $$files($${cutilsRepoRoot}/src/core/*.cpp,true)

OTHER_FILES += $$files($${PWD}/*.Makefile,false)
