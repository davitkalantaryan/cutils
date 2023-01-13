//
// file:			internal_header.h
// path:			include/cinternal/internal_header.h
// created on:		2022 Jun 04
// created by:		Davit Kalantaryan (davit.kalantaryan@gmail.com)
//

#ifndef CINTERNAL_INCLUDE_CINTERNAL_INTERNAL_HEADER_H
#define CINTERNAL_INCLUDE_CINTERNAL_INTERNAL_HEADER_H

#include <stddef.h>

#define cinternal_alloca	alloca

#ifdef _MSC_VER

	#if defined(_WIN64) || defined(_M_ARM)
		#define CINTERNAL_FNAME_PREFIX ""
		#define CINTERNAL_DS_FNAME_POSTFIX
		#define CINTERNAL_SEC_CH_FNC_NAME	"__security_check_cookie"
	#else
		#define CINTERNAL_FNAME_PREFIX "_"
		#define CINTERNAL_DS_FNAME_POSTFIX	"@12"
		#define CINTERNAL_SEC_CH_FNC_NAME	"@__security_check_cookie@4"
	#endif

    #define CINTERNAL_C_CODE_INITIALIZER_RAW(_sect,f) \
        __pragma(section(_sect,read)) \
        static void f(void); \
        __declspec(allocate(_sect)) void (*f##_)(void) = f; \
        __pragma(comment(linker,"/include:" CINTERNAL_FNAME_PREFIX #f "_")) \
        static void f(void)

    #define CINTERNAL_C_CODE_INITIALIZER(f)  CINTERNAL_C_CODE_INITIALIZER_RAW(".CRT$XCU",f)

	#undef cinternal_alloca
	#define cinternal_alloca	_alloca
	#define CINTERNAL_UNREACHABLE_CODE(_code)
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
	#define CINTERNAL_BEFORE_CPP_17_FALL_THR
    #define CINTERNAL_DLL_PUBLIC		__declspec(dllexport)
    #define CINTERNAL_DLL_PRIVATE
    #define CINTERNAL_IMPORT_FROM_DLL	__declspec(dllimport)
	#define CINTERNAL_THREAD_LOCAL		__declspec(thread)
	#if !defined(_WIN64) && !defined(_M_ARM64)
		#define CPPUTLS_32_BIT
	#endif
#elif defined(__GNUC__) || defined(__clang__) || defined(LINUX_GCC)
    #define CINTERNAL_MAY_ALIAS  __attribute__ ((__may_alias__))
	#define CINTERNAL_UNREACHABLE_CODE(_code)	_code ;
	#if __GNUC__>=7
		#define CINTERNAL_BEFORE_CPP_17_FALL_THR	__attribute__ ((fallthrough)) ;
	#elif defined(__has_attribute)
		#if __has_attribute (fallthrough)
			#define CINTERNAL_BEFORE_CPP_17_FALL_THR	__attribute__ ((fallthrough)) ;
		#else
			#define CINTERNAL_BEFORE_CPP_17_FALL_THR		/* FALLTHRU */
		#endif
	#else
		#define CINTERNAL_BEFORE_CPP_17_FALL_THR		/* FALLTHRU */
	#endif  // #if __GNUC__>=7
    //#define CINTERNAL_DLL_PUBLIC		__attribute__((visibility("default")))
    #define CINTERNAL_DLL_PUBLIC
    #define CINTERNAL_DLL_PRIVATE		__attribute__((visibility("hidden")))
    #define CINTERNAL_IMPORT_FROM_DLL
	#define CINTERNAL_THREAD_LOCAL		__thread
#elif defined(__CYGWIN__)
	#define CINTERNAL_UNREACHABLE_CODE(_code)	_code ;
	#define CINTERNAL_BEFORE_CPP_17_FALL_THR	__attribute__ ((fallthrough)) ;
    #define CINTERNAL_DLL_PUBLIC		__attribute__((dllexport))
    #define CINTERNAL_DLL_PRIVATE
    #define CINTERNAL_IMPORT_FROM_DLL	__attribute__((dllimport))
#elif defined(__MINGW64__) || defined(__MINGW32__)
	#define CINTERNAL_UNREACHABLE_CODE(_code)	_code ;
	#define CINTERNAL_BEFORE_CPP_17_FALL_THR	__attribute__ ((fallthrough)) ;
    #define CINTERNAL_DLL_PUBLIC		_declspec(dllexport)
    #define CINTERNAL_DLL_PRIVATE
    #define CINTERNAL_IMPORT_FROM_DLL	_declspec(dllimport)
#elif defined(__SUNPRO_CC)
	#define CINTERNAL_UNREACHABLE_CODE(_code)	_code ;
	// #define CINTERNAL_BEFORE_CPP_17_FALL_THR	__attribute__ ((fallthrough)) ; // ???
	#define CINTERNAL_BEFORE_CPP_17_FALL_THR
    #define CINTERNAL_DLL_PUBLIC
    #define CINTERNAL_DLL_PRIVATE		__hidden
    #define CINTERNAL_IMPORT_FROM_DLL
#endif  // #ifdef _MSC_VER

#if defined(_MSC_VER) && defined(_MSVC_LANG)
	#if (_MSVC_LANG>=201100L)
		#define CINTERNAL_CPP_11_DEFINED		1
	#endif
	#if (_MSVC_LANG>=201400L)
		#define CINTERNAL_CPP_14_DEFINED		1
	#endif
	#if (_MSVC_LANG>=201700L)
		#define CINTERNAL_CPP_17_DEFINED		1
	#endif
	#if (_MSVC_LANG>=202000L)
		#define CINTERNAL_CPP_20_DEFINED		1
	#endif
	#if (_MSVC_LANG>=202300L)
		#define CINTERNAL_CPP_23_DEFINED		1
	#endif
#elif defined(__cplusplus)  // #if defined(_MSC_VER) && defined(_MSVC_LANG)
	#if (__cplusplus>=201100L)
		#define CINTERNAL_CPP_11_DEFINED		1
	#endif
	#if (__cplusplus>=201400L)
		#define CINTERNAL_CPP_14_DEFINED		1
	#endif
	#if (__cplusplus>=201700L)
		#define CINTERNAL_CPP_17_DEFINED		1
	#endif
	#if (__cplusplus>=202000L)
		#define CINTERNAL_CPP_20_DEFINED		1
	#endif
	#if (__cplusplus>=202300L)
		#define CINTERNAL_CPP_23_DEFINED		1
	#endif
#endif // #if defined(_MSC_VER) && defined(_MSVC_LANG)


//#undef CINTERNAL_CPP_11_DEFINED


//#define CINTERNAL_RESTRICT   restrict
#define CINTERNAL_RESTRICT

#ifndef CINTERNAL_MAY_ALIAS
#define CINTERNAL_MAY_ALIAS
#endif

#ifdef __cplusplus
#define CINTERNAL_STATIC_CAST(_type,_data)		static_cast<_type>(_data)
#define CINTERNAL_REINTERPRET_CAST(_type,_data)	reinterpret_cast<_type>(_data)
#define CINTERNAL_CONST_CAST(_type,_data)		const_cast<_type>(_data)
#define CINTERNAL_DYNAMIC_CAST(_type,_data)		dynamic_cast<_type>(_data)
#define CINTERNAL_GLOBAL	   ::
#define CINTERNAL_BEGIN_C   extern "C" {
#define CINTERNAL_END_C     }
#define CINTERNAL_EXTERN_C  extern "C"
#else
#define CINTERNAL_STATIC_CAST(_type,_data)		((_type)(_data))
#define CINTERNAL_REINTERPRET_CAST(_type,_data)	((_type)(_data))
#define CINTERNAL_CONST_CAST(_type,_data)		((_type)(_data))
#define CINTERNAL_DYNAMIC_CAST(_type,_data)		((_type)(_data))
#define CINTERNAL_GLOBAL
#define CINTERNAL_BEGIN_C
#define CINTERNAL_END_C
#define CINTERNAL_EXTERN_C
#endif


#ifdef CINTERNAL_CPP_17_DEFINED
#define CINTERNAL_FALLTHROUGH	[[fallthrough]] ;
#else
#define CINTERNAL_FALLTHROUGH	CINTERNAL_BEFORE_CPP_17_FALL_THR 
//#define CINTERNAL_FALLTHROUGH	
#endif

//#undef CINTERNAL_CPP_11_DEFINED
//#undef CINTERNAL_CPP_14_DEFINED

#ifdef CINTERNAL_CPP_11_DEFINED
#define CINTERNAL_STD_MOVE_DEFINED   1
#define CINTERNAL_NOEXCEPT           noexcept
#define CINTERNAL_NULL               nullptr
#define CINTERNAL_OVERRIDE           override
//#define CINTERNAL_CONSTEXPR          constexpr
//#define CINTERNAL_CONSTEXPR_CONS     constexpr
#define CINTERNAL_CONSTEXPR          constexpr
#define CINTERNAL_CONSTEXPR_FNC          constexpr
#define CINTERNAL_CONSTEXPR_EQ(_exp)	= (_exp)
#define CINTERNAL_DELETE             =delete;
#define CINTERNAL_CONSTEXPR_STACK_ARRAY(_type,_name,_count)	_type _name[_count]
#else
#define CINTERNAL_NOEXCEPT	throw()
#define CINTERNAL_NULL		NULL 
#define CINTERNAL_OVERRIDE
#define CINTERNAL_CONSTEXPR	const
#define CINTERNAL_CONSTEXPR_FNC
#define CINTERNAL_CONSTEXPR_EQ(_exp)
#define CINTERNAL_DELETE   {}
#define CINTERNAL_CONSTEXPR_STACK_ARRAY(_type,_name,_count)	_type * _name = CINTERNAL_STATIC_CAST(  _type *,cinternal_alloca((_count)*sizeof(_type))  )
#endif

#ifndef __cplusplus
#undef CINTERNAL_NOEXCEPT
#define CINTERNAL_NOEXCEPT
#endif

#ifdef CINTERNAL_CPP_14_DEFINED
#define CINTERNAL_CONSTEXPR_FNC_CPP14     constexpr
#else
#define CINTERNAL_CONSTEXPR_FNC_CPP14
#endif

#ifdef __cplusplus
#define CINTERNAL_REGISTER
#else
#define CINTERNAL_REGISTER	register
#endif


//#define CINTERNAL_IS_LITTLE_ENDIAN (((union { unsigned x; unsigned char c; }){1}).c)

#if defined(_DEBUG) || defined(CINTERNAL_DEBUG)
// we have debug compilation
#else
// we have release
#ifndef NDEBUG
// let's define NDEBUG (No DEBUG)
#define NDEBUG
#endif
#endif

#ifdef NDEBUG
#define CINTERNAL_DO_DEBUG_EXP(_exp)
#define CINTERNAL_SAFE_CAST(_type,_val)	static_cast<_type>(_val)
#else
#define CINTERNAL_DO_DEBUG_EXP(_exp)              _exp ;
#define CINTERNAL_SAFE_CAST(_type,_val)	dynamic_cast<_type>(_val)
#endif


#define CINTERNAL_NO_NULL

#define CINTERNAL_STRINGIFY(_x)                CINTERNAL_STRINGIFY_PRIV_RAW(_x)
#define CINTERNAL_STRINGIFY_PRIV_RAW(_x)		#_x


#if defined(__EMSCRIPTEN__) || defined(EMSCRIPTEN) || defined(CINTERNAL_WASM)
#define CINTERNAL_EMSCRIPTEN_IS_USED
#endif
//#define CINTERNAL_EMSCRIPTEN_IS_USED

#ifdef CINTERNAL_EMSCRIPTEN_IS_USED
#ifdef CINTERNAL_DLL_PUBLIC
#undef CINTERNAL_DLL_PUBLIC
#endif
#include <emscripten/emscripten.h>
#define CINTERNAL_DLL_PUBLIC     EMSCRIPTEN_KEEPALIVE
#endif

// todo: make better multithreading decision
#if !defined(CINTERNAL_EMSCRIPTEN_IS_USED) && !defined(CINTERNAL_FORCE_SINGLE_THREADED)
#define CINTERNAL_MULTITHREADED
#endif

// todo: make better possible no file dfecision
#ifdef CINTERNAL_EMSCRIPTEN_IS_USED
#define CINTERNAL_POSSIBLE_NO_PERS_FILE
#endif

#ifdef CINTERNAL_MULTITHREADED
#define CINTERNAL_TRY_CATCH(_expression,_result)	(_expression) ;
#else
#define CINTERNAL_TRY_CATCH(_expression,_result)   try{(_expression);}catch(...){return _result;}
#endif

#define CINTERNAL_IN_OUT

// https://gcc.gnu.org/bugzilla/show_bug.cgi?id=56480
#ifdef __GNUC__
#define CINTERNAL_GCC_BUG_56480
#endif

#ifdef CINTERNAL_CPP_20_DEFINED
#define CINTERNAL_NODISCARD	[[nodiscard]]
#elif defined(CINTERNAL_CPP_11_DEFINED)
#define CINTERNAL_NODISCARD	noexcept
#else
#define CINTERNAL_NODISCARD	throw()
#endif

#if defined(__GNUC__) || defined(__clang__) || defined(LINUX_GCC)
#define CINTERNAL_LIKELY(_x)             __builtin_expect(!!(_x), 1)
#define CINTERNAL_UNLIKELY(_x)           __builtin_expect(!!(_x), 0)
#define CINTERNAL_LIKELY_VALUE(_x,_val)  __builtin_expect((_x), (_val))
#else
#define CINTERNAL_LIKELY(_x)             (_x)
#define CINTERNAL_UNLIKELY(_x)           (_x)
#define CINTERNAL_LIKELY_VALUE(_x,_val)  ((_x)==(_val))
#endif


#define CINTERNAL_ARG_NONULL


#endif  // #ifndef CINTERNAL_INCLUDE_CINTERNAL_INTERNAL_HEADER_H
