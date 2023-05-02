
targetName=insert_custom_info_into_bin_test_lib

mkfile_path		=  $(abspath $(lastword $(MAKEFILE_LIST)))
mkfile_dir		=  $(shell dirname $(mkfile_path))

firstTarget: all

COMMON_FLAGS += -fPIC

include $(mkfile_dir)/../../common/common_mkfl/unix.common.Makefile


SOURCES += $(cinternalRepoRoot)/src/tests/insert_custom_info_into_bin_test/entry_insert_custom_info_into_bin_test_lib.c
SOURCES += $(cinternalRepoRoot)/src/tests/insert_custom_info_into_bin_test/insert_custom_info_into_bin_test.c

all: $(repoRootPath)/sys/$(lsbCode)/$(Configuration)/dll/lib$(targetName).so.1

$(repoRootPath)/sys/$(lsbCode)/$(Configuration)/dll/lib$(targetName).so.1: \
	$(SOURCES:%=$(repoRootPath)/sys/$(lsbCode)/$(Configuration)/.objects/$(targetName)/%.o)
	@mkdir -p $(@D)
	@mkdir -p $(@D)/../lib
	@$(LINK) $^ -Wl,-E,-soname,lib$(targetName).so.1 -pie -shared $(LIBS) $(LFLAGS) -o $@
	@rm -f $(@D)/../lib/lib$(targetName).so
	@cd $(@D)/../lib && ln -s ../dll/lib$(targetName).so.1 lib$(targetName).so

.PHONY: clean
clean:
	@rm -rf $(repoRootPath)/sys/$(lsbCode)/$(Configuration)/.objects/$(targetName)
	@rm -f  $(repoRootPath)/sys/$(lsbCode)/$(Configuration)/dll/lib$(targetName).so.1
	@rm -f  $(repoRootPath)/sys/$(lsbCode)/$(Configuration)/lib/lib$(targetName).so
	@echo "  " cleaning of googletest complete !!!
