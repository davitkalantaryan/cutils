
!IFNDEF cutilsRepoRoot
cutilsRepoRoot	= $(MAKEDIR)\..\..\..
!ENDIF

!include <$(cutilsRepoRoot)\prj\common\common_mkfl\flagsandsys_common_pure.windows.Makefile>

CFLAGS				= $(CFLAGS) /I"$(cutilsRepoRoot)\src\include"
