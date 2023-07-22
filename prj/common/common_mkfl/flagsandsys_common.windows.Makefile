#
# file:		windows.common.Makefile
# created on:	2020 Dec 14
# created by:	
#
# This file can be only as include
#


!IFNDEF cutilsRepoRoot
cutilsRepoRoot	= $(MAKEDIR)\..\..\..
!ENDIF

!include <$(cutilsRepoRoot)\prj\common\common_mkfl\flagsandsys_common_pure.windows.Makefile>


!IFNDEF cinternalRepoRoot
cinternalRepoRoot	= $(cutilsRepoRoot)\contrib\cinternal
!ENDIF

!include <$(cinternalRepoRoot)\prj\common\common_mkfl\flagsandsys_common_pure.windows.Makefile>
