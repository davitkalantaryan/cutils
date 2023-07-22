#
# repo:			cinternal
# name:			flagsandsys_common.pri
# path:			prj/common/common_qt/flagsandsys_common.pri
# created on:           2023 Jun 21
# created by:           Davit Kalantaryan (davit.kalantaryan@desy.de)
# usage:		Use this qt include file to calculate some platform specific stuff
#


message("!!! $${PWD}/flagsandsys_common.pri")

isEmpty(cinternalFlagsAndSysCommonIncluded){
    cinternalFlagsAndSysCommonIncluded = 1

    cinternalRepoRoot = $${PWD}/../../..

    isEmpty(artifactRoot) {
        artifactRoot = $$(artifactRoot)
	isEmpty(artifactRoot) {
	    artifactRoot = $${cinternalRepoRoot}
	}
    }

    DEFINES += CPPUTILS_COMPILER_WARNINGS_PUSH_POP
    INCLUDEPATH += $${cinternalRepoRoot}/include

    STATIC_LIB_EXTENSION    = a
    LIB_PREFIX		    = lib
    TARGET_PATH_EXTRA	    =

    isEmpty( TARGET_PATH ) {
        contains( TEMPLATE, lib ) {
	    TARGET_PATH=lib
	} else {
	    TARGET_PATH=bin
	}
    }

    win32{
        STATIC_LIB_EXTENSION = lib
	LIB_PREFIX =
	QMAKE_CXXFLAGS += /Wall /WX /sdl-
	contains(QMAKE_TARGET.arch, x86_64) {
	    message ("!!!!!!!!!! windows 64")
	    CODENAME = win_x64
	} else {
	    message ("!!!!!!!!!! windows 32")
	    CODENAME = win_x86
	}
    } else:mac {
        message ("!!!!!!!!!! mac")
	CODENAME = mac
	QMAKE_CXXFLAGS += -Wall
	QMAKE_CXXFLAGS += -Werror
    } else:android {
        # ANDROID_TARGET_ARCH values 1."armeabi-v7a", 2."arm64-v8a", 3."x86", 4."x86_64"
	# x86 and x86_64 are simulators
	#contains(ANDROID_TARGET_ARCH,armeabi-v7a) {
	##ANDROID_EXTRA_LIBS += $$PWD/../platform/android/openssl/armeabi-v7a/libcrypto.so
	##ANDROID_EXTRA_LIBS += $$PWD/../platform/android/openssl/armeabi-v7a/libssl.so
	message("!!!!!!!!!! android: ANDROID_TARGET_ARCH=$$ANDROID_TARGET_ARCH")
	CODENAME = android_$${ANDROID_TARGET_ARCH}
	QMAKE_CXXFLAGS += -Wall
	QMAKE_CXXFLAGS += -Werror
    } else:ios {
        message ("!!!!!!!!!! ios")
	CODENAME = ios
	QMAKE_CXXFLAGS += -Wall
	QMAKE_CXXFLAGS += -Werror
    } else:wasm {
        message ("!!!!!!!!!! wasm")
	STATIC_LIB_EXTENSION	= ba
	CODENAME = wasm
	TARGET_PATH_EXTRA = /$${TARGET}
	QMAKE_CXXFLAGS += -Wall
	QMAKE_CXXFLAGS += -Werror
	QMAKE_CXXFLAGS += -fexceptions
	#QMAKE_CXXFLAGS += -s DISABLE_EXCEPTION_CATCHING=0 -s ASYNCIFY -O3
	QMAKE_CXXFLAGS += -s DISABLE_EXCEPTION_CATCHING=0 -O3 $$(EXTRA_WASM_FLAGS)
    } else:linux {
        CODENAME = $$system(lsb_release -sc)
	message("!!!!!!!!!! linux: Codename:$${CODENAME}")
	QMAKE_CXXFLAGS += -Wall
	QMAKE_CXXFLAGS += -Werror
    } else {
        message("----------------------- Unknown platform")
    }

    CONFIGURATION=Profile
    nameExtension=

    CONFIG(debug, debug|release) {
        nameExtension=d
	CONFIGURATION=Debug
	DEFINES += CPPUTILS_DEBUG
    } else:CONFIG(release, debug|release) {
        CONFIGURATION=Release
    }

    DEFINES	+= CpputilsNameExtension=\\\"$${nameExtension}\\\"
    MAKEFILE	=  Makefile.$${TARGET}.$${CODENAME}.$${CONFIGURATION}
    DESTDIR     =  $${artifactRoot}/sys/$${CODENAME}/$$CONFIGURATION/$${TARGET_PATH}$${TARGET_PATH_EXTRA}
    OBJECTS_DIR =  $${artifactRoot}/sys/$${CODENAME}/$$CONFIGURATION/.other/objects/$${TARGET}
    MOC_DIR     =  $${artifactRoot}/sys/$${CODENAME}/$$CONFIGURATION/.other/mocs/$${TARGET}
    UI_DIR      =  $${artifactRoot}/sys/$${CODENAME}/$$CONFIGURATION/.other/uics/$${TARGET}
}
