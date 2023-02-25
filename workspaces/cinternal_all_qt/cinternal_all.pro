

TEMPLATE = subdirs
#CONFIG += ordered

include ( "$${PWD}/../../prj/common/common_qt/flags_common.pri" )
repositoryRoot = $${PWD}/../..

SUBDIRS		+=	"$${repositoryRoot}/prj/tests/any_quick_test_qt/any_quick_test.pro"
SUBDIRS		+=	"$${repositoryRoot}/prj/tests/c_raii_test_qt/c_raii_test.pro"
SUBDIRS		+=	"$${repositoryRoot}/prj/tests/lhash_test_qt/lhash_test.pro"
SUBDIRS		+=	"$${repositoryRoot}/prj/tests/llist_test_qt/llist_test.pro"

OTHER_FILES += $$files($${repositoryRoot}/docs/*.md,true)
OTHER_FILES += $$files($${repositoryRoot}/docs/*.txt,true)

OTHER_FILES	+=	\
        "$${repositoryRoot}/.gitattributes"					\
	"$${repositoryRoot}/.gitignore"						\
	"$${repositoryRoot}/LICENSE"						\
	"$${repositoryRoot}/README.md"						\
	"$${PWD}/../../prj/common/common_mkfl/unix.common.Makefile"		\
	"$${PWD}/../../prj/common/common_mkfl/windows.common.Makefile"
