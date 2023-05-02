//
// file:            cinternal_core_replace_function_unix.c
// path:			src/core/windows/cinternal_core_replace_function_unix.c
// created on:		2023 Mar 18
// created by:		Davit Kalantaryan (davit.kalantaryan@desy.de)
//


#include <cinternal/internal_header.h>

#ifndef _WIN32


#include <cinternal/loadfreelib_on_remote_process_sys.h>
#include <cinternal/loadfreelib_on_remote_process.h>


CPPUTILS_BEGIN_C


#ifndef _GNU_SOURCE
#define  _GNU_SOURCE
#endif
#ifndef __USE_GNU
#define  __USE_GNU
#endif
#include <stddef.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <dlfcn.h>
#include <sys/ptrace.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/user.h>

#define CINTR_BUFFER_MAX_SIZE   1024

static char  s_vcLibDlName[CINTR_BUFFER_MAX_SIZE];
static unsigned long long int s_lib_dl_address_here;


static inline unsigned long long int FindLibraryOffsetByPid(const char* a_library, int a_pid) {
    char mapFilename[1024];
    char buffer[9076];
    FILE* fdMaps;
    unsigned long long int addr = 0;

    snprintf(mapFilename, sizeof(mapFilename), "/proc/%d/maps", a_pid);

    fdMaps = fopen(mapFilename, "r");
    if(!fdMaps){
        return 0;
    }

    while(fgets(buffer, sizeof(buffer), fdMaps)) {
        if (strstr(buffer, a_library)) {
            addr = strtoull(buffer, CPPUTILS_NULL, 16);
            break;
        }
    }

    fclose(fdMaps);

    return addr;
}


int main(int a_argc, char* a_argv[])
{
	unsigned long long int lib_dl_address_on_remote;
	unsigned long long int dlopen_address_here,dlopen_address_on_remote;
	unsigned long long int dlerror_address_here,dlerror_address_on_remote;
	void* handle;
	char* error;
	int pid;
	
	if(a_argc<2){
		fprintf(stderr,"pid of process is not provided\n");
		return 1;
	}
	
	pid = atoi(a_argv[1]);
	if(pid<1){
		fprintf(stderr,"bad pid\n");
		return 1;
	}
	
	handle = dlopen(s_vcLibDlName, RTLD_LAZY);
	if (!handle) {
		fprintf(stderr,"Unable to open libdl\n");
		return 1;
	}
	
	dlopen_address_here = (unsigned long long int)dlsym(handle, "dlopen");
	if ((error = dlerror()) != CPPUTILS_NULL)  {
		dlclose(handle);
		CPPUTILS_STATIC_CAST(void,error);
		fprintf(stderr,"Unable to get address for dlopen\n");
		return 1;
	}
	
	dlerror_address_here = (unsigned long long int)dlsym(handle, "dlerror");
	if ((error = dlerror()) != CPPUTILS_NULL)  {
		dlclose(handle);
		CPPUTILS_STATIC_CAST(void,error);
		fprintf(stderr,"Unable to get address for dlclose\n");
		return 1;
	}
		
	dlclose(handle);
	
	lib_dl_address_on_remote = FindLibraryOffsetByPid(s_vcLibDlName, pid);
	
	dlopen_address_on_remote = lib_dl_address_on_remote + (dlopen_address_here - s_lib_dl_address_here);
	printf("dlopen_address_on_remote = %llu\n",dlopen_address_on_remote);
	
	dlerror_address_on_remote = lib_dl_address_on_remote + (dlerror_address_here - s_lib_dl_address_here);
	printf("dlerror_address_on_remote = %llu\n",dlerror_address_on_remote);
	
	return 0;
}


CPPUTILS_CODE_INITIALIZER(cinternal_main_unix_helper_to_get_sym_address_on_process){
    char mapFilename[1024];
    char buffer[9076];
    FILE* fdMaps;
    size_t unStrLenMin1;

    snprintf(mapFilename, sizeof(mapFilename), "/proc/self/maps");

    fdMaps = fopen(mapFilename, "r");
    if(!fdMaps){
        exit(1);
    }

    while(fgets(buffer, sizeof(buffer), fdMaps)) {
        if (strstr(buffer, "libdl")) {
            char* pcFileName = strrchr(buffer,'/');
			fclose(fdMaps);
            if(pcFileName){
                ++pcFileName;
            }
            else{
                pcFileName = buffer;
            }
            unStrLenMin1 = strlen(pcFileName)-1;
            if(pcFileName[unStrLenMin1]=='\n'){
                pcFileName[unStrLenMin1] = 0;
            }
            else{
                ++unStrLenMin1;
            }
            memcpy(s_vcLibDlName,pcFileName,unStrLenMin1);
			s_lib_dl_address_here = strtoull(buffer, CPPUTILS_NULL, 16);
			if(!s_lib_dl_address_here){
				exit(1);
			}
            return;
        }
    }

    fclose(fdMaps);
    exit(1);
}


CPPUTILS_END_C


#endif  //  #ifndef _WIN32
