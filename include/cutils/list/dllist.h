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

struct SCinternalDLList;
typedef struct SCinternalDLList* CinternalDLList_t;
typedef const struct SCinternalDLList* ConstCinternalDLList_t;

struct SCinternalDLListItem {
	struct SCinternalDLListIterator	itr;
	void*							data;
};
typedef const struct SCinternalDLListItem* CinternalDLListItem_t;

#define CInternalDLListIteratorFromDLListItem(_item_ptr)	(&((_item_ptr)->itr))
#define CInternalDLListItemFromDLListIterator(_iter_ptr)	cpputils_container_of(_iter_ptr,const struct SCinternalDLListItem,itr)

CUTILS_EXPORT CinternalDLList_t CInternalDLListCreateEx(TypeCinternalAllocator a_allocator, TypeCinternalDeallocator a_deallocator);
CUTILS_EXPORT void	CInternalDLListDestroyEx(CinternalDLList_t CPPUTILS_ARG_NN a_list, TypeCinternalDeallocator a_remainingDataCleaner);
CUTILS_EXPORT CinternalDLListItem_t CInternalDLListFirstItem(ConstCinternalDLList_t CPPUTILS_ARG_NN a_list);
CUTILS_EXPORT CinternalDLListItem_t CInternalDLListLastItem(ConstCinternalDLList_t CPPUTILS_ARG_NN a_list);
CUTILS_EXPORT void	CInternalDLListRemoveData(CinternalDLList_t CPPUTILS_ARG_NN a_list, CinternalDLListItem_t CPPUTILS_ARG_NN a_iterator);
CUTILS_EXPORT size_t CInternalDLListSize(ConstCinternalDLList_t CPPUTILS_ARG_NN a_list);
CUTILS_EXPORT CinternalDLListItem_t CInternalDLListAddDataBeforeIterator(CinternalDLList_t CPPUTILS_ARG_NN a_list, CinternalDLListItem_t CPPUTILS_ARG_NN a_iter, const void* a_data);
CUTILS_EXPORT CinternalDLListItem_t CInternalDLListAddDataAfterIterator(CinternalDLList_t CPPUTILS_ARG_NN a_list, CinternalDLListItem_t CPPUTILS_ARG_NN a_iter, const void* a_data);
CUTILS_EXPORT CinternalDLListItem_t CInternalDLListAddDataToFront(CinternalDLList_t CPPUTILS_ARG_NN a_list, const void* a_data);
CUTILS_EXPORT CinternalDLListItem_t CInternalDLListAddDataToBack(CinternalDLList_t CPPUTILS_ARG_NN a_list, const void* a_data);


CPPUTILS_END_C

#define CInternalDLListCreate()						CInternalDLListCreateEx(CPPUTILS_NULL,CPPUTILS_NULL)
#define CInternalDLListDestroy(_list)				CInternalDLListDestroyEx(_list,CPPUTILS_NULL)

#ifdef _MSC_VER
#define CInternalDLListAddDataBeforeIteratorFn(_list,_iter,_fn)		\
	__pragma(warning (push))										\
	__pragma(warning (disable:5039))								\
	CInternalDLListAddDataBeforeIterator(_list,_iter,(void*)(_fn))	\
	__pragma(warning (pop))

#else
#define CInternalDLListAddDataBeforeIteratorFn(_list,_iter,_fn)	CInternalDLListAddDataBeforeIterator(_list,_iter,(void*)(_fn))
#endif

#ifdef _MSC_VER
#define CInternalDLListAddDataAfterIteratorFn(_list,_iter,_fn)		\
	__pragma(warning (push))										\
	__pragma(warning (disable:5039))								\
	CInternalDLListAddDataAfterIterator(_list,_iter,(void*)(_fn))	\
	__pragma(warning (pop))

#else
#define CInternalDLListAddDataAfterIteratorFn(_list,_iter,_fn)	CInternalDLListAddDataAfterIterator(_list,_iter,(void*)(_fn))
#endif

#ifdef _MSC_VER
#define CInternalDLListAddDataToFrontFn(_list,_fn)		\
	__pragma(warning (push))							\
	__pragma(warning (disable:5039))					\
	CInternalDLListAddDataToFront(_list,(void*)(_fn))	\
	__pragma(warning (pop))

#else
#define CInternalDLListAddDataToFrontFn(_list,_fn)	CInternalDLListAddDataToFront(_list,(void*)(_fn))
#endif

#ifdef _MSC_VER
#define CInternalDLListAddDataToBackFn(_list,_fn)		\
	__pragma(warning (push))							\
	__pragma(warning (disable:5039))					\
	CInternalDLListAddDataToBack(_list,(void*)(_fn))	\
	__pragma(warning (pop))

#else
#define CInternalDLListAddDataToBackFn(_list,_fn)	CInternalDLListAddDataToBack(_list,(void*)(_fn))
#endif


#endif  // #ifndef CUTILS_INCLUDE_CUTILS_LIST_LLIST_H
