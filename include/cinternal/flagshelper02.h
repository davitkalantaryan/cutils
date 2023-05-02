//
// file:            flagshelper02.h
// path:			include/cinternal/flagshelper02.h
// created on:		2021 Nov 13
// created by:		Davit Kalantaryan (davit.kalantaryan@gmail.com)
//
// if CPPUTILS_FLAGS_UN_RAW macros is used, then for uint64_t include #include <stdint.h>
//

#if !defined(CINTERNAL_INCLUDE_CINTERNAL_FLAGSHELPER02_H) && !defined(CINTERNAL_INCLUDE_CINTERNAL_FLAGSHELPER_ANY_H)
#define CINTERNAL_INCLUDE_CINTERNAL_FLAGSHELPER02_H
#define CINTERNAL_INCLUDE_CINTERNAL_FLAGSHELPER_ANY_H

#include <cinternal/internal_header.h>
#include <cinternal/macroses02.h>

#define CPPUTILS_MAKE_BITS_TRUE         1
#define CPPUTILS_MAKE_BITS_FALSE        2
#define CPPUTILS_INIT_BITS              0xaaaaaaaaaaaaaaaa

#define CPPUTILS_POS_NEG_BITS_RAW(_type,_name) \
    _type  _name ## _true : 1; \
    _type  _name ## _false : 1

#define CPPUTILS_POS_NEG_BITS(_name)  CPPUTILS_POS_NEG_BITS_RAW(uint64_t,_name)
#define CPPUTILS_POS_NEG_BITS2(_a,_name)  CPPUTILS_POS_NEG_BITS(_name) ;


#define CPPUTILS_BOTH_BITS_RAW(_type,_name) \
    _type  _name  : 2
#define CPPUTILS_BOTH_BITS(_name)  CPPUTILS_BOTH_BITS_RAW(uint64_t,_name)
#define CPPUTILS_BOTH_BITS2(_a,_name)  CPPUTILS_BOTH_BITS(_name) ;


#define CPPUTILS_BITS_B(...) CPPUTILS_MACRO02_APPY(CPPUTILS_POS_NEG_BITS2,,__VA_ARGS__)
#define CPPUTILS_BITS_B2(...) CPPUTILS_MACRO02_APPY(CPPUTILS_BOTH_BITS2,,__VA_ARGS__)


#define CPPUTILS_FLAGS_UN_RAW(_name, _numberOfReserved,...)  \
    union _name {  \
        uint64_t  wr_all; \
        struct{ \
            CPPUTILS_BITS_B(__VA_ARGS__)                \
            uint64_t    reserved01 : _numberOfReserved; \
        }rd; \
        struct{ \
            CPPUTILS_BITS_B2(__VA_ARGS__)               \
            uint64_t    reserved01 : _numberOfReserved; \
        }wr;    \
    }

#define CPPUTILS_FLAGS_UN(...)    CPPUTILS_FLAGS_UN_RAW(,64-2*CPPUTILS_NARGS(__VA_ARGS__),__VA_ARGS__)
#define CPPUTILS_FLAGS_UN_NM(_name,...)    CPPUTILS_FLAGS_UN_RAW(_name,64-2*CPPUTILS_NARGS(__VA_ARGS__),__VA_ARGS__)


#endif  //  #if !defined(CINTERNAL_INCLUDE_CINTERNAL_FLAGSHELPER02_H) && !defined(CINTERNAL_INCLUDE_CINTERNAL_FLAGSHELPER_ANY_H)
