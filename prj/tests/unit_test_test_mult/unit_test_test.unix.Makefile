targetName=unittest

mkfile_path		=  $(abspath $(lastword $(MAKEFILE_LIST)))
mkfile_dir		=  $(shell dirname $(mkfile_path))
# line below is not needed, just here as a example
repoRootPath	:= $(shell curDir=`pwd` && cd $(mkfile_dir)/../../.. && pwd && cd ${curDir})

firstTarget: all

include $(mkfile_dir)/../../common/common_mkfl/unix.common.Makefile

GTEST_SRC_DIR=$(repoRootPath)/src/tests/unit_test
COMMON_SRC_DIR=$(repoRootPath)/src/core
TOOLS_SRC_DIR=$(repoRootPath)/src/tools/cinternal_unit_test

GTEST_SRCS_CPP	= $(shell find $(GTEST_SRC_DIR) -name "*.cpp")
GTEST_SRCS_C	= $(shell find $(GTEST_SRC_DIR) -name "*.c")
COMMON_SRCS	= $(shell find $(COMMON_SRC_DIR) -name "*.c")
TOOLS_SRCS	= $(shell find $(TOOLS_SRC_DIR) -name "*.c")

#CPPFLAGS += -I$(repoRootPath)/contrib/googletest/googletest/include
# c=+ 11 is needed for google test
CPPFLAGS += -std=c++11

EXTRA_SOURCSES += $(repoRootPath)/src/core/cinternal_core_unit_test.c
EXTRA_SOURCSES += $(repoRootPath)/src/core/cinternal_core_list_dllist.c

#LIBS += $(repoRootPath)/sys/$(lsbCode)/$(Configuration)/lib/libgtest_main$(nameExtension).a
#LIBS += $(repoRootPath)/sys/$(lsbCode)/$(Configuration)/lib/libgtest$(nameExtension).a
LIBS += -pthread
#LIBS += -ldl

all: $(repoRootPath)/sys/$(lsbCode)/$(Configuration)/test/$(targetName)

$(repoRootPath)/sys/$(lsbCode)/$(Configuration)/test/$(targetName): \
			$(EXTRA_SOURCSES:%=$(repoRootPath)/sys/$(lsbCode)/$(Configuration)/.objects/$(targetName)/%.o)	\
			$(GTEST_SRCS_CPP:%=$(repoRootPath)/sys/$(lsbCode)/$(Configuration)/.objects/$(targetName)/%.o)	\
			$(GTEST_SRCS_C:%=$(repoRootPath)/sys/$(lsbCode)/$(Configuration)/.objects/$(targetName)/%.o)	\
			$(TOOLS_SRCS:%=$(repoRootPath)/sys/$(lsbCode)/$(Configuration)/.objects/$(targetName)/%.o)
	@mkdir -p $(@D)
	@$(LINK) $^ $(LIBS) $(LFLAGS) -o $@

.PHONY: clean
clean:
	@rm -rf $(repoRootPath)/sys/$(lsbCode)/$(Configuration)/.objects/$(targetName)
	@rm -f  $(repoRootPath)/sys/$(lsbCode)/$(Configuration)/test/$(targetName)
	@echo "  " cleaning of unit_test complete !!!
