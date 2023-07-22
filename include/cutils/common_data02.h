//
// file:            common_data02.h
// path:			include/cinternal/common_data02.h
// created on:		2023 Apr 12
// created by:		Davit Kalantaryan (davit.kalantaryan@desy.de)
//

#ifndef CINTERNAL_INCLUDE_CINTERNAL_COMMON_DATA02_H
#define CINTERNAL_INCLUDE_CINTERNAL_COMMON_DATA02_H

#include <cinternal/export_symbols.h>


CPPUTILS_BEGIN_C

struct SCinternalDLListIterator {
	struct SCinternalDLListIterator*prev, *next;
};
typedef const struct SCinternalDLListIterator* CinternalDLListIterator_t;

CPPUTILS_END_C



#endif  // #ifndef CINTERNAL_INCLUDE_CINTERNAL_COMMON_DATA02_H
