//
// file:            cinternal_core_list_dllist.c
// path:			src/core/cinternal_core_list_dllist.c
// created on:		2023 Feb 25
// created by:		Davit Kalantaryan (davit.kalantaryan@desy.de)
// explanation:		Double Linked List
//


#include <cinternal/list/dllist.h>
#define CINTERNAL_SRC_CORE_CINTERNAL_CORE_LIST_DLLIST_IMPL_H_NEEDED		1
#define CInternalDLListAddCreatedIteratorAfterIteratorInline_needed		1
#define CInternalDLListAddCreatedIteratorBeforeIteratorInline_needed	1
#define CInternalDLListAddCreatedIteratorFrontInline2_needed			1
#define CInternalDLListAddCreatedIteratorBackInline_needed				1
#define CInternalListRemoveItertaorInline2_needed						1
#include "cinternal_core_list_dllist.impl.h"


CPPUTILS_BEGIN_C


struct CPPUTILS_DLL_PRIVATE SCinternalDLList {
	TypeCinternalAllocator			allocator;
	TypeCinternalDeallocator		deallocator;
	struct SCinternalDLListIterator	*first, *last;
	size_t							m_size;
};


CINTERNAL_EXPORT CinternalDLList_t CInternalDLListCreateEx(TypeCinternalAllocator a_allocator, TypeCinternalDeallocator a_deallocator)
{
	CinternalDLList_t pRet;
	a_allocator = a_allocator ? a_allocator : (&malloc);
	pRet = CPPUTILS_STATIC_CAST(CinternalDLList_t, (*a_allocator)(sizeof(struct SCinternalDLList)));
	if (!pRet) {
		return CPPUTILS_NULL;
	}
	//CInternalDLListInitializeInline(pRet, a_allocator, a_deallocator);
	pRet->allocator = a_allocator;
	pRet->deallocator = a_deallocator ? a_deallocator : (&free);
	pRet->last = pRet->first = CPPUTILS_NULL;
	pRet->m_size = 0;
	return pRet;
}


static void CinternalDLListItemExtraCleaner(void* a_container, struct SCinternalDLListIterator* CPPUTILS_ARG_NN a_iter, TypeCinternalDeallocator CPPUTILS_ARG_NN a_remainingDataCleaner) CPPUTILS_NOEXCEPT
{
	CPPUTILS_STATIC_CAST(void, a_container);
	(*a_remainingDataCleaner)(CInternalDLListItemFromDLListIterator(a_iter)->data);
}


CINTERNAL_EXPORT void CInternalDLListDestroyEx(CinternalDLList_t CPPUTILS_ARG_NN a_list, TypeCinternalDeallocator a_remainingDataCleaner)
{
	CInternalListCleanInline(a_list->first, a_list->deallocator, a_list,a_remainingDataCleaner,&CinternalDLListItemExtraCleaner);
	(*(a_list->deallocator))(a_list);
}


CINTERNAL_EXPORT CinternalDLListItem_t CInternalDLListAddDataBeforeIterator(CinternalDLList_t CPPUTILS_ARG_NN a_list, CinternalDLListItem_t CPPUTILS_ARG_NN a_iter, const void* a_data)
{
	struct SCinternalDLListItem* const pNewItem = CPPUTILS_STATIC_CAST(struct SCinternalDLListItem*, (*(a_list->allocator))(sizeof(struct SCinternalDLListItem)));
	if (!pNewItem) {
		return CPPUTILS_NULL;
	}
	pNewItem->data = CPPUTILS_CONST_CAST(void*, a_data);
	CInternalDLListAddCreatedIteratorBeforeIteratorInline(&(a_list->first), CInternalDLListIteratorFromDLListItem(a_iter), &(pNewItem->itr));
	++(a_list->m_size);
	return pNewItem;
}


CINTERNAL_EXPORT CinternalDLListItem_t CInternalDLListAddDataAfterIterator(CinternalDLList_t CPPUTILS_ARG_NN a_list, CinternalDLListItem_t CPPUTILS_ARG_NN a_iter, const void* a_data)
{
	struct SCinternalDLListItem* const pNewItem = CPPUTILS_STATIC_CAST(struct SCinternalDLListItem*, (*(a_list->allocator))(sizeof(struct SCinternalDLListItem)));
	if (!pNewItem) {
		return CPPUTILS_NULL;
	}
	pNewItem->data = CPPUTILS_CONST_CAST(void*, a_data);
	CInternalDLListAddCreatedIteratorAfterIteratorInline(&(a_list->last), CInternalDLListIteratorFromDLListItem(a_iter), &(pNewItem->itr));
	++(a_list->m_size);
	return pNewItem;
}


CINTERNAL_EXPORT CinternalDLListItem_t CInternalDLListAddDataToFront(CinternalDLList_t CPPUTILS_ARG_NN a_list, const void* a_data)
{
	struct SCinternalDLListItem* const pNewItem = CPPUTILS_STATIC_CAST(struct SCinternalDLListItem*, (*(a_list->allocator))(sizeof(struct SCinternalDLListItem)));
	if (!pNewItem) {
		return CPPUTILS_NULL;
	}
	pNewItem->data = CPPUTILS_CONST_CAST(void*, a_data);
	CInternalDLListAddCreatedIteratorFrontInline2(&(a_list->first) ,&(a_list->last), CInternalDLListIteratorFromDLListItem(pNewItem));
	++(a_list->m_size);
	return pNewItem;
}


CINTERNAL_EXPORT CinternalDLListItem_t CInternalDLListAddDataToBack(CinternalDLList_t CPPUTILS_ARG_NN a_list, const void* a_data)
{
	struct SCinternalDLListItem* const pNewItem = CPPUTILS_STATIC_CAST(struct SCinternalDLListItem*, (*(a_list->allocator))(sizeof(struct SCinternalDLListItem)));
	if (!pNewItem) {
		return CPPUTILS_NULL;
	}
	pNewItem->data = CPPUTILS_CONST_CAST(void*, a_data);
	CInternalDLListAddCreatedIteratorBackInline(&(a_list->first), &(a_list->last), CInternalDLListIteratorFromDLListItem(pNewItem));
	++(a_list->m_size);
	return pNewItem;
}


CINTERNAL_EXPORT CinternalDLListItem_t CInternalDLListFirstItem(ConstCinternalDLList_t CPPUTILS_ARG_NN a_list)
{
	return CInternalDLListItemFromDLListIterator(a_list->first);
}


CINTERNAL_EXPORT CinternalDLListItem_t CInternalDLListLastItem(ConstCinternalDLList_t CPPUTILS_ARG_NN a_list)
{
	return CInternalDLListItemFromDLListIterator(a_list->last);
}


CINTERNAL_EXPORT void CInternalDLListRemoveData(CinternalDLList_t CPPUTILS_ARG_NN a_list, CinternalDLListItem_t CPPUTILS_ARG_NN a_iterator)
{
	CInternalListRemoveItertaorInline2(&(a_list->first), &(a_list->last), CInternalDLListIteratorFromDLListItem(a_iterator));
	(*(a_list->deallocator))(CPPUTILS_REINTERPRET_CAST(struct SCinternalDLListItem*, CPPUTILS_CONST_CAST(struct SCinternalDLListItem*, a_iterator)));
	--(a_list->m_size);
}


CINTERNAL_EXPORT size_t CInternalDLListSize(ConstCinternalDLList_t CPPUTILS_ARG_NN a_list)
{
	return a_list->m_size;
}


CPPUTILS_END_C