targetName=unittest

mkfile_path		=  $(abspath $(lastword $(MAKEFILE_LIST)))
mkfile_dir		=  $(shell dirname $(mkfile_path))
# line below is not needed, just here as a example

firstTarget: all

include $(mkfile_dir)/../../common/common_mkfl/sys_common.unix.Makefile

GTEST_SRC_DIR=$(cinternalRepoRoot)/src/tests/unit_test
COMMON_SRC_DIR=$(cinternalRepoRoot)/src/core
TOOLS_SRC_DIR=$(cinternalRepoRoot)/src/tools/cinternal_unit_test

GTEST_SRCS_CPP	= $(shell find $(GTEST_SRC_DIR) -name "*.cpp")
GTEST_SRCS_C	= $(shell find $(GTEST_SRC_DIR) -name "*.c")
COMMON_SRCS	= $(shell find $(COMMON_SRC_DIR) -name "*.c")
TOOLS_SRCS	= $(shell find $(TOOLS_SRC_DIR) -name "*.c")

# c=+ 11 is needed for google test
# CPPFLAGS += -std=c++11

EXTRA_SOURCSES += $(cinternalRepoRoot)/src/core/cinternal_core_unit_test.c
EXTRA_SOURCSES += $(cinternalRepoRoot)/src/core/cinternal_core_list_dllist.c
EXTRA_SOURCSES += $(cinternalRepoRoot)/src/core/cinternal_core_lw_mutex_recursive.c

#LIBS += $(artifactRoot)/sys/$(lsbCode)/$(Configuration)/lib/libgtest_main$(nameExtension).a
#LIBS += $(artifactRoot)/sys/$(lsbCode)/$(Configuration)/lib/libgtest$(nameExtension).a
LIBS += -pthread
#LIBS += -ldl

all: $(artifactRoot)/sys/$(lsbCode)/$(Configuration)/test/$(targetName)

$(artifactRoot)/sys/$(lsbCode)/$(Configuration)/test/$(targetName): \
		$(EXTRA_SOURCSES:%=$(artifactRoot)/sys/$(lsbCode)/$(Configuration)/.objects/$(targetName)/%.o)	\
		$(GTEST_SRCS_CPP:%=$(artifactRoot)/sys/$(lsbCode)/$(Configuration)/.objects/$(targetName)/%.o)	\
		$(GTEST_SRCS_C:%=$(artifactRoot)/sys/$(lsbCode)/$(Configuration)/.objects/$(targetName)/%.o)	\
		$(TOOLS_SRCS:%=$(artifactRoot)/sys/$(lsbCode)/$(Configuration)/.objects/$(targetName)/%.o)
	@mkdir -p $(@D)
	@$(LINK) $^ $(LIBS) $(LFLAGS) -o $@

.PHONY: clean
clean:
	@rm -rf $(artifactRoot)/sys/$(lsbCode)/$(Configuration)/.objects/$(targetName)
	@rm -f  $(artifactRoot)/sys/$(lsbCode)/$(Configuration)/test/$(targetName)
	@echo "  " cleaning of $(targetName) complete !!!
