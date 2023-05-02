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

include ( "$${PWD}/../../common/common_qt/sys_common.pri" )
include ( "$${PWD}/../../common/common_qt/flags_common.pri" )


QT -= gui
QT -= core
QT -= widgets
CONFIG -= qt

LIBS += -ldl

repoRootPath=$${PWD}/../../..

INCLUDEPATH += "$${PWD}/../../../include"
DEFINES += CPPUTILS_USING_STATIC_LIB_OR_OBJECTS


#SOURCES += $$files($${PWD}/../../../src/core/*.c*,true)
SOURCES	+=		\
        "$${PWD}/../../../src/core/init_libdl/entry_cinternal_core_init_libdl.c"

COMMON_HDRS	= $$files($${repoRootPath}/include/*.h,true)
COMMON_HDRSPP	= $$files($${repoRootPath}/include/*.hpp,true)

HEADERS += $$COMMON_HDRS
HEADERS += $$COMMON_HDRSPP

OTHER_FILES += $$files($${PWD}/../libcintr_init_libdl_mkfl/*.Makefile,false)
