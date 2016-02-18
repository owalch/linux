/**
 * @file    mylist.c
 * @brief   Implementation file for the list handling
 *
 * This file contains the list handling.
 *
 *
 *
 * @author  M. Thaler
 * @author  O. Walch
 *
 * @date    2012-04-17
 * @version 1.0
 */
#include <stdlib.h>

#include "mythread.h"
#include "mylist.h"

/******************************************************************************/
// macros to allocate new TNode and TList
/******************************************************************************/
#define newTNode() (TNode *)malloc(sizeof(TNode))
#define newTList() (TList *)malloc(sizeof(TList))


/******************************************************************************/
// public functions implementations
/******************************************************************************/
/**
 * @fn      TList* tlNewList(void)
 * @brief   Setup list with dummy header node
 * @return  TList pointer to the created list
 *
 * This function sets up a new List with a dummy node. The list contains three
 * pointers, head, iter and tail as well as a counter for the enqueued nodes.
 */
TList* tlNewList(void)
{
    TNode *dummy = newTNode();                  // TList's dummy node
    TList *list  = newTList();                  // new list

    /* dummy node pointers */
    dummy->data  = NULL;                        // set dummy data ptr to NULL
    dummy->next  = NULL;                        // no next node available

    /* list pointers */
    list->numNodes  = 0;                        // dummy node is not counted
    list->head      = dummy;                    // set head ptr to the dummy
    list->tail      = dummy;                    // set tail ptr to the dummy
    list->iter      = NULL;                     // set iter ptr to NULL
    
    return list;                                // pointer to the allocated list
}

/******************************************************************************/
/**
 * @fn      void tlDelList(TList *list)
 * @brief   Delete list including data
 * @param   list TList Pointer to the list
 *
 * This function frees the list. It checks if the list still contains nodes.
 * If any, it frees it before freeing the allocated list.
 */
void tlDelList(TList *list)
{
    tlSetPtrFirst(list);                        // set iter ptr to the first node

    while (list->head->next != NULL) {
        list->head->next = list->iter->next;
        free(list->iter);
        tlSetPtrFirst(list);                    // refresh iter ptr
    }
    free(list->head);                           // free dummy node
    free(list);                                 // free list
}

/******************************************************************************/
/**
 * @fn      void tlEnqueue(TList *list, ThreadCB *tcb)
 * @brief   Append thread data to list
 * @param   list TList pointer to the list
 * @param   tcb  ThreadCB pointer to the thread control block
 *
 * This function enqueues a node to the list and sets the list tail pointer
 * the the new last node.
 */
void tlEnqueue(TList *list, ThreadCB *tcb)
{
    TNode *node = newTNode();                   // create new node

    /* new node pointers */
    node->data  = tcb;                          // ptr to data
    node->next  = NULL;                         // node is last element

    /* list pointers */
    list->tail->next    = node;                 // set olt tail next to new tail
    list->tail          = node;                 // set tail ptr to the new node
    list->numNodes      += 1;                   // add node to numNodes

}

/******************************************************************************/
/**
 * @fn      ThreadCB* tlDequeue(TList *list)
 * @brief   Take first element out of the list
 * @param   list TList pointer to the list
 *
 * This function removes the first node. (not the dummy node).
 * A pointer to the ThreadCB sctruct or NULL is returned.
 */
ThreadCB* tlDequeue(TList *list)
{
    ThreadCB *oldThread = NULL;                 // buffer for the old thread
    tlSetPtrFirst(list);

    /* check if a next node exists */
    if (list->head->next != NULL)
        oldThread = list->head->next->data;

    if (list->numNodes > 0) {
        list->head->next = list->head->next->next;
        list->numNodes -= 1;

        /* if dummy node is last node */
        if (list->numNodes == 0) {
            list->tail = list->head;
        }
    }

    /* return NULL if no data is available */
    if (oldThread != NULL)
        free(list->iter);                       // BUG
    
    return oldThread;
}

/******************************************************************************/
/**
 * @fn      void tlSortIn(TList* list, ThreadCB* tcb)
 * @brief   Insert thread data sorted according ready time
 * @param   list TList pointer to the list
 * @param   tcb ThreadCB pointer to the thread control block
 *
 * This function enqueues a new thread to the list according to the read time.
 */
void tlSortIn(TList* list, ThreadCB* tcb)
{
    int node_enqueued = 0;                      // flag for new node

    /* check if list is empty */
    if (list->numNodes == 0)
        tlEnqueue(list,tcb);                    // enqueue node on empty list
    else {
        TNode *node = newTNode();               // create new node
        
        node->data  = tcb;                      // ptr to data
        tlSetPtrFirst(list);                    // set iter ptr to the firs node

        if (tcb->readyTime <= list->iter->data->readyTime) {
            /* enqueue node as first node */
            node->next = list->head->next;
            list->head->next = node;
            list->numNodes += 1;
        } else {
            while (list->iter != NULL) {
                if (list->iter->next != NULL) {
                    if (tcb->readyTime <= list->iter->next->data->readyTime) {
                        /* enque node after iter ptr node */
                        node->next = list->iter->next;
                        list->iter->next = node;
                        list->numNodes += 1;
                        node_enqueued = 1;
                        break;
                    }
                }
                tlSetPtrNext(list);
            }
            /* enqueue node if readyTime is biggest */
            if (node_enqueued == 0)
                tlEnqueue(list, tcb);
        }
    }
}

/******************************************************************************/
/**
 * @fn      ThreadCB* tlReadFirst(TList *list)
 * @brief   Return a pointer to the first thread
 * @param   list TList Pointer to the list
 * @return  ThreadCB pointer to the first thread
 *
 * This function returns a pointer to the first not dummy node in the list.
 * If no node is available, a Null pointer will be returned.
 */
ThreadCB* tlReadFirst(TList *list)
{
    if (list->head->next != NULL)
        return list->head->next->data;          // ptr to the first node
    else
        return list->head->data;                // ptr to the dummy node
}

/******************************************************************************/
/**
 * @fn      unsigned tlGetNumNodes(TList *list)
 * @brief   Return the number of elements in list
 * @param   list TList pointer to the list
 * @return  unsigned number of nodes in the list
 */
unsigned tlGetNumNodes(TList *list)
{
    return list->numNodes;                      // number of elements in the list
}

/******************************************************************************/
/**
 * @fn      void tlSetPtrFirst(TList *list)
 * @brief   Set iteration pointer to first element
 * @param   list TList pointer to the list
 */
void tlSetPtrFirst(TList *list)
{
    list->iter  = list->head->next;             // set ptr to the first node
}

/******************************************************************************/
/**
 * @fn      void tlSetPtrNext(TList *list)
 * @brief   Move itaration pointer to next list element
 * @param   list TList pointer to the list
 */
void tlSetPtrNext(TList *list)
{
    if (list->iter != NULL)
        list->iter = list->iter->next;          // set ptr only if != 0
}

/******************************************************************************/
/**
 * @fn      ThreadCB* tlReadCurrent(TList *list)
 * @brief   Return thread data via iter pointer
 * @param   list TList pointer to the list
 * @return  ThreadCB pointer to the current thread
 */
ThreadCB* tlReadCurrent(TList *list)
{
    if (list->iter != NULL)
        return list->iter->data;                // return data ptr
    else
        return NULL;
}

