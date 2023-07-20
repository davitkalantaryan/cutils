#
# name:			resolve_common.pri
# path:			${repositoryRoot}/prj/common/common_qt/resolve_common.pri
# created on:           2023 Jun 21
# created by:           Davit Kalantaryan (davit.kalantaryan@desy.de)
# usage:		Use this qt include file to calculate some platform specific stuff
#


message("!!! $${PWD}/resolve_common.pri")
cinternalResolveCommonIncluded = 1

isEmpty( cinternalRepoRoot ) {
        cinternalRepoRoot = $$(cinternalRepoRoot)
        isEmpty(cinternalRepoRoot) {
            cinternalRepoRoot = $${PWD}/../../..
        }
}

isEmpty( repositoryRoot ) {
        repositoryRoot = $$(repositoryRoot)
        isEmpty(repositoryRoot) {
            repositoryRoot = $${cinternalRepoRoot}
        }
}

isEmpty(artifactRoot) {
    artifactRoot = $$(artifactRoot)
    isEmpty(artifactRoot) {
        artifactRoot = $${repositoryRoot}
    }
}
