//
// repo:			cutils
// file:            common_data02.h
// path:			include/cinternal/common_data02.h
// created on:		2023 Apr 12
// created by:		Davit Kalantaryan (davit.kalantaryan@desy.de)
//

#ifndef CUTILS_INCLUDE_CUTILS_COMMON_DATA02_H
#define CUTILS_INCLUDE_CUTILS_COMMON_DATA02_H

#include <cinternal/internal_header.h>


CPPUTILS_BEGIN_C

struct SCinternalDLListIterator {
	struct SCinternalDLListIterator*prev, *next;
};
typedef const struct SCinternalDLListIterator* CinternalDLListIterator_t;

CPPUTILS_END_C



#endif  // #ifndef CUTILS_INCLUDE_CUTILS_COMMON_DATA02_H
