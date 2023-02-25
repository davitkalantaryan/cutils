//
// file:            llist.h
// path:			include/cinternal/list/llist.h
// created on:		2023 Feb 25
// created by:		Davit Kalantaryan (davit.kalantaryan@desy.de)
//

#ifndef CINTERNAL_INCLUDE_CINTERNAL_LIST_LLIST_H
#define CINTERNAL_INCLUDE_CINTERNAL_LIST_LLIST_H

#include <cinternal/export_symbols.h>
#include <cinternal/common_data01.h>


CPPUTILS_BEGIN_C

struct SCinternalLListItem {
	struct SCinternalLListItem* prevIList, * nextInList;
	void*				data;
	void*				reserved01;
};

typedef const struct SCinternalLListItem* CInternalLListIterator;
typedef struct SCinternalLList* CinternalLList_t;


CINTERNAL_EXPORT CinternalLList_t CInternalLListCreate(void);
CINTERNAL_EXPORT void	CInternalLListDestroyEx(CinternalLList_t a_list, TypeCinternalDataCleaner a_cleaner);
CINTERNAL_EXPORT CInternalLListIterator CInternalLListAddDataToFront(CinternalLList_t a_list, const void* a_data);
CINTERNAL_EXPORT CInternalLListIterator CInternalLListFirstItem(CinternalLList_t a_list);
CINTERNAL_EXPORT void	CInternalLListRemoveData(CinternalLList_t a_list, CInternalLListIterator a_iterator);
CINTERNAL_EXPORT size_t CInternalLListSize(CinternalLList_t a_list);


CPPUTILS_END_C

#define CInternalLListDestroy(_hashTbl)		CInternalLListDestroyEx(_hashTbl,CPPUTILS_NULL)


#endif  // #ifndef CINTERNAL_INCLUDE_CINTERNAL_LIST_LLIST_H
