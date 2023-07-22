
targetName=test_lib01

mkfile_path		=  $(abspath $(lastword $(MAKEFILE_LIST)))
mkfile_dir		=  $(shell dirname $(mkfile_path))

firstTarget: all

COMMON_FLAGS += -fPIC

include $(mkfile_dir)/../../common/common_mkfl/flagsandsys_common.unix.Makefile


SOURCES += $(cutilsRepoRoot)/src/tests/entry_test_lib01.cpp

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
