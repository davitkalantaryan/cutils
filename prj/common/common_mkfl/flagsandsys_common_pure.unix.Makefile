

mkfile_path		=  $(abspath $(lastword $(MAKEFILE_LIST)))
mkfile_dir		=  $(shell dirname $(mkfile_path))

cutilsRepoRoot	:= $(shell curDir=`pwd` && cd $(mkfile_dir)/../../.. && pwd && cd ${curDir})

ifndef artifactRoot
        artifactRoot	= $(cutilsRepoRoot)
endif

include $(cutilsRepoRoot)/contrib/cinternal/prj/common/common_mkfl/flagsandsys_common_pure.unix.Makefile
COMMON_FLAGS	+= -I$(cutilsRepoRoot)/include
