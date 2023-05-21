

CONFIG -= qt

include ($${PWD}/../../common/common_qt/sys_common.pri)


INCLUDEPATH += $${cinternalRepoRoot}/include

LIBS += -ldl
LIBS += -pthread

HEADERS += $$files($${cinternalRepoRoot}/include/*.h,true)
HEADERS += $$files($${cinternalRepoRoot}/include/*.hpp,true)
HEADERS += $$files($${cinternalRepoRoot}/src/*.h,true)
HEADERS += $$files($${cinternalRepoRoot}/src/*.hpp,true)

SOURCES += $$files($${cinternalRepoRoot}/src/tests/unit_test/*.c,true)
SOURCES += $$files($${cinternalRepoRoot}/src/tests/unit_test/*.cpp,true)
SOURCES += $$files($${cinternalRepoRoot}/src/tools/cinternal_unit_test/*.c,true)
SOURCES += $$files($${cinternalRepoRoot}/src/tools/cinternal_unit_test/*.cpp,true)
SOURCES += $$files($${cinternalRepoRoot}/src/core/*.c,true)
SOURCES += $$files($${cinternalRepoRoot}/src/core/*.cpp,true)

OTHER_FILES += $$files($${PWD}/*.Makefile,false)