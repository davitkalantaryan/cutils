#
# repo:		cutils
# file:		flagsandsys_common_pure.windows.Makefile
# created on:	2020 Dec 14
# created by:	Davit Kalantaryan (davit.kalantaryan@desy.de)
# purpose:	This file can be only as include
#

!IFNDEF MakeFileDir
MakeFileDir			= $(MAKEDIR)\..
!ENDIF

!IFNDEF cutilsRepoRoot
cutilsRepoRoot	= $(MakeFileDir)\..\..\..
!ENDIF

!IFNDEF artifactRoot
artifactRoot	= $(cutilsRepoRoot)
!ENDIF

!IFNDEF cinternalRepoRoot
cinternalRepoRoot	= $(cutilsRepoRoot)\contrib\cinternal
!ENDIF

!include <$(cinternalRepoRoot)\prj\common\common_mkfl\flagsandsys_common.windows.Makefile>

CFLAGS				= $(CFLAGS) /I"$(cutilsRepoRoot)\include"

LFLAGS				= $(LFLAGS) /LIBPATH:"$(cutilsRepoRoot)\sys\win_$(Platform)\$(Configuration)\lib"
LFLAGS				= $(LFLAGS) /LIBPATH:"$(cutilsRepoRoot)\sys\win_$(Platform)\$(Configuration)\tlib"
