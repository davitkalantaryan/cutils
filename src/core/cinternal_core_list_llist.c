//
// file:            cinternal_core_list_llist.c
// path:			src/core/cinternal_core_list_llist.c
// created on:		2023 Feb 25
// created by:		Davit Kalantaryan (davit.kalantaryan@desy.de)
//


#include <cinternal/list/llist.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#ifdef _MSC_VER

#elif defined(__GNUC__) 

#pragma GCC diagnostic ignored "-Wattributes"

#endif


CPPUTILS_BEGIN_C


static void CinternalDefaultDataCleaner(void* a_pData) {
	CPPUTILS_STATIC_CAST(void, a_pData);
}


struct CPPUTILS_DLL_PRIVATE SCinternalLList {
	struct SCinternalLListItem*		first;
	size_t							m_size;
};


CINTERNAL_EXPORT CinternalLList_t CInternalLListCreate(void)
{
	CinternalLList_t pRet = CPPUTILS_STATIC_CAST(CinternalLList_t, calloc(1, sizeof(struct SCinternalLList)));
	//if (!pRet) {
	//	return CPPUTILS_NULL;
	//}
	return pRet;
}


CINTERNAL_EXPORT void	CInternalLListDestroyEx(CinternalLList_t a_list, TypeCinternalDataCleaner a_cleaner)
{
	struct SCinternalLListItem* pItemTmp, * pItem = a_list->first;

	a_cleaner = a_cleaner ? a_cleaner : (&CinternalDefaultDataCleaner);

	while (pItem) {
		pItemTmp = pItem->nextInList;
		(*a_cleaner)(pItem->data);
		free(pItem);
		pItem = pItemTmp;
	}

	free(a_list);
}


CINTERNAL_EXPORT CInternalLListIterator CInternalLListAddDataToFront(CinternalLList_t a_list, const void* a_data)
{
	struct SCinternalLListItem* pItem = CPPUTILS_STATIC_CAST(struct SCinternalLListItem*, calloc(1, sizeof(struct SCinternalLListItem)));
	if (!pItem) {
		return CPPUTILS_NULL;
	}

	pItem->data = CPPUTILS_CONST_CAST(void*, a_data);

	pItem->nextInList = a_list->first;
	if (a_list->first) {
		a_list->first->prevIList = pItem;
	}
	a_list->first = pItem;
	++(a_list->m_size);
	
	return pItem;
}


CINTERNAL_EXPORT CInternalLListIterator CInternalLListFirstItem(CinternalLList_t a_list)
{
	return a_list->first;
}


CINTERNAL_EXPORT void CInternalLListRemoveData(CinternalLList_t a_list, CInternalLListIterator a_iterator)
{
	if (a_iterator->prevIList) {
		a_iterator->prevIList->nextInList = a_iterator->nextInList;
	}

	if (a_iterator->nextInList) {
		a_iterator->nextInList->prevIList = a_iterator->prevIList;
	}

	if (a_iterator == a_list->first) {
		a_list->first = a_iterator->nextInList;
	}

	--(a_list->m_size);

	free(CPPUTILS_CONST_CAST(struct SCinternalLListItem*, a_iterator));
}


CINTERNAL_EXPORT size_t CInternalLListSize(CinternalLList_t a_list)
{
	return a_list->m_size;
}


CPPUTILS_END_C
