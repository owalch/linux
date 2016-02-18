#ifndef MYLIST_HEADER
#define MYLIST_HEADER

//******************************************************************************
// Definition of structs TNode and TList
// J. Zeman, Oct. 1999, M. Thaler, Sept. 2003
// M. Thaler, Feb. 2011 -> from C++ to pure C, 
//                      -> changed naming
//                      -> single linked list with header dummy
//******************************************************************************

#include "mythread.h"

//------------------------------------------------------------------------------
// list node

typedef struct TNode{
    struct ThreadCB *data;              // pointer to data
    struct TNode    *next;              // pointer to next list element
} TNode;

//------------------------------------------------------------------------------
// list header (we use her type TNode)

typedef struct {
    unsigned    numNodes;               // number of list elements
    TNode       *head;                  // pointer to header node
    TNode       *tail;                  // pointer to tail node
    TNode       *iter;                  // pointer for iterartions
} TList;

//------------------------------------------------------------------------------

TList*      tlNewList();                // setup list with dummy header node
void        tlDelList(TList *list);     // delete list including data

void        tlEnqueue(TList *list, ThreadCB *dat); // append thread data to list
ThreadCB*   tlDequeue(TList *list);     // take first element out of the list
                                        // return ptr to thread struct or NULL

void        tlSortIn(TList *list, ThreadCB *dat); // insert thread data sorted
                                                  // according ready time

ThreadCB*   tlReadFirst(TList *list);   // return ptr to the first thread data
                                        // struct in list, do not dequeue not

unsigned    tlGetNumNodes(TList *list); // return number of elements in list
void        tlSetPtrFirst(TList *list); // set iter pointer to first element
void        tlSetPtrNext(TList *list);  // move iter pointer to next element
ThreadCB*   tlReadCurrent(TList *list); // return thread data via iter pointer

//******************************************************************************

#endif // MYLIST_HEADER
