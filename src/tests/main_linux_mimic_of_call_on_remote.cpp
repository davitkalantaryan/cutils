//
// file:            main_linux_mimic_of_call_on_remote.cpp
// path:			src/tests/main_linux_mimic_of_call_on_remote.cpp
// created on:		2023 Mar 22
// created by:		Davit Kalantaryan (davit.kalantaryan@desy.de)
//


#include <cinternal/disable_compiler_warnings.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

#include <dlfcn.h>

typedef void* (*TypeDlopen)(const char *filename, int flags);
typedef char* (*TypeDlerror)(void);

static int TryCallsStatic(void);

int main(void)
{
	void* pRet;
    printf("linux_mimic_of_call_on_remote version 01 started. Pid is: %d  . Going to infinite loop\n", (int)getpid());
	
	fprintf(stdout,"Press any key then enter to continue  ");
	(void)getchar();
	
	pRet = dlopen("libtest_lib01.so.1",2);
	printf("pRet = %p\n",pRet);
	
	if(pRet){
		dlclose(pRet);
	}
	else{
		char* pcDlError = dlerror();
		printf("pcDlError = \"%s\"\n",pcDlError?pcDlError:"nil");
	}
	
	while(1){
		if(TryCallsStatic()){
			break;
		}
	}
		
	return 0;
}


static int TryCallsStatic(void)
{
	char* pcTerm;
	char* pcBuffer = CPPUTILS_NULL;
	size_t unSize = 0;
	unsigned long long int addressDlopen = 0, addressDlerror = 0;
	TypeDlopen fnDlOpen;
	TypeDlerror fnDlError;
	void* pRet;
	
	fprintf(stdout,"dlopenAddress = ");
	fflush(stdout);
	while(getline(&pcBuffer,&unSize,stdin)<2){
		free(pcBuffer);
		pcBuffer = CPPUTILS_NULL;
		unSize = 0;
	}
	if((pcBuffer[0]=='0')&&((pcBuffer[1]=='x')||(pcBuffer[1]=='X'))){
		addressDlopen = strtoll(pcBuffer+2,&pcTerm,10);
	}
	else{
		addressDlopen = strtoll(pcBuffer,&pcTerm,10);
	}
	if(!addressDlopen){
		fprintf(stderr,"bad address is provided, going to exit\n");
		return 1;
	}
	fnDlOpen = (TypeDlopen)addressDlopen;
	free(pcBuffer);
	pcBuffer = CPPUTILS_NULL;
	unSize = 0;
	
	
	fprintf(stdout,"dlerrorAddress = ");
	fflush(stdout);
	while(getline(&pcBuffer,&unSize,stdin)<2){
		free(pcBuffer);
		pcBuffer = CPPUTILS_NULL;
		unSize = 0;
	}
	if((pcBuffer[0]=='0')&&((pcBuffer[1]=='x')||(pcBuffer[1]=='X'))){
		addressDlerror = strtoll(pcBuffer+2,&pcTerm,10);
	}
	else{
		addressDlerror = strtoll(pcBuffer,&pcTerm,10);
	}
	if(!addressDlerror){
		fprintf(stderr,"bad address is provided, going to exit\n");
		return 1;
	}
	fnDlError = (TypeDlerror)addressDlerror;
	free(pcBuffer);
	pcBuffer = CPPUTILS_NULL;
	unSize = 0;
	
	
	pRet = (*fnDlOpen)("libtest_lib01.so.1",2);
	printf("pRet = %p\n",pRet);
	
	if(!pRet){
		char* pcDlError = (*fnDlError)();
		printf("pcDlError = \"%s\"\n",pcDlError?pcDlError:"nil");
	}
	
	return 0;
}
