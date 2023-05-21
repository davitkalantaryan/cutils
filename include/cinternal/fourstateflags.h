//
// file:            fourstateflags.h
// path:			include/cinternal/fourstateflags.h
// created on:		2023 May 19
// created by:		Davit Kalantaryan (davit.kalantaryan@gmail.com)
//

#ifndef CINTERNAL_INCLUDE_CINTERNAL_FOURSTATEFLAGS_H
#define CINTERNAL_INCLUDE_CINTERNAL_FOURSTATEFLAGS_H

#include <cinternal/internal_header.h>
#include <cinternal/macroses02.h>
#include <stdint.h>

#define CPPUTILS_FOURSTATE_MAKE_ALL_BITS_TRUE       0x1111111111111111
#define CPPUTILS_FOURSTATE_MAKE_ALL_BITS_ONGOING_FT 0x2222222222222222
#define CPPUTILS_FOURSTATE_MAKE_ALL_BITS_ONGOING_TF 0x4444444444444444
#define CPPUTILS_FOURSTATE_MAKE_ALL_BITS_FALSE      0x8888888888888888

#define CPPUTILS_FOURSTATE_MAKE_BITS_TRUE           1
#define CPPUTILS_FOURSTATE_MAKE_BITS_ONGOING_FT     2
#define CPPUTILS_FOURSTATE_MAKE_BITS_ONGOING_TF     4
#define CPPUTILS_FOURSTATE_MAKE_BITS_FALSE          8


#define CPPUTILS_FOURSTATE1(_name)                  \
    uint64_t _name ## _true : 1;                    \
    uint64_t _name ## _ongoing_false_to_true : 1;   \
    uint64_t _name ## _ongoing_true_to_false : 1;   \
    uint64_t _name ## _false : 1

#define CPPUTILS_FOURSTATE2(_name)      \
    uint64_t _name ## _bits12 : 2;      \
    uint64_t _name ## _bits34 : 2

#define CPPUTILS_FOURSTATE3a(_name)     \
    uint64_t _name ## _any_true : 3;    \
    uint64_t _name ## _false : 1

#define CPPUTILS_FOURSTATE3b(_name)     \
    uint64_t _name ## _true : 1;        \
    uint64_t _name ## _any_false : 3

#define CPPUTILS_FOURSTATE4(_name)     \
    uint64_t _name : 4


#define CPPUTILS_FOURSTATE1_2(_a,_name)     CPPUTILS_FOURSTATE1(_name) ;
#define CPPUTILS_FOURSTATE2_2(_a,_name)     CPPUTILS_FOURSTATE2(_name) ;
#define CPPUTILS_FOURSTATE3a_2(_a,_name)    CPPUTILS_FOURSTATE3a(_name) ;
#define CPPUTILS_FOURSTATE3b_2(_a,_name)    CPPUTILS_FOURSTATE3b(_name) ;
#define CPPUTILS_FOURSTATE4_2(_a,_name)     CPPUTILS_FOURSTATE4(_name) ;


#define CPPUTILS_FOURSTATE1_ALL(...)    CPPUTILS_MACRO02_APPY(CPPUTILS_FOURSTATE1_2,,__VA_ARGS__)
#define CPPUTILS_FOURSTATE2_ALL(...)    CPPUTILS_MACRO02_APPY(CPPUTILS_FOURSTATE2_2,,__VA_ARGS__)
#define CPPUTILS_FOURSTATE3a_ALL(...)   CPPUTILS_MACRO02_APPY(CPPUTILS_FOURSTATE3a_2,,__VA_ARGS__)
#define CPPUTILS_FOURSTATE3b_ALL(...)   CPPUTILS_MACRO02_APPY(CPPUTILS_FOURSTATE3b_2,,__VA_ARGS__)
#define CPPUTILS_FOURSTATE4_ALL(...)    CPPUTILS_MACRO02_APPY(CPPUTILS_FOURSTATE4_2,,__VA_ARGS__)


#define CPPUTILS_FOURSTATE_FLAGS_UN_RAW(_name, _numberOfReserved,...)  \
    union _name {  \
        uint64_t  wr_all; \
        struct{ \
            CPPUTILS_FOURSTATE1_ALL(__VA_ARGS__)                \
            uint64_t    reserved01 : _numberOfReserved; \
        }rd1; \
        struct{ \
            CPPUTILS_FOURSTATE2_ALL(__VA_ARGS__)               \
            uint64_t    reserved01 : _numberOfReserved; \
        }rd2;    \
        struct{ \
            CPPUTILS_FOURSTATE3a_ALL(__VA_ARGS__)               \
            uint64_t    reserved01 : _numberOfReserved; \
        }rd3a;    \
        struct{ \
            CPPUTILS_FOURSTATE3b_ALL(__VA_ARGS__)               \
            uint64_t    reserved01 : _numberOfReserved; \
        }rd3b;    \
        struct{ \
            CPPUTILS_FOURSTATE4_ALL(__VA_ARGS__)               \
            uint64_t    reserved01 : _numberOfReserved; \
        }wr;    \
    }

#define CPPUTILS_FOURSTATE_FLAGS_UN(...)              CPPUTILS_FOURSTATE_FLAGS_UN_RAW(,64-4*CPPUTILS_NARGS(__VA_ARGS__),__VA_ARGS__)
#define CPPUTILS_FOURSTATE_FLAGS_UN_NM(_name,...)     CPPUTILS_FOURSTATE_FLAGS_UN_RAW(_name,64-4*CPPUTILS_NARGS(__VA_ARGS__),__VA_ARGS__)



#endif  //  #ifndef CINTERNAL_INCLUDE_CINTERNAL_FOURSTATEFLAGS_H
