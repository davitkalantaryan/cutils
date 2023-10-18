//
// repo:			cutils
// file:            cutils_core_list_dllist.impl.h
// path:			src/core/cutils_core_list_dllist.impl.h
// created on:		2023 Apr 11
// created by:		Davit Kalantaryan (davit.kalantaryan@desy.de)
//


#ifndef CUTILS_SRC_CORE_CUTILS_CORE_LIST_DLLIST_IMPL_H
#define CUTILS_SRC_CORE_CUTILS_CORE_LIST_DLLIST_IMPL_H

#include <cinternal/internal_header.h>

#ifdef CUTILS_SRC_CORE_CUTILS_CORE_LIST_DLLIST_IMPL_H_NEEDED

#include <cutils/common_data02.h>
#include <cinternal/common_data01.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

//#define CInternalListItemToIter(_item_ptr)		CPPUTILS_REINTERPRET_CAST(struct SCinternalListIterator*,_item_ptr)
#define CInternalItemToIterator(_item_ptr)			(&((_item_ptr)->itr))

#ifdef CUTILS_INLINE2
#undef CUTILS_INLINE2
#endif

//#define CUTILS_INLINE2
#define CUTILS_INLINE2	inline

#ifdef _MSC_VER
#ifdef __cplusplus
#pragma warning (disable:5039)
#endif
#elif defined(__GNUC__) 
#pragma GCC diagnostic ignored "-Wattributes"
#endif


CPPUTILS_BEGIN_C

typedef void (*TypeCutilListItemExtraCleaner)(void* a_container, struct SCutilDLListIterator* a_iter, TypeCinternalDeallocator a_remainingDataCleaner);


static void CinternalDefaultDataCleaner(void* a_pData) CPPUTILS_NOEXCEPT  {
	CPPUTILS_STATIC_CAST(void, a_pData);
}


//struct CPPUTILS_DLL_PRIVATE SCinternalDLList {
//	TypeCinternalAllocator			allocator;
//	TypeCinternalDeallocator		deallocator;
//	struct SCinternalListIterator	*first, *last;
//	size_t							m_size;
//};


//static CUTILS_INLINE2 void CUtilDLListInitializeInline(CinternalDLList_t a_list, TypeCinternalAllocator CPPUTILS_ARG_NN a_allocator, TypeCinternalDeallocator a_deallocator) CPPUTILS_NOEXCEPT  {
//	a_list->allocator = a_allocator;
//	a_list->deallocator = a_deallocator ? a_deallocator : (&free);
//	a_list->last = a_list->first = CPPUTILS_NULL;
//	a_list->m_size = 0;
//}


static CUTILS_INLINE2 void CInternalListCleanInline(	struct SCutilDLListIterator* a_first, TypeCinternalDeallocator a_deallocator, void* a_container,
														TypeCinternalDeallocator a_remainingDataCleaner, TypeCutilListItemExtraCleaner a_extraCleaner) CPPUTILS_NOEXCEPT {
	struct SCutilDLListIterator*pItemTmp, *pItem = a_first;
	a_remainingDataCleaner = a_remainingDataCleaner ? a_remainingDataCleaner : (&CinternalDefaultDataCleaner); // if null, then data should not be cleaned
	while (pItem) {
		pItemTmp = pItem->next;
		(*a_extraCleaner)(a_container, pItem, a_remainingDataCleaner);
		(*(a_deallocator))(pItem);
		pItem = pItemTmp;
	}
}


#ifdef CUtilDLListAddCreatedIteratorBeforeIteratorInline_needed
static CUTILS_INLINE2 void CUtilDLListAddCreatedIteratorBeforeIteratorInline(struct SCutilDLListIterator** CPPUTILS_ARG_NN a_first_p,
																					CutilDLListIterator_t CPPUTILS_ARG_NN a_iter, 
																					struct SCutilDLListIterator* CPPUTILS_ARG_NN a_pNewIter) CPPUTILS_NOEXCEPT  {
	struct SCutilDLListIterator* const pIterInp = CPPUTILS_CONST_CAST(struct SCutilDLListIterator*, a_iter);
	a_pNewIter->next = pIterInp;
	a_pNewIter->prev = pIterInp->prev;
	if (pIterInp->prev) {
		pIterInp->prev->next = a_pNewIter;
	}

	if (pIterInp == (*a_first_p)) {
		*a_first_p = a_pNewIter;
	}	
}
#endif  //  #ifdef CUtilDLListAddCreatedIteratorBeforeIteratorInline_needed


#ifdef CUtilDLListAddCreatedIteratorAfterIteratorInline_needed
static CUTILS_INLINE2 void CUtilDLListAddCreatedIteratorAfterIteratorInline(	struct SCutilDLListIterator** CPPUTILS_ARG_NN a_last_p,
																					CutilDLListIterator_t CPPUTILS_ARG_NN a_iter, 
																					struct SCutilDLListIterator* CPPUTILS_ARG_NN a_pNewIter) CPPUTILS_NOEXCEPT  {
	struct SCutilDLListIterator* const pIterInp = CPPUTILS_CONST_CAST(struct SCutilDLListIterator*, a_iter);
	a_pNewIter->prev = pIterInp;
	a_pNewIter->next = pIterInp->prev;
	if (pIterInp->next) {
		pIterInp->next->prev = a_pNewIter;
	}

	if (pIterInp == (*a_last_p)) {
		*a_last_p = a_pNewIter;
	}
}
#endif  //  #ifdef CUtilDLListAddCreatedIteratorAfterIteratorInline_needed


#ifdef CUtilDLListAddCreatedIteratorFrontInline1_needed
static CUTILS_INLINE2 void CUtilDLListAddCreatedIteratorFrontInline1(struct SCutilDLListIterator** CPPUTILS_ARG_NN a_first_p,
																			struct SCutilDLListIterator* CPPUTILS_ARG_NN a_pNewIter) CPPUTILS_NOEXCEPT {
	if ((*a_first_p)) {
		(*a_first_p)->prev = a_pNewIter;
	}
	a_pNewIter->prev = CPPUTILS_NULL;
	a_pNewIter->next = (*a_first_p);
	(*a_first_p) = a_pNewIter;
}
#endif  //  #ifdef CUtilDLListAddCreatedIteratorFrontInline1_needed


#ifdef CUtilDLListAddCreatedIteratorFrontInline2_needed
static CUTILS_INLINE2 void CUtilDLListAddCreatedIteratorFrontInline2(struct SCutilDLListIterator** CPPUTILS_ARG_NN a_first_p,struct SCutilDLListIterator** CPPUTILS_ARG_NN a_last_p,
																			struct SCutilDLListIterator* CPPUTILS_ARG_NN a_pNewIter) CPPUTILS_NOEXCEPT {
	if ((*a_first_p)) {
		(*a_first_p)->prev = a_pNewIter;
	}
	else {
		(*a_last_p) = a_pNewIter;
	}
	a_pNewIter->prev = CPPUTILS_NULL;
	a_pNewIter->next = (*a_first_p);
	(*a_first_p) = a_pNewIter;
}
#endif  //  #ifdef CUtilDLListAddCreatedIteratorFrontInline2_needed


#ifdef CUtilDLListAddCreatedIteratorBackInline_needed
static CUTILS_INLINE2 void CUtilDLListAddCreatedIteratorBackInline(	struct SCutilDLListIterator** CPPUTILS_ARG_NN a_first_p, struct SCutilDLListIterator** CPPUTILS_ARG_NN a_last_p,
																			struct SCutilDLListIterator* CPPUTILS_ARG_NN a_pNewIter) CPPUTILS_NOEXCEPT {
	if ((*a_last_p)) {
		(*a_last_p)->next = a_pNewIter;
	}
	else {
		(*a_first_p) = a_pNewIter;
	}
	a_pNewIter->next = CPPUTILS_NULL;
	a_pNewIter->prev = (*a_last_p);
	(*a_last_p) = a_pNewIter;
}
#endif  //  #ifdef CUtilDLListAddCreatedIteratorBackInline_needed



static CUTILS_INLINE2 void CInternalListRemoveItertaorInline1(	struct SCutilDLListIterator** CPPUTILS_ARG_NN a_first_p,
																	CutilDLListIterator_t CPPUTILS_ARG_NN a_iter) CPPUTILS_NOEXCEPT {
	if (a_iter->prev) {
		a_iter->prev->next = a_iter->next;
	}

	if (a_iter->next) {
		a_iter->next->prev = a_iter->prev;
	}

	if (a_iter == (*a_first_p)) {
		*a_first_p = a_iter->next;
	}
}


#ifdef CInternalListRemoveItertaorInline2_needed
static CUTILS_INLINE2 void CInternalListRemoveItertaorInline2(	struct SCutilDLListIterator** CPPUTILS_ARG_NN a_first_p, struct SCutilDLListIterator** CPPUTILS_ARG_NN a_last_p,
																	CutilDLListIterator_t CPPUTILS_ARG_NN a_iter) CPPUTILS_NOEXCEPT {
	CInternalListRemoveItertaorInline1(a_first_p, a_iter);
	if (a_iter == (*a_last_p)) {
		*a_last_p = a_iter->prev;
	}
}
#endif  //  #ifdef CInternalListRemoveItertaorInline2_needed



//static CUTILS_INLINE2 void CUtilDLListRemoveDataNoFreeInline(CinternalDLList_t a_list, CinternalListIterator_t a_iter) CPPUTILS_NOEXCEPT {
//	CInternalListRemoveItertaorInline(&(a_list->first), a_iter);
//	if (a_iter == a_list->last) {
//		a_list->last = a_iter->prev;
//	}
//	--(a_list->m_size);
//}


CPPUTILS_END_C


#endif  //  #ifdef CUTILS_SRC_CORE_CUTILS_CORE_LIST_DLLIST_IMPL_H_NEEDED
#endif  //  #ifndef CUTILS_SRC_CORE_CUTILS_CORE_LIST_DLLIST_IMPL_H
