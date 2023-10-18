//
// repo:			cutils
// file:            dllist.h
// path:			include/cutils/list/dllist.h
// created on:		2023 Feb 25
// created by:		Davit Kalantaryan (davit.kalantaryan@desy.de)
// explanation:		Double Linked List
//

#ifndef CUTILS_INCLUDE_CUTILS_LIST_LLIST_H
#define CUTILS_INCLUDE_CUTILS_LIST_LLIST_H

#include <cutils/export_symbols.h>
#include <cutils/common_data02.h>
#include <cinternal/common_data01.h>


CPPUTILS_BEGIN_C

struct SCutilDLList;
typedef struct SCutilDLList* CutilDLList_t;
typedef const struct SCutilDLList* ConstCutilDLList_t;

struct SCutilDLListItem {
	struct SCutilDLListIterator	itr;
	void*							data;
};
typedef const struct SCutilDLListItem* CutilDLListItem_t;

#define CUtilDLListIteratorFromDLListItem(_item_ptr)	(&((_item_ptr)->itr))
#define CUtilDLListItemFromDLListIterator(_iter_ptr)	cpputils_container_of(_iter_ptr,const struct SCutilDLListItem,itr)

CUTILS_EXPORT CutilDLList_t CUtilDLListCreateEx(TypeCinternalAllocator a_allocator, TypeCinternalDeallocator a_deallocator);
CUTILS_EXPORT void	CUtilDLListDestroyEx(CutilDLList_t CPPUTILS_ARG_NN a_list, TypeCinternalDeallocator a_remainingDataCleaner);
CUTILS_EXPORT CutilDLListItem_t CUtilDLListFirstItem(ConstCutilDLList_t CPPUTILS_ARG_NN a_list);
CUTILS_EXPORT CutilDLListItem_t CUtilDLListLastItem(ConstCutilDLList_t CPPUTILS_ARG_NN a_list);
CUTILS_EXPORT void	CUtilDLListRemoveData(CutilDLList_t CPPUTILS_ARG_NN a_list, CutilDLListItem_t CPPUTILS_ARG_NN a_iterator);
CUTILS_EXPORT size_t CUtilDLListSize(ConstCutilDLList_t CPPUTILS_ARG_NN a_list);
CUTILS_EXPORT CutilDLListItem_t CUtilDLListAddDataBeforeIterator(CutilDLList_t CPPUTILS_ARG_NN a_list, CutilDLListItem_t CPPUTILS_ARG_NN a_iter, const void* a_data);
CUTILS_EXPORT CutilDLListItem_t CUtilDLListAddDataAfterIterator(CutilDLList_t CPPUTILS_ARG_NN a_list, CutilDLListItem_t CPPUTILS_ARG_NN a_iter, const void* a_data);
CUTILS_EXPORT CutilDLListItem_t CUtilDLListAddDataToFront(CutilDLList_t CPPUTILS_ARG_NN a_list, const void* a_data);
CUTILS_EXPORT CutilDLListItem_t CUtilDLListAddDataToBack(CutilDLList_t CPPUTILS_ARG_NN a_list, const void* a_data);


CPPUTILS_END_C

#define CUtilDLListCreate()						CUtilDLListCreateEx(CPPUTILS_NULL,CPPUTILS_NULL)
#define CUtilDLListDestroy(_list)				CUtilDLListDestroyEx(_list,CPPUTILS_NULL)

#ifdef _MSC_VER
#define CUtilDLListAddDataBeforeIteratorFn(_list,_iter,_fn)		\
	__pragma(warning (push))										\
	__pragma(warning (disable:5039))								\
	CUtilDLListAddDataBeforeIterator(_list,_iter,(void*)(_fn))	\
	__pragma(warning (pop))

#else
#define CUtilDLListAddDataBeforeIteratorFn(_list,_iter,_fn)	CUtilDLListAddDataBeforeIterator(_list,_iter,(void*)(_fn))
#endif

#ifdef _MSC_VER
#define CUtilDLListAddDataAfterIteratorFn(_list,_iter,_fn)		\
	__pragma(warning (push))										\
	__pragma(warning (disable:5039))								\
	CUtilDLListAddDataAfterIterator(_list,_iter,(void*)(_fn))	\
	__pragma(warning (pop))

#else
#define CUtilDLListAddDataAfterIteratorFn(_list,_iter,_fn)	CUtilDLListAddDataAfterIterator(_list,_iter,(void*)(_fn))
#endif

#ifdef _MSC_VER
#define CUtilDLListAddDataToFrontFn(_list,_fn)		\
	__pragma(warning (push))							\
	__pragma(warning (disable:5039))					\
	CUtilDLListAddDataToFront(_list,(void*)(_fn))	\
	__pragma(warning (pop))

#else
#define CUtilDLListAddDataToFrontFn(_list,_fn)	CUtilDLListAddDataToFront(_list,(void*)(_fn))
#endif

#ifdef _MSC_VER
#define CUtilDLListAddDataToBackFn(_list,_fn)		\
	__pragma(warning (push))							\
	__pragma(warning (disable:5039))					\
	CUtilDLListAddDataToBack(_list,(void*)(_fn))	\
	__pragma(warning (pop))

#else
#define CUtilDLListAddDataToBackFn(_list,_fn)	CUtilDLListAddDataToBack(_list,(void*)(_fn))
#endif


#endif  // #ifndef CUTILS_INCLUDE_CUTILS_LIST_LLIST_H
