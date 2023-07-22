#!/bin/bash

# script to prepare developer host, to work with the code on this repo

#scriptFileFullPath=`readlink -f ${0}`
#scriptDirectory=`dirname ${scriptFileFullPath}`
#cd ${scriptDirectory}/../..
#repositoryRoot=`pwd`

# in mac os above short calculation will not work
# also realpath utilit is missing in mac

scriptDirectory=`dirname "${0}"`
scriptFileName=`basename "${0}"`
cd "${scriptDirectory}"
fileOrigin=`readlink "${scriptFileName}"` || :
while [ ! -z "${fileOrigin}" ]
do
	scriptDirectory=`dirname "${fileOrigin}"`
	scriptFileName=`basename "${fileOrigin}"`
	cd "${scriptDirectory}"
	fileOrigin=`readlink "${scriptFileName}"`  || :
done
cd ..
repositoryRoot=`pwd`
echo repositoryRoot=$repositoryRoot

cd workspaces/cinternal_all_mkfl
unset CPPUTILS_DEBUG
make -f cinternal_all.unix.Makefile CPPUTILS_RELEASE=1
unset CPPUTILS_RELEASE
make -f cinternal_all.unix.Makefile CPPUTILS_DEBUG=1


cd ${repositoryRoot}/prj/tests/unit_test_test_mult
unset CPPUTILS_DEBUG
make -f unit_test_test.unix.Makefile  CPPUTILS_RELEASE=1
# to make debug use line below
unset CPPUTILS_RELEASE
make -f unit_test_test.unix.Makefile all CPPUTILS_DEBUG=1