//
// repo:			cinternal
// file:            undisable_compiler_warnings.h
// path:			include/cinternal/undisable_compiler_warnings.h
// created on:		2023 Jul 07
// created by:		Davit Kalantaryan (davit.kalantaryan@desy.de)
//

#ifndef CINTERNAL_INCLUDE_CINTERNAL_UNDISABLE_COMPILER_WARNINGS_H
#define CINTERNAL_INCLUDE_CINTERNAL_UNDISABLE_COMPILER_WARNINGS_H
#include <cinternal/internal_header.h>
#endif 

#ifdef CINTERNAL_COMPILER_WARNINGS_DISABLED
#undef CINTERNAL_COMPILER_WARNINGS_DISABLED


#ifdef CPPUTILS_COMPILER_WARNINGS_PUSHED
CPPUTILS_WARNINGS_POP
#undef CPPUTILS_COMPILER_WARNINGS_PUSHED
#endif


#endif  //  #ifdef CINTERNAL_COMPILER_WARNINGS_DISABLED
