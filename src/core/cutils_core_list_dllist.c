//
// repo:			cutils
// file:            cutils_core_list_dllist.c
// path:			src/core/cutils_core_list_dllist.c
// created on:		2023 Feb 25
// created by:		Davit Kalantaryan (davit.kalantaryan@desy.de)
// explanation:		Double Linked List
//


#include <cutils/list/dllist.h>
#define CUTILS_SRC_CORE_CUTILS_CORE_LIST_DLLIST_IMPL_H_NEEDED			1
#define CInternalListRemoveItertaorInline2_needed						1
#define CUtilDLListAddCreatedIteratorBeforeIteratorInline_needed		1
#define CUtilDLListAddCreatedIteratorAfterIteratorInline_needed			1
#define CUtilDLListAddCreatedIteratorFrontInline2_needed				1
#define CUtilDLListAddCreatedIteratorBackInline_needed					1
#include "cutils_core_list_dllist.impl.h"


CPPUTILS_BEGIN_C


struct CPPUTILS_DLL_PRIVATE SCutilDLList {
	TypeCinternalAllocator			allocator;
	TypeCinternalDeallocator		deallocator;
	struct SCutilDLListIterator		*first, *last;
	size_t							m_size;
};


CUTILS_EXPORT CutilDLList_t CUtilDLListCreateEx(TypeCinternalAllocator a_allocator, TypeCinternalDeallocator a_deallocator)
{
	CutilDLList_t pRet;
	a_allocator = a_allocator ? a_allocator : (&malloc);
	pRet = CPPUTILS_STATIC_CAST(CutilDLList_t, (*a_allocator)(sizeof(struct SCutilDLList)));
	if (!pRet) {
		return CPPUTILS_NULL;
	}
	//CUtilDLListInitializeInline(pRet, a_allocator, a_deallocator);
	pRet->allocator = a_allocator;
	pRet->deallocator = a_deallocator ? a_deallocator : (&free);
	pRet->last = pRet->first = CPPUTILS_NULL;
	pRet->m_size = 0;
	return pRet;
}


static void CutilDLListItemExtraCleaner(void* a_container, struct SCutilDLListIterator* CPPUTILS_ARG_NN a_iter, TypeCinternalDeallocator CPPUTILS_ARG_NN a_remainingDataCleaner) CPPUTILS_NOEXCEPT
{
	CPPUTILS_STATIC_CAST(void, a_container);
	(*a_remainingDataCleaner)(CUtilDLListItemFromDLListIterator(a_iter)->data);
}


CUTILS_EXPORT void CUtilDLListDestroyEx(CutilDLList_t CPPUTILS_ARG_NN a_list, TypeCinternalDeallocator a_remainingDataCleaner)
{
	CInternalListCleanInline(a_list->first, a_list->deallocator, a_list,a_remainingDataCleaner,&CutilDLListItemExtraCleaner);
	(*(a_list->deallocator))(a_list);
}


CUTILS_EXPORT CutilDLListItem_t CUtilDLListAddDataBeforeIterator(CutilDLList_t CPPUTILS_ARG_NN a_list, CutilDLListItem_t CPPUTILS_ARG_NN a_iter, const void* a_data)
{
	struct SCutilDLListItem* const pNewItem = CPPUTILS_STATIC_CAST(struct SCutilDLListItem*, (*(a_list->allocator))(sizeof(struct SCutilDLListItem)));
	if (!pNewItem) {
		return CPPUTILS_NULL;
	}
	pNewItem->data = CPPUTILS_CONST_CAST(void*, a_data);
	CUtilDLListAddCreatedIteratorBeforeIteratorInline(&(a_list->first), CUtilDLListIteratorFromDLListItem(a_iter), &(pNewItem->itr));
	++(a_list->m_size);
	return pNewItem;
}


CUTILS_EXPORT CutilDLListItem_t CUtilDLListAddDataAfterIterator(CutilDLList_t CPPUTILS_ARG_NN a_list, CutilDLListItem_t CPPUTILS_ARG_NN a_iter, const void* a_data)
{
	struct SCutilDLListItem* const pNewItem = CPPUTILS_STATIC_CAST(struct SCutilDLListItem*, (*(a_list->allocator))(sizeof(struct SCutilDLListItem)));
	if (!pNewItem) {
		return CPPUTILS_NULL;
	}
	pNewItem->data = CPPUTILS_CONST_CAST(void*, a_data);
	CUtilDLListAddCreatedIteratorAfterIteratorInline(&(a_list->last), CUtilDLListIteratorFromDLListItem(a_iter), &(pNewItem->itr));
	++(a_list->m_size);
	return pNewItem;
}


CUTILS_EXPORT CutilDLListItem_t CUtilDLListAddDataToFront(CutilDLList_t CPPUTILS_ARG_NN a_list, const void* a_data)
{
	struct SCutilDLListItem* const pNewItem = CPPUTILS_STATIC_CAST(struct SCutilDLListItem*, (*(a_list->allocator))(sizeof(struct SCutilDLListItem)));
	if (!pNewItem) {
		return CPPUTILS_NULL;
	}
	pNewItem->data = CPPUTILS_CONST_CAST(void*, a_data);
	CUtilDLListAddCreatedIteratorFrontInline2(&(a_list->first) ,&(a_list->last), CUtilDLListIteratorFromDLListItem(pNewItem));
	++(a_list->m_size);
	return pNewItem;
}


CUTILS_EXPORT CutilDLListItem_t CUtilDLListAddDataToBack(CutilDLList_t CPPUTILS_ARG_NN a_list, const void* a_data)
{
	struct SCutilDLListItem* const pNewItem = CPPUTILS_STATIC_CAST(struct SCutilDLListItem*, (*(a_list->allocator))(sizeof(struct SCutilDLListItem)));
	if (!pNewItem) {
		return CPPUTILS_NULL;
	}
	pNewItem->data = CPPUTILS_CONST_CAST(void*, a_data);
	CUtilDLListAddCreatedIteratorBackInline(&(a_list->first), &(a_list->last), CUtilDLListIteratorFromDLListItem(pNewItem));
	++(a_list->m_size);
	return pNewItem;
}


CUTILS_EXPORT CutilDLListItem_t CUtilDLListFirstItem(ConstCutilDLList_t CPPUTILS_ARG_NN a_list)
{
	return CUtilDLListItemFromDLListIterator(a_list->first);
}


CUTILS_EXPORT CutilDLListItem_t CUtilDLListLastItem(ConstCutilDLList_t CPPUTILS_ARG_NN a_list)
{
	return CUtilDLListItemFromDLListIterator(a_list->last);
}


CUTILS_EXPORT void CUtilDLListRemoveData(CutilDLList_t CPPUTILS_ARG_NN a_list, CutilDLListItem_t CPPUTILS_ARG_NN a_iterator)
{
	CInternalListRemoveItertaorInline2(&(a_list->first), &(a_list->last), CUtilDLListIteratorFromDLListItem(a_iterator));
	(*(a_list->deallocator))(CPPUTILS_REINTERPRET_CAST(struct SCutilDLListItem*, CPPUTILS_CONST_CAST(struct SCutilDLListItem*, a_iterator)));
	--(a_list->m_size);
}


CUTILS_EXPORT size_t CUtilDLListSize(ConstCutilDLList_t CPPUTILS_ARG_NN a_list)
{
	return a_list->m_size;
}


CPPUTILS_END_C
