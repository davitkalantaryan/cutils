#
# file:		windows.common.Makefile
# created on:	2020 Dec 14
# created by:	
#
# This file can be only as include
#


!IFNDEF MakeFileDir
MakeFileDir			= $(MAKEDIR)
!ENDIF

!IFNDEF RepoRootDir
RepoRootDir			= $(MakeFileDir)\..\..\..
!ENDIF

!IFNDEF cutilsRepoRoot
cutilsRepoRoot	= $(RepoRootDir)
!ENDIF

CFLAGS				= $(CFLAGS) /I"$(cutilsRepoRoot)\include"
