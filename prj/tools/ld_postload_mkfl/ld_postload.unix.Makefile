
targetName=ld_postload

mkfile_path		=  $(abspath $(lastword $(MAKEFILE_LIST)))
mkfile_dir		=  $(shell dirname $(mkfile_path))

firstTarget: all


COMMON_FLAGS	+= -I$(cinternalRepoRoot)/src/include

include $(mkfile_dir)/../../common/common_mkfl/flagsandsys_common_private.unix.Makefile


SOURCES += $(cutilsRepoRoot)/src/tools/ld_postload/main_cinternal_tools_ld_postload.c
SOURCES += $(cutilsRepoRoot)/src/core/cutils_core_parser_argparser01.c
SOURCES += $(cutilsRepoRoot)/src/core/cutils_core_loadfreelib_on_remote_process_unix.c
SOURCES += $(cutilsRepoRoot)/src/core/cutils_core_list_dllist.c
SOURCES += $(cutilsRepoRoot)/src/intern/cutils_core_intern_tokenizer01_common.c                            
SOURCES += $(cutilsRepoRoot)/src/core/cutils_core_parser_tokenizer01.c

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
