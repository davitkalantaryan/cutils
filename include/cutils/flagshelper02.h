//
// file:            flagshelper02.h
// path:			include/cinternal/flagshelper02.h
// created on:		2021 Nov 13
// created by:		Davit Kalantaryan (davit.kalantaryan@gmail.com)
//

#if !defined(CINTERNAL_INCLUDE_CINTERNAL_FLAGSHELPER02_H) && !defined(CINTERNAL_INCLUDE_CINTERNAL_FLAGSHELPER_ANY_H)
#define CINTERNAL_INCLUDE_CINTERNAL_FLAGSHELPER02_H
#define CINTERNAL_INCLUDE_CINTERNAL_FLAGSHELPER_ANY_H

#include <cinternal/internal_header.h>
#include <cinternal/macroses02.h>
#include <stdint.h>

#define CPPUTILS_MAKE_BITS_TRUE                 1
#define CPPUTILS_MAKE_BITS_FALSE                2
#define CPPUTILS_INIT_BITS                      0xaaaaaaaaaaaaaaaa

#define CPPUTILS_BISTATE_MAKE_BITS_TRUE         1
#define CPPUTILS_BISTATE_MAKE_BITS_FALSE        2
#define CPPUTILS_BISTATE_MAKE_ALL_BITS_TRUE     0x5555555555555555
#define CPPUTILS_BISTATE_MAKE_ALL_BITS_FALSE    0xaaaaaaaaaaaaaaaa

#define CPPUTILS_BISTATE1(_name)                    \
    uint64_t _name ## _true : 1;                    \
    uint64_t _name ## _false : 1


#define CPPUTILS_BISTATE2(_name)      \
    uint64_t _name : 2


#define CPPUTILS_BISTATE1_2(_a,_name)  CPPUTILS_BISTATE1(_name) ;
#define CPPUTILS_BISTATE2_2(_a,_name)  CPPUTILS_BISTATE2(_name) ;


#define CPPUTILS_BISTATE1_ALL(...) CPPUTILS_MACRO02_APPY(CPPUTILS_BISTATE1_2,,__VA_ARGS__)
#define CPPUTILS_BISTATE2_ALL(...) CPPUTILS_MACRO02_APPY(CPPUTILS_BISTATE2_2,,__VA_ARGS__)


#define CPPUTILS_FLAGS_UN_RAW(_name, _numberOfReserved,...)  \
    union _name {  \
        uint64_t  wr_all; \
        struct{ \
            CPPUTILS_BISTATE1_ALL(__VA_ARGS__)                \
            uint64_t    reserved01 : _numberOfReserved; \
        }rd; \
        struct{ \
            CPPUTILS_BISTATE2_ALL(__VA_ARGS__)               \
            uint64_t    reserved01 : _numberOfReserved; \
        }wr;    \
    }

#define CPPUTILS_FLAGS_UN(...)              CPPUTILS_FLAGS_UN_RAW(,64-2*CPPUTILS_NARGS(__VA_ARGS__),__VA_ARGS__)
#define CPPUTILS_FLAGS_UN_NM(_name,...)     CPPUTILS_FLAGS_UN_RAW(_name,64-2*CPPUTILS_NARGS(__VA_ARGS__),__VA_ARGS__)


#endif  //  #if !defined(CINTERNAL_INCLUDE_CINTERNAL_FLAGSHELPER02_H) && !defined(CINTERNAL_INCLUDE_CINTERNAL_FLAGSHELPER_ANY_H)
