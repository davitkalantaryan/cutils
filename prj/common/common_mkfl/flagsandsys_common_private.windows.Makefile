
!IFNDEF cutilsRepoRoot
cutilsRepoRoot	= $(MAKEDIR)\..\..\..
!ENDIF

!include <$(cutilsRepoRoot)\prj\common\common_mkfl\flagsandsys_common_private_pure.windows.Makefile>


!IFNDEF cinternalRepoRoot
cinternalRepoRoot	= $(cutilsRepoRoot)\contrib\cinternal
!ENDIF

!include <$(cinternalRepoRoot)\prj\common\common_mkfl\flagsandsys_common_pure.windows.Makefile>
