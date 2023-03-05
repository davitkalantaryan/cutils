//
// file:            insert_info_to_bin.h
// path:			include/cinternal/insert_info_to_bin.h
// created on:		2023 Feb 28
// created by:		Davit Kalantaryan (davit.kalantaryan@desy.de)
//

#ifndef CINTERNAL_INCLUDE_CINTERNAL_INSERT_INO_TO_BIN_H
#define CINTERNAL_INCLUDE_CINTERNAL_INSERT_INO_TO_BIN_H

#include <cinternal/export_symbols.h>


#define CPPUTILS_INSERT_COMMENT_TO_BIN_RAW(_sectionName,_comment)	\
	CPPUTILS_INSERT_COMMENT_TO_BIN_RAW_RAW(CPPUTILS_NAME_WITH_LINE(CPPUTILS_NAME_WITH_CNTR(___section_var_)),_sectionName,_comment)


#endif  // #ifndef CINTERNAL_INCLUDE_CINTERNAL_INSERT_INO_TO_BIN_H
