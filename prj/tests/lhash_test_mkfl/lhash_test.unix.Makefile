
targetName=lhash_test

mkfile_path		=  $(abspath $(lastword $(MAKEFILE_LIST)))
mkfile_dir		=  $(shell dirname $(mkfile_path))

firstTarget: all

include $(mkfile_dir)/../../common/common_mkfl/unix.common.Makefile


SOURCES += $(cinternalRepoRoot)/src/tests/main_lhash_test.c
SOURCES += $(cinternalRepoRoot)/src/core/cinternal_core_hash_dllhash.c
SOURCES += $(cinternalRepoRoot)/src/core/cinternal_core_unit_test.c

all: $(repoRootPath)/sys/$(lsbCode)/$(Configuration)/test/$(targetName)

$(repoRootPath)/sys/$(lsbCode)/$(Configuration)/test/$(targetName): \
	$(SOURCES:%=$(repoRootPath)/sys/$(lsbCode)/$(Configuration)/.objects/$(targetName)/%.o)
	@mkdir -p $(@D)
	@$(LINK) $^ $(LIBS) $(LFLAGS) -o $@

.PHONY: clean
clean:
	@rm -rf $(repoRootPath)/sys/$(lsbCode)/$(Configuration)/.objects/$(targetName)
	@rm -f  $(repoRootPath)/sys/$(lsbCode)/$(Configuration)/test/$(targetName)
	@echo "  " cleaning of googletest complete !!!
