

targetName=cutils_all

mkfile_path		=  $(abspath $(lastword $(MAKEFILE_LIST)))
mkfile_dir		=  $(shell dirname $(mkfile_path))

ifndef cutilsRepoRoot
        cutilsRepoRoot	:= $(shell curDir=`pwd` && cd $(mkfile_dir)/../.. && pwd && cd ${curDir})
endif

osSystem		:= $(shell uname)

ifeq ($(osSystem),Darwin)

all: all_common

else

all: all_common all_no_mac

endif
	

all_no_mac:
	$(MAKE) -f $(cutilsRepoRoot)/prj/tools/freelib_on_remote_proc_by_handle_mkfl/freelib_on_remote_proc_by_handle.unix.Makefile			&& \
	$(MAKE) -f $(cutilsRepoRoot)/prj/tools/free_libs_by_names_on_remote_proc_mkfl/free_libs_by_names_on_remote_proc.unix.Makefile		&& \
	$(MAKE) -f $(cutilsRepoRoot)/prj/tools/ld_postload_mkfl/ld_postload.unix.Makefile													&& \
	$(MAKE) -f $(cutilsRepoRoot)/prj/core/libcintr_init_libdl_mkfl/libcintr_init_libdl.unix.Makefile									&& \
	$(MAKE) -f $(cutilsRepoRoot)/prj/tests/app_to_hack_mkfl/app_to_hack.unix.Makefile													&& \
	$(MAKE) -f $(cutilsRepoRoot)/prj/tests/test_lib01_mkfl/test_lib01.unix.Makefile

all_common:
	$(MAKE) -f $(cutilsRepoRoot)/prj/tests/cutils_unit_test_mult/cutils_unit_test.unix.Makefile											&& \
	$(MAKE) -f $(cutilsRepoRoot)/prj/tests/any_quick_test_mkfl/any_quick_test.unix.Makefile												&& \
	$(MAKE) -f $(cutilsRepoRoot)/prj/tests/lhash_test_mkfl/lhash_test.unix.Makefile														&& \
	$(MAKE) -f $(cutilsRepoRoot)/prj/tests/llist_test_mkfl/llist_test.unix.Makefile


clean_no_mac:
	$(MAKE) -f $(cutilsRepoRoot)/prj/tools/freelib_on_remote_proc_by_handle_mkfl/freelib_on_remote_proc_by_handle.unix.Makefile clean
	$(MAKE) -f $(cutilsRepoRoot)/prj/tools/free_libs_by_names_on_remote_proc_mkfl/free_libs_by_names_on_remote_proc.unix.Makefile clean
	$(MAKE) -f $(cutilsRepoRoot)/prj/tools/ld_postload_mkfl/ld_postload.unix.Makefile clean
	$(MAKE) -f $(cutilsRepoRoot)/prj/core/libcintr_init_libdl_mkfl/libcintr_init_libdl.unix.Makefile clean	
	$(MAKE) -f $(cutilsRepoRoot)/prj/tests/app_to_hack_mkfl/app_to_hack.unix.Makefile clean
	$(MAKE) -f $(cutilsRepoRoot)/prj/tests/test_lib01_mkfl/test_lib01.unix.Makefile clean

clean_common:
	$(MAKE) -f $(cutilsRepoRoot)/prj/tests/cutils_unit_test_mult/cutils_unit_test.unix.Makefile clean
	$(MAKE) -f $(cutilsRepoRoot)/prj/tests/any_quick_test_mkfl/any_quick_test.unix.Makefile clean
	$(MAKE) -f $(cutilsRepoRoot)/prj/tests/lhash_test_mkfl/lhash_test.unix.Makefile clean
	$(MAKE) -f $(cutilsRepoRoot)/prj/tests/llist_test_mkfl/llist_test.unix.Makefile clean
	

ifeq ($(osSystem),Darwin)

.PHONY: clean
clean: clean_common

else

.PHONY: clean
clean: clean_common clean_no_mac

endif
