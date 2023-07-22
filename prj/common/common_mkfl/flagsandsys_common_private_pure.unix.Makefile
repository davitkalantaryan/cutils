

mkfile_path		=  $(abspath $(lastword $(MAKEFILE_LIST)))
mkfile_dir		=  $(shell dirname $(mkfile_path))

include $(mkfile_dir)/flagsandsys_common.unix.Makefile
COMMON_FLAGS	+= -I$(cutilsRepoRoot)/src/include
