//
// repo:			cutils
// file:            cutils_core_parser_argparser01.c
// path:			src/core/cutils_core_parser_argparser01.c
// created on:		2023 Mar 16
// created by:		Davit Kalantaryan (davit.kalantaryan@desy.de)
//

#include <cutils/parser/argparser01.h>
#include <cinternal/disable_compiler_warnings.h>
#include <string.h>
#include <cinternal/undisable_compiler_warnings.h>


CPPUTILS_BEGIN_C


CUTILS_EXPORT const char* CInternalFindEndTakeArg(
	int* CPPUTILS_ARG_NONULL a_argc_p, char** CPPUTILS_ARG_NONULL a_argv, 
	const char* CPPUTILS_ARG_NONULL a_key, int* a_pLastArg, bool a_hasArg)
{
	const char* cpcReturn;
	const size_t keyStrLen = strlen(a_key);
	size_t unStrLen;
	int i;
	for (i = 0; i < (*a_argc_p); ++i) {
		unStrLen = strlen(a_argv[i]);
		if (unStrLen > keyStrLen) {
			if (memcmp(a_key, a_argv[i], keyStrLen) == 0) {
				cpcReturn = a_argv[i] + keyStrLen;
				if (a_pLastArg) { *a_pLastArg = i; }
				if (i < ((*a_argc_p) - 1)) {
					memmove(&a_argv[i], a_argv[i] + 1, (CPPUTILS_STATIC_CAST(size_t, *a_argc_p) - CPPUTILS_STATIC_CAST(size_t, i)) * sizeof(char*));
				}
				else {
					a_argv[i] = CPPUTILS_NULL;
				}
				--(*a_argc_p);
				return cpcReturn;
			}  // if (memcmp(a_key, a_argv[i], keyStrLen) == 0) {
		}  // if (unStrLen > keyStrLen) {
		else if (unStrLen == keyStrLen) {
			if (memcmp(a_key, a_argv[i], keyStrLen) == 0) {
				if (a_pLastArg) { *a_pLastArg = i; }
				cpcReturn = a_argv[i];
				if (i < ((*a_argc_p) - 1)) {
					memmove(&a_argv[i], &a_argv[i+1], (CPPUTILS_STATIC_CAST(size_t, *a_argc_p) - CPPUTILS_STATIC_CAST(size_t, i)) * sizeof(char*));
					if (a_hasArg) {
						cpcReturn = a_argv[i];
						--(*a_argc_p);
						if (i < ((*a_argc_p) - 1)) {
							memmove(&a_argv[i], &a_argv[i + 1], (CPPUTILS_STATIC_CAST(size_t, *a_argc_p) - CPPUTILS_STATIC_CAST(size_t, i)) * sizeof(char*));
						}
						else {
							a_argv[i] = CPPUTILS_NULL;
						}
					}  //  if (a_hasArg) {
				}
				else {
					a_argv[i] = CPPUTILS_NULL;
					if (a_hasArg) { cpcReturn = CPPUTILS_NULL; }
				}
				--(*a_argc_p);
				return cpcReturn;
			}  // if (memcmp(a_key, a_argv[i], keyStrLen) == 0) {
		}  //  else if (unStrLen == keyStrLen) {
	}  //  for (i = 0; i < a_argc; ++i) {

	return CPPUTILS_NULL;
}


CPPUTILS_END_C
