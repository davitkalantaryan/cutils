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

CPPUTILS_C_CODE_INITIALIZER(code_init) {
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

CPPUTILS_C_CODE_INITIALIZER(code_init) {
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
   
   
## Conclusion  
  
The expectation is that these codes are good examples (starting points) for clean C development. 
If you will have any questions concerning stuff in this repository or in C at all, please let me know.
