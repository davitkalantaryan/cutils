
targetName=insert_custom_info_into_bin_test_lib

mkfile_path		=  $(abspath $(lastword $(MAKEFILE_LIST)))
mkfile_dir		=  $(shell dirname $(mkfile_path))

firstTarget: all

COMMON_FLAGS += -fPIC

include $(mkfile_dir)/../../common/common_mkfl/unix.common.Makefile


SOURCES += $(cinternalRepoRoot)/src/tests/insert_custom_info_into_bin_test/entry_insert_custom_info_into_bin_test_lib.c
SOURCES += $(cinternalRepoRoot)/src/tests/insert_custom_info_into_bin_test/insert_custom_info_into_bin_test.c

all: $(artifactRoot)/sys/$(lsbCode)/$(Configuration)/tdll/lib$(targetName).so.1

$(artifactRoot)/sys/$(lsbCode)/$(Configuration)/tdll/lib$(targetName).so.1: \
        $(SOURCES:%=$(artifactRoot)/sys/$(lsbCode)/$(Configuration)/.objects/$(targetName)/%.o)
	@mkdir -p $(@D)
	@mkdir -p $(@D)/../tlib
	@$(LINK) $^ -Wl,-E,-soname,lib$(targetName).so.1 -pie -shared $(LIBS) $(LFLAGS) -o $@
	@rm -f $(@D)/../tlib/lib$(targetName).so
	@cd $(@D)/../tlib && ln -s ../tdll/lib$(targetName).so.1 lib$(targetName).so

.PHONY: clean
clean:
	@rm -rf $(artifactRoot)/sys/$(lsbCode)/$(Configuration)/.objects/$(targetName)
	@rm -f  $(artifactRoot)/sys/$(lsbCode)/$(Configuration)/tdll/lib$(targetName).so*
	@rm -f  $(artifactRoot)/sys/$(lsbCode)/$(Configuration)/tlib/lib$(targetName).so*
	@echo "  " cleaning of $(targetName) complete !!!
