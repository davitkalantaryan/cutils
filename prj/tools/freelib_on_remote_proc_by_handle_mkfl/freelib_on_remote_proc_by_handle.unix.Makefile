
targetName=freelib_on_remote_proc_by_handle

mkfile_path		=  $(abspath $(lastword $(MAKEFILE_LIST)))
mkfile_dir		=  $(shell dirname $(mkfile_path))

firstTarget: all

include $(mkfile_dir)/../../common/common_mkfl/flagsandsys_common.unix.Makefile


SOURCES += $(cutilsRepoRoot)/src/tools/freelib_on_remote_proc_by_handle/main_freelib_on_remote_proc_by_handle.c
SOURCES += $(cutilsRepoRoot)/src/core/cutils_core_parser_argparser01.c
SOURCES += $(cutilsRepoRoot)/src/core/cutils_core_loadfreelib_on_remote_process_unix.c

all: $(artifactRoot)/sys/$(lsbCode)/$(Configuration)/bin/$(targetName)

$(artifactRoot)/sys/$(lsbCode)/$(Configuration)/bin/$(targetName): \
        $(SOURCES:%=$(artifactRoot)/sys/$(lsbCode)/$(Configuration)/.objects/$(targetName)/%.o)
	@mkdir -p $(@D)
	@$(LINK) $^ $(LIBS) -ldl $(LFLAGS) -o $@

.PHONY: clean
clean:
	@rm -rf $(artifactRoot)/sys/$(lsbCode)/$(Configuration)/.objects/$(targetName)
	@rm -f  $(artifactRoot)/sys/$(lsbCode)/$(Configuration)/bin/$(targetName)
	@echo "  " cleaning of $(targetName) complete !!!
