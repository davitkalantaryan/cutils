# cinternal  
  
  
## Introduction  
  
If you are doing C development then you will find here some stuff (headers some tools as well example files) to help with it (C development).  
  
  
## What is available 
  
  
### Compiler and system detection  
  
Depending on the compiler and OS a lot of macroses are defined in the file [internal_header.h](include/cinternal/internal_header.h). 
Below is a snippet from that file  
  
```c 
#ifdef _MSC_VER

	#if defined(_WIN64) || defined(_M_ARM)
		#define CPPUTILS_FNAME_PREFIX ""
		#define CPPUTILS_DS_FNAME_POSTFIX
		#define CPPUTILS_SEC_CH_FNC_NAME	"__security_check_cookie"
	#else
		#define CPPUTILS_FNAME_PREFIX "_"
		#define CPPUTILS_DS_FNAME_POSTFIX	"@12"
		#define CPPUTILS_SEC_CH_FNC_NAME	"@__security_check_cookie@4"
	#endif

    #define CPPUTILS_C_CODE_INITIALIZER_RAW(_sect,f) \
        __pragma(section(_sect,read)) \
        static void f(void); \
        __declspec(allocate(_sect)) void (*f##_)(void) = f; \
        __pragma(comment(linker,"/include:" CPPUTILS_FNAME_PREFIX #f "_")) \
        static void f(void)

    #define CPPUTILS_C_CODE_INITIALIZER(f)  CPPUTILS_C_CODE_INITIALIZER_RAW(".CRT$XCU",f)

	#undef cpputils_alloca
	#define cpputils_alloca	_alloca
	#define CPPUTILS_UNREACHABLE_CODE(_code)
	//#if _MSC_FULL_VER
	#if (_MSC_VER>1900) // 1900 is VS2015
		#pragma warning (disable:5045)
		#pragma warning (disable:5247)
		#pragma warning (disable:5248)
	#endif
	// assignment within conditional expression (https://docs.microsoft.com/en-us/cpp/error-messages/compiler-warnings/compiler-warning-level-4-c4706?view=msvc-160)
	#pragma warning (disable:4706) 
	// https://docs.microsoft.com/en-us/cpp/error-messages/compiler-warnings/compiler-warning-level-1-c4711?view=msvc-160
	#pragma warning (disable:4711)
	// Function not inlined althou defined to be inline. 
	// this can happen also with library functions, so this should be disabled
	// https://docs.microsoft.com/en-us/cpp/error-messages/compiler-warnings/compiler-warning-level-1-c4711?view=msvc-160
	#pragma warning (disable:4710)
	#define CPPUTILS_BEFORE_CPP_17_FALL_THR
    #define CPPUTILS_DLL_PUBLIC		__declspec(dllexport)
    #define CPPUTILS_DLL_PRIVATE
    #define CPPUTILS_IMPORT_FROM_DLL	__declspec(dllimport)
	#define CPPUTILS_THREAD_LOCAL		__declspec(thread)
	#if !defined(_WIN64) && !defined(_M_ARM64)
		#define CPPUTLS_32_BIT
	#endif
#elif defined(__GNUC__) || defined(__clang__) || defined(LINUX_GCC)

	#define CPPUTILS_C_CODE_INITIALIZER(f)	static void __attribute__ ((__constructor__)) f(void)

    #define CPPUTILS_MAY_ALIAS  __attribute__ ((__may_alias__))
	#define CPPUTILS_UNREACHABLE_CODE(_code)	_code ;
	#if __GNUC__>=7
		#define CPPUTILS_BEFORE_CPP_17_FALL_THR	__attribute__ ((fallthrough)) ;
	#elif defined(__has_attribute)
		#if __has_attribute (fallthrough)
			#define CPPUTILS_BEFORE_CPP_17_FALL_THR	__attribute__ ((fallthrough)) ;
		#else
			#define CPPUTILS_BEFORE_CPP_17_FALL_THR		/* FALLTHRU */
		#endif
	#else
		#define CPPUTILS_BEFORE_CPP_17_FALL_THR		/* FALLTHRU */
	#endif  // #if __GNUC__>=7
    //#define CPPUTILS_DLL_PUBLIC		__attribute__((visibility("default")))
    #define CPPUTILS_DLL_PUBLIC
    #define CPPUTILS_DLL_PRIVATE		__attribute__((visibility("hidden")))
    #define CPPUTILS_IMPORT_FROM_DLL
	#define CPPUTILS_THREAD_LOCAL		__thread
#elif defined(__CYGWIN__)

	#define CPPUTILS_C_CODE_INITIALIZER(f)	static void __attribute__ ((__constructor__)) f(void)

	#define CPPUTILS_UNREACHABLE_CODE(_code)	_code ;
	#define CPPUTILS_BEFORE_CPP_17_FALL_THR	__attribute__ ((fallthrough)) ;
    #define CPPUTILS_DLL_PUBLIC		__attribute__((dllexport))
    #define CPPUTILS_DLL_PRIVATE
    #define CPPUTILS_IMPORT_FROM_DLL	__attribute__((dllimport))
#elif defined(__MINGW64__) || defined(__MINGW32__)

	#define CPPUTILS_C_CODE_INITIALIZER(f)	static void __attribute__ ((__constructor__)) f(void)

	#define CPPUTILS_UNREACHABLE_CODE(_code)	_code ;
	#define CPPUTILS_BEFORE_CPP_17_FALL_THR	__attribute__ ((fallthrough)) ;
    #define CPPUTILS_DLL_PUBLIC		_declspec(dllexport)
    #define CPPUTILS_DLL_PRIVATE
    #define CPPUTILS_IMPORT_FROM_DLL	_declspec(dllimport)
#elif defined(__SUNPRO_CC)

	#define CPPUTILS_C_CODE_INITIALIZER(f)	static void f(void); _Pragma(init  (f)) static void f(void)

	#define CPPUTILS_UNREACHABLE_CODE(_code)	_code ;
	// #define CPPUTILS_BEFORE_CPP_17_FALL_THR	__attribute__ ((fallthrough)) ; // ???
	#define CPPUTILS_BEFORE_CPP_17_FALL_THR
    #define CPPUTILS_DLL_PUBLIC
    #define CPPUTILS_DLL_PRIVATE		__hidden
    #define CPPUTILS_IMPORT_FROM_DLL
#endif  // #ifdef _MSC_VER
```  
  
This file can be used directly, or one can check and use it in a custom way (for example one can find a global initialization definition way for C (like global constructors in C++)).  
  
  
### Global initializers  
  
As you know there is no standard way to make global initialization in the case of C (like C++ global constructors). 
This tool (C++ global constructors) are very useful for initializing code blocks (static lib, dynamic lib, or just a bunch of sources).
In the case of GCC, there is a `__attribute__ ((__constructor__))`, but this is available only for GCC and family (clang, WASM, CYGWIN).
Here you will find approaches for all major compilers and the good thing is that they are unified by the macros `CPPUTILS_C_CODE_INITIALIZER`.
Below is the code snippet from the file [main_c_global_initer_test.c](src/tests/main_c_global_initer_test.c).  
  
```C  
#include <cinternal/export_symbols.h>
#include <stdio.h>
#include <assert.h>

#define CINTERNALS_GLB_CONS_DSGN_VAL	1

static int s_nData = 0;

CPPUTILS_CODE_INITIALIZER(code_init) {
    printf("Hello from C global constructor\n");
	s_nData = CINTERNALS_GLB_CONS_DSGN_VAL;
}

int main(void)
{
	printf("s_nData = %d\n", s_nData);
	assert(s_nData == CINTERNALS_GLB_CONS_DSGN_VAL);
	return 0;
}
```  
  
If you compile and run this code then you will see `Hello from C global constructor` text in the console.
This text is there because of below global initialization  
  
```C  

...

CPPUTILS_CODE_INITIALIZER(code_init) {
    printf("Hello from C global constructor\n");
	s_nData = CINTERNALS_GLB_CONS_DSGN_VAL;
}

...

```  
  
  
### RAII in C  
  
Another very useful thing in C++ is RAII (Resource Acquisition Is initialization). There is no standard in C also for this.
For this purpose stuff was prepared.
In the case of Windows, it will handle also exceptions (even C++ throw will be handled).
Below is the snippet of the file [main_c_raii_test.c](src/tests/c_raii_test/main_c_raii_test.c).  
  
```C  
#include <cinternal/c_raii.h>
#include <stdio.h>


extern void dummy_c_raii_test(void);

void cleanup_func(void** CPPUTILS_ARG_NO_NULL a_ppData) {
    // perform cleanup actions here
    printf("%s, a_pData=%p\n", __FUNCTION__, *a_ppData);
}

int main(void) 
{
    printf("%s 1\n", __FUNCTION__);

#ifdef _MSC_VER

    CINTERNAL_C_RAII_ANY_CLEAN_CODE_START
        // guarded code
        dummy_c_raii_test();
    CINTERNAL_C_RAII_ANY_CLEAN_CODE_END
        // termination code
        cleanup_func(NULL);
    CINTERNAL_C_RAII_ANY_CLEAN_END

    printf("%s 2\n", __FUNCTION__);

#endif  //  #ifdef _MSC_VER

    CINTERNAL_C_RAII_CODE_START(cleanup_func, NULL) {
        dummy_c_raii_test();
    }CINTERNAL_C_RAII_CODE_END


    printf("%s 3\n", __FUNCTION__);

    return 0;
}
```  
  
  
### Some tools  
 1. Hash table in C. See: [lhash.h](include/cinternal/hash/lhash.h)  
 2. List in the C. See: [llist.h](include/cinternal/list/llist.h)  
   
   
### Info insertion into binary  
  
In case there is a necessity to insert custom info into binary, you can use macros `CPPUTILS_INSERT_COMMENT_TO_BIN_RAW`
defined in the file [insert_info_to_bin.h](include/cinternal/insert_info_to_bin.h).
An example of usage one can find in the file [main_insert_custom_info_into_bin_test_exe.cpp](src/tests/insert_custom_info_into_bin_test/main_insert_custom_info_into_bin_test_exe.cpp).  
  
```cpp  
#include <cinternal/insert_info_to_bin.h>

#define COMMIT_ID	e6ae7a2e4e7100532b6884d1534f4c8399067413

CPPUTILS_INSERT_COMMENT_TO_BIN_RAW(".cintr", "__commit-id02=" CPPUTILS_STRVAL(COMMIT_ID))

int main(int a_argc, char* a_argv[])
{
	(void)a_argc;
	(void)a_argv;
	return 0;
}
```  
  
To examine custom data in the binary later on one can use `dumpbin.exe` in the Windows and `objdump` in Linux.
Examples of the see commands with possible outputs are below  
  
Windows  
```bat  
...\cinternal>dumpbin /rawdata /section:.cintr any_quick_test.exe
Microsoft (R) COFF/PE Dumper Version 14.29.30147.0
Copyright (C) Microsoft Corporation.  All rights reserved.


Dump of file sys\win_x64\Debug\test\any_quick_test.exe

File Type: EXECUTABLE IMAGE

SECTION HEADER #8
  .cintr name
     126 virtual size
   25000 virtual address (0000000140025000 to 0000000140025125)
     200 size of raw data
   10C00 file pointer to raw data (00010C00 to 00010DFF)
       0 file pointer to relocation table
       0 file pointer to line numbers
       0 number of relocations
       0 number of line numbers
40000040 flags
         Initialized Data
         Read Only

RAW DATA #8
  0000000140025000: 74 65 73 74 20 63 6F 6D 6D 65 6E 74 20 30 31 00  test comment 01.
  0000000140025010: 74 65 73 74 20 63 6F 6D 6D 65 6E 74 20 30 32 00  test comment 02.
  0000000140025020: 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00  ................
  0000000140025030: 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00  ................
  0000000140025040: 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00  ................
  0000000140025050: 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00  ................
  0000000140025060: 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00  ................
  0000000140025070: 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00  ................
  0000000140025080: 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00  ................
  0000000140025090: 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00  ................
  00000001400250A0: 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00  ................
  00000001400250B0: 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00  ................
  00000001400250C0: 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00  ................
  00000001400250D0: 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00  ................
  00000001400250E0: 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00  ................
  00000001400250F0: 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00  ................
  0000000140025100: 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00  ................
  0000000140025110: 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00  ................
  0000000140025120: 00 00 00 00 00 00                                ......

  Summary

        1000 .cintr
```  
  
Mac  
```bash  
.../cinternal% otool insert_custom_info_into_bin_test_exe -s __DATA .cintr -v
insert_custom_info_into_bin_test_exe.app/Contents/MacOS/insert_custom_info_into_bin_test_exe:
Contents of (__DATA,.cintr) section
0000000100004000 5f 5f 63 6f 6d 6d 69 74 2d 69 64 30 32 3d 65 36 
0000000100004010 61 65 37 61 32 65 34 65 37 31 30 30 35 33 32 62 
0000000100004020 36 38 38 34 64 31 35 33 34 66 34 63 38 33 39 39 
0000000100004030 30 36 37 34 31 33 00 00 00 00 00 00 00 00 00 00 
0000000100004040 5f 5f 63 6f 6d 6d 69 74 2d 69 64 3d 65 36 61 65 
0000000100004050 37 61 32 65 34 65 37 31 30 30 35 33 32 62 36 38 
0000000100004060 38 34 64 31 35 33 34 66 34 63 38 33 39 39 30 36 
0000000100004070 37 34 31 33 00
```  
I do not know how to force `otool` to display content as ascii string  
  
  
Linux
```bash  
.../cinternal$ objdump -s -j .cintr insert_custom_info_into_bin_test_exe

insert_custom_info_into_bin_test_exe:     file format elf64-x86-64

Contents of section .cintr:
 2020 5f5f636f 6d6d6974 2d696430 323d6536  __commit-id02=e6
 2030 61653761 32653465 37313030 35333262  ae7a2e4e7100532b
 2040 36383834 64313533 34663463 38333939  6884d1534f4c8399
 2050 30363734 31330000 00000000 00000000  067413..........
 2060 5f5f636f 6d6d6974 2d69643d 65366165  __commit-id=e6ae
 2070 37613265 34653731 30303533 32623638  7a2e4e7100532b68
 2080 38346431 35333466 34633833 39393036  84d1534f4c839906
 2090 37343133 00                          7413.
```  
  
Custom information also can be added to dynamic libraries. Output on Linux will be the following:  
  
```bash  
.../$objdump -s -j .cintr libinsert_custom_info_into_bin_test_lib.so

libinsert_custom_info_into_bin_test_lib.so:     file format elf64-x86-64

Contents of section .cintr:
 2000 5f5f636f 6d6d6974 2d69643d 65366165  __commit-id=e6ae
 2010 37613265 34653731 30303533 32623638  7a2e4e7100532b68
 2020 38346431 35333466 34633833 39393036  84d1534f4c839906
 2030 37343133 00                          7413.
```  
  
  
### Changing function during runtime windows  
  
Code example [main_function_changer_test.c](src/tests/main_function_changer_test.c)  
  
```cpp  
#include <cinternal/replace_function.h>
#include <stdlib.h>
#include <stdio.h>

typedef void* (*TypeMallocFnc)(size_t);
typedef void (*TypeFreeFnc)(void*);

static TypeMallocFnc    s_originalMalloc = &malloc;
static TypeFreeFnc    s_originalFree = &free;
static int CPPUTILS_THREAD_LOCAL  s_nIgnoreThisStack = 0;

static void* MyMalloc(size_t a_size){
	void* pRet;
	if (s_nIgnoreThisStack) {
		pRet = (*s_originalMalloc)(a_size);
	}
	else {
		s_nIgnoreThisStack = 1;
		pRet = (*s_originalMalloc)(a_size);
		printf(" +++++ MyMalloc pRet=%p\n", pRet);
		s_nIgnoreThisStack = 0;
	}
	return pRet;
}

static void MyFree(void* a_ptr){
	if (s_nIgnoreThisStack) {
		(*s_originalFree)(a_ptr);
	}
	else {
		s_nIgnoreThisStack = 1;
		printf(" ----- MyFree pRet=%p\n", a_ptr);
		(*s_originalFree)(a_ptr);
		s_nIgnoreThisStack = 0;
	}
}

int main(void){
	void* pMem;
	struct SCInternalReplaceFunctionData aReplaceData[2];

	s_originalMalloc = &malloc;
	s_originalFree = &free;

	aReplaceData[0].funcname = "malloc";
	aReplaceData[0].newFuncAddress = &MyMalloc;

	aReplaceData[1].funcname = "free";
	aReplaceData[1].newFuncAddress = &MyFree;

	CInternalReplaceFunctions(2, aReplaceData);

	pMem = malloc(100);
	printf("pMem = %p\n", pMem);
	free(pMem);

	return 0;
}
```  
  
  
  
## Conclusion  
  
The expectation is that these codes are good examples (starting points) for clean C development. 
If you will have any questions concerning stuff in this repository or in C at all, please let me know.
