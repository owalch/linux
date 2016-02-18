/**
 * @file    mylist.h
 * @brief   Header file for the list handling
 *
 * This file contains the global header information.
 *
 *
 *
 * @author  M. Thaler
 * @author  O. Walch
 *
 * @date    2012-04-17
 * @version 1.0
 */

#ifndef MYLIST_HEADER_H
#define MYLIST_HEADER_H

#include "mythread.h"

/**
 * @struct      TNode
 * @brief       This struct contains the Node information
 */
typedef struct TNode{
    struct ThreadCB *data;              /**< pointer to the data thread*/
    struct TNode    *next;              /**< pointer to next list element */
} TNode;

/******************************************************************************/
/**
 * @struct      TList
 * @brief       This struct contains the list information
 */
typedef struct {
    unsigned    numNodes;               /**< number of list elements */
    TNode       *head;                  /**< pointer to header node */
    TNode       *tail;                  /**< pointer to tail node */
    TNode       *iter;                  /**< pointer for iterartions */
} TList;

/******************************************************************************/

TList*      tlNewList(void);            // setup list with dummy header node
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

/******************************************************************************/

#endif  /* MYLIST_HEADER_H */

