
targetName=c_raii_test

mkfile_path		=  $(abspath $(lastword $(MAKEFILE_LIST)))
mkfile_dir		=  $(shell dirname $(mkfile_path))

firstTarget: all

include $(mkfile_dir)/../../common/common_mkfl/unix.common.Makefile


SOURCES += $(cinternalRepoRoot)/src/tests/c_raii_test/main_c_raii_test.c
SOURCES += $(cinternalRepoRoot)/src/tests/c_raii_test/c_raii_test_cpp01.cpp

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
