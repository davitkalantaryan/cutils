#
# file:		libcintr_init_libdl.pro
# path:		prj/core/libcintr_init_libdl_qt/libcintr_init_libdl.pro
# created on:	2021 Mar 23
# created by:	Davit Kalantaryan
#

TEMPLATE = lib
CONFIG += dll
CONFIG -= static
TARGET = cintr_init_libdl

message("!!! $${_PRO_FILE_}")
include ( "$${PWD}/../../common/common_qt/flagsandsys_common.pri" )

DESTDIR     = "$${artifactRoot}/sys/$${CODENAME}/$$CONFIGURATION/tlib"


QT -= gui
QT -= core
QT -= widgets
CONFIG -= qt

LIBS += -ldl


SOURCES	+=		\
        "$${PWD}/../../../src/core/init_libdl/entry_cutils_core_init_libdl.c"

HEADERS += $$files($${cutilsRepoRoot}/include/*.h,true)

OTHER_FILES += $$files($${PWD}/../libcintr_init_libdl_mkfl/*.Makefile,false)
