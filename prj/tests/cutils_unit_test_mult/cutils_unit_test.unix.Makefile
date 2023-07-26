
targetName=cutils_unit_test

mkfile_path		=  $(abspath $(lastword $(MAKEFILE_LIST)))
mkfile_dir		=  $(shell dirname $(mkfile_path))
# line below is not needed, just here as a example

firstTarget: all

#COMMON_FLAGS += -DCinternalAddUnitTestFunction_defined
#COMMON_FLAGS += -DCinternalIterateAndCallUnitTestFunctions_defined

include $(mkfile_dir)/../../common/common_mkfl/flagsandsys_common_private.unix.Makefile

UTEST_SRCS_DIR=$(cutilsRepoRoot)/src/tests/unit_test
CORE_SRCS_DIR=$(cutilsRepoRoot)/src/core

UTEST_SRCS_CPP	= $(shell find $(UTEST_SRCS_DIR) -name "*.cpp")
UTEST_SRCS_C	= $(shell find $(UTEST_SRCS_DIR) -name "*.c")
#CORE_SRCS	= $(shell find $(CORE_SRCS_DIR) -name "*.c")

EXTRA_SOURCSES += $(cutilsRepoRoot)/src/core/cutils_core_hash_dllhash.c
EXTRA_SOURCSES += $(cutilsRepoRoot)/src/core/cutils_core_list_dllist.c
EXTRA_SOURCSES += $(cutilsRepoRoot)/src/core/cutils_core_unit_test_add_remove_functions_example.c
EXTRA_SOURCSES += $(cinternalRepoRoot)/src/core/cinternal_core_unit_test_tools_and_main.c
EXTRA_SOURCSES += $(cinternalRepoRoot)/src/core/cinternal_core_logger.c

LIBS += -pthread
LIBS += -ldl

all: $(artifactRoot)/sys/$(lsbCode)/$(Configuration)/test/$(targetName)

$(artifactRoot)/sys/$(lsbCode)/$(Configuration)/test/$(targetName): \
		$(EXTRA_SOURCSES:%=$(artifactRoot)/sys/$(lsbCode)/$(Configuration)/.objects/$(targetName)/%.o)	\
		$(UTEST_SRCS_CPP:%=$(artifactRoot)/sys/$(lsbCode)/$(Configuration)/.objects/$(targetName)/%.o)	\
		$(UTEST_SRCS_C:%=$(artifactRoot)/sys/$(lsbCode)/$(Configuration)/.objects/$(targetName)/%.o)
	@mkdir -p $(@D)
	@$(LINK) $^ $(LIBS) $(LFLAGS) -o $@

.PHONY: clean
clean:
	@rm -rf $(artifactRoot)/sys/$(lsbCode)/$(Configuration)/.objects/$(targetName)
	@rm -f  $(artifactRoot)/sys/$(lsbCode)/$(Configuration)/test/$(targetName)
	@echo "  " cleaning of $(targetName) complete !!!
