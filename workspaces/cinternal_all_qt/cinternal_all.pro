

TEMPLATE = subdirs
#CONFIG += ordered

include ( "$${PWD}/../../prj/common/common_qt/flags_common.pri" )
repositoryRoot = $${PWD}/../..

INCLUDEPATH += $${PWD}/../../include

SUBDIRS		+=	"$${repositoryRoot}/prj/tools/freelib_on_remote_proc_by_handle_qt/freelib_on_remote_proc_by_handle.pro"
SUBDIRS		+=	"$${repositoryRoot}/prj/tools/free_libs_by_names_on_remote_proc_qt/free_libs_by_names_on_remote_proc.pro"
SUBDIRS		+=	"$${repositoryRoot}/prj/tools/ld_postload_qt/ld_postload.pro"

SUBDIRS		+=	"$${repositoryRoot}/prj/core/libcintr_init_libdl_qt/libcintr_init_libdl.pro"

SUBDIRS		+=	"$${repositoryRoot}/prj/tests/any_quick_test_qt/any_quick_test.pro"
SUBDIRS		+=	"$${repositoryRoot}/prj/tests/app_to_hack_qt/app_to_hack.pro"
SUBDIRS		+=	"$${repositoryRoot}/prj/tests/c_global_initer_test_qt/c_global_initer_test.pro"
SUBDIRS		+=	"$${repositoryRoot}/prj/tests/c_raii_test_qt/c_raii_test.pro"
SUBDIRS		+=	"$${repositoryRoot}/prj/tests/c_raii_test_unix_qt/c_raii_test_unix.pro"
SUBDIRS		+=	"$${repositoryRoot}/prj/tests/insert_custom_info_into_bin_test_exe_qt/insert_custom_info_into_bin_test_exe.pro"
SUBDIRS		+=	"$${repositoryRoot}/prj/tests/insert_custom_info_into_bin_test_lib_qt/insert_custom_info_into_bin_test_lib.pro"
SUBDIRS		+=	"$${repositoryRoot}/prj/tests/lhash_test_qt/lhash_test.pro"
SUBDIRS		+=	"$${repositoryRoot}/prj/tests/llist_test_qt/llist_test.pro"
SUBDIRS		+=	"$${repositoryRoot}/prj/tests/test_lib01_qt/test_lib01.pro"

unitTestHere{
    SUBDIRS		+=	"$${repositoryRoot}/prj/tests/unit_test_test_mult/unit_test_test.pro"
}

OTHER_FILES += $$files($${repositoryRoot}/docs/*.md,true)
OTHER_FILES += $$files($${repositoryRoot}/docs/*.txt,true)
OTHER_FILES += $$files($${repositoryRoot}/scripts/*.sh,true)
OTHER_FILES += $$files($${repositoryRoot}/scripts/*.bat,true)
OTHER_FILES += $$files($${repositoryRoot}/.github/*.yml,true)

OTHER_FILES	+=	\
        "$${repositoryRoot}/.gitattributes"						\
	"$${repositoryRoot}/.gitignore"							\
	"$${repositoryRoot}/LICENSE"							\
	"$${repositoryRoot}/README.md"							\
	"$${repositoryRoot}/workspaces/cinternal_all_mkfl/cinternal_all.unix.Makefile"	\
	"$${PWD}/../../prj/common/common_mkfl/unix.common.Makefile"			\
	"$${PWD}/../../prj/common/common_mkfl/windows.common.Makefile"
