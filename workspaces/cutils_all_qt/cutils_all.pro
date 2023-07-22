

TEMPLATE = subdirs
#CONFIG += ordered

include ( "$${PWD}/../../prj/common/common_qt/flagsandsys_common_private.pri" )

cinternalFromHere{
        SUBDIRS	+= "$${cinternalRepoRoot}/workspaces/cinternal_all_qt/cinternal_all.pro"
}


SUBDIRS		+=	"$${cutilsRepoRoot}/prj/tools/freelib_on_remote_proc_by_handle_qt/freelib_on_remote_proc_by_handle.pro"
SUBDIRS		+=	"$${cutilsRepoRoot}/prj/tools/free_libs_by_names_on_remote_proc_qt/free_libs_by_names_on_remote_proc.pro"
SUBDIRS		+=	"$${cutilsRepoRoot}/prj/tools/ld_postload_qt/ld_postload.pro"

SUBDIRS		+=	"$${cutilsRepoRoot}/prj/core/libcintr_init_libdl_qt/libcintr_init_libdl.pro"

SUBDIRS		+=	"$${cutilsRepoRoot}/prj/tests/any_quick_test_qt/any_quick_test.pro"
SUBDIRS		+=	"$${cutilsRepoRoot}/prj/tests/app_to_hack_qt/app_to_hack.pro"
SUBDIRS		+=	"$${cutilsRepoRoot}/prj/tests/lhash_test_qt/lhash_test.pro"
SUBDIRS		+=	"$${cutilsRepoRoot}/prj/tests/llist_test_qt/llist_test.pro"
SUBDIRS		+=	"$${cutilsRepoRoot}/prj/tests/test_lib01_qt/test_lib01.pro"

unitTestHere{
    SUBDIRS		+=	"$${cutilsRepoRoot}/prj/tests/unit_test_test_mult/unit_test_test.pro"
}

OTHER_FILES += $$files($${cutilsRepoRoot}/docs/*.md,true)
OTHER_FILES += $$files($${cutilsRepoRoot}/docs/*.txt,true)
OTHER_FILES += $$files($${cutilsRepoRoot}/scripts/*.sh,true)
OTHER_FILES += $$files($${cutilsRepoRoot}/scripts/*.bat,true)
OTHER_FILES += $$files($${cutilsRepoRoot}/.github/*.yml,true)
OTHER_FILES += $$files($${cutilsRepoRoot}/prj/common/common_mkfl/*.Makefile,true)
OTHER_FILES += $$files($${cutilsRepoRoot}/workspaces/cinternal_all_mkfl/*.Makefile,true)

OTHER_FILES	+=	\
        "$${cutilsRepoRoot}/.gitattributes"						\
	"$${cutilsRepoRoot}/.gitignore"							\
	"$${cutilsRepoRoot}/LICENSE"							\
	"$${cutilsRepoRoot}/README.md"
