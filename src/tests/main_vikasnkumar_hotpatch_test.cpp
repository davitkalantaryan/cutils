//
// file:            main_vikasnkumar_hotpatch_test.cpp
// path:			src/tests/main_vikasnkumar_hotpatch_test.cpp
// created on:		2023 Mar 22
// created by:		Davit Kalantaryan (davit.kalantaryan@desy.de)
//


#include <stdio.h>
#include <stdlib.h>
#include <hotpatch.h>



int main(int a_argc, char* a_argv[])
{
	uintptr_t outAdr, outRes;
	pid_t pid;
	hotpatch_t* pHotpatch;
	
	if(a_argc<2){
		fprintf(stderr,"pid is not provided\n");
		return 1;
	}
	
	pid = (pid_t)atoi(a_argv[1]);
	if(pid<1){
		fprintf(stderr,"Bad pid\n");
		return 1;
	}
	
	pHotpatch = hotpatch_create(pid, 6);
	if(!pHotpatch){
		fprintf(stderr,"Unable to create hotpatch data\n");
		return 1;
	}
	
	if(hotpatch_inject_library(pHotpatch,"libtest_lib01.so.1",NULL,NULL,0,&outAdr,&outRes)){
		hotpatch_destroy(pHotpatch);
		fprintf(stderr,"hotpatch_inject_library failed\n");
		return 1;
	}
	
	hotpatch_destroy(pHotpatch);
	return 0;
	
}
