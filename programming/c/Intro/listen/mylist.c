//******************************************************************************
// Implementation of mylist.c
// J. Zeman, Oct. 1999, M. Thaler, Sept. 2003
// M. Thaler, Feb. 2011 -> from C++ to pure C,
//                      -> changed naming
//                      -> single linked list with header dummy
// O. Walch, Feb. 2012  -> functions implemented
//******************************************************************************

#include <stdlib.h>

#include "mythread.h"
#include "mylist.h"

//******************************************************************************
// macro to allocate new TNode and TList
#define newTNode() (TNode *)malloc(sizeof(TNode))
#define newTList() (TList *)malloc(sizeof(TList))


//******************************************************************************
/**
 * tlNewList() - Setup list with dummy header node
 *
 * This function sets up a new List with a dummy node. The list contains three
 * pointers, head, iter and tail as well as a counter for the enqueued nodes.
 */
TList* tlNewList()
{
    TNode *dummy = newTNode();          // TList's dummy node
    TList *list  = newTList();          // new list

    /* dummy node pointers */
    dummy->data  = NULL;                // set dummy data ptr to NULL
    dummy->next  = NULL;                // no next node available -> NULL

    /* list pointers */
    list->numNodes  = 0;                // dummy node is not counted
    list->head      = dummy;            // set head ptr to the dummy node
    list->tail      = dummy;            // set tail ptr to the dummy node
    list->iter      = NULL;             // set iter ptr to NULL
    
    return list;                        // pointer to the allocated list
}

//******************************************************************************
/**
 * tlDelList() - Delete list including data
 * @list:       Pointer to the list
 *
 * This function frees the list. It checks if the list still contains nodes.
 * If any, it frees it before freeing the allocated list.
 */
void tlDelList(TList *list)
{
    tlSetPtrFirst(list);                // set iter ptr to the first node

    while (list->head->next != NULL) {
        list->head->next = list->iter->next;
        free(list->iter);
        tlSetPtrFirst(list);            // refresh iter ptr
    }
    free(list->head);                   // free dummy node
    free(list);                         // free list
}

//******************************************************************************
/**
 * tlEnqueue() - Append thread data to list
 * @list:       Pointer to the list
 * @dat:        Pointer to the thread control block
 *
 * This function enqueues a node to the list and sets the list tail pointer
 * the the new last node.
 */
void tlEnqueue(TList *list, ThreadCB *dat)
{
    TNode *node = newTNode();           // create new node

    /* new node pointers */
    node->data  = dat;                  // ptr to data
    node->next  = NULL;                 // node is last element

    /* list pointers */
    list->tail->next    = node;         // set olt tail next to new tail
    list->tail          = node;         // set tail ptr to the new node
    list->numNodes      += 1;           // add node to numNodes

}

//******************************************************************************
/**
 * tlDequeue() - Take first element out of the list
 * @list:       Pointer to the list
 *
 * This function removes the first node. (not the dummy node).
 * A pointer to the ThreadCB sctruct or NULL is returned.
 */
ThreadCB* tlDequeue(TList *list)
{
    ThreadCB *oldThread = NULL;         // buffer for the old thread
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
        free(list->iter);               // BUG
    
    return oldThread;
}

//******************************************************************************
/**
 * tlSortIn() - Insert thread data sorted according ready time
 * @list:       Pointer to the list
 * @dat:        Pointer to the thread control block
 */
void tlSortIn(TList* list, ThreadCB* dat)
{
    int node_enqueued = 0;              // flag for new node if enqueued or not

    /* check if list is empty */
    if (list->numNodes == 0)
        tlEnqueue(list,dat);            // enqueue node on empty list
    else {
        TNode *node = newTNode();       // create new node
        
        node->data  = dat;              // ptr to data
        tlSetPtrFirst(list);            // set iter ptr to the firs node

        if (dat->readyTime <= list->iter->data->readyTime) {
            /* enqueue node as first node */
            node->next = list->head->next;
            list->head->next = node;
            list->numNodes += 1;
        } else {
            while (list->iter != NULL) {
                if (list->iter->next != NULL) {
                    if (dat->readyTime <= list->iter->next->data->readyTime) {
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
                tlEnqueue(list,dat);
        }
    }
}

//******************************************************************************
/**
 * tlReadFirst() - Return pointer to the first thread
 * @list        Pointer to the list
 */
ThreadCB* tlReadFirst(TList *list)
{
    if (list->head->next != NULL)
        return list->head->next->data;  // ptr to the first node
    else
        return list->head->data;        // ptr to the dummy node
}

//******************************************************************************
/**
 * tlGetNumNodes() - Return number of elements in list
 * @list:       Pointer to the list
 */
unsigned tlGetNumNodes(TList *list)
{
    return list->numNodes;              // number of elements in the list
}

//******************************************************************************
/**
 * tlSetPtrFirst() - Set iteration pointer to first element
 * @list:       Pointer to the list
 */
void tlSetPtrFirst(TList *list)
{
    list->iter  = list->head->next;     // set ptr to the first (not dummy) node
}

//******************************************************************************
/**
 * tlSetPtrNext() - Move itaration ptr to next element
 * @list:       Pointer to the list
 */
void tlSetPtrNext(TList *list)
{
    if (list->iter != NULL)
        list->iter = list->iter->next;  // set ptr only if != 0
}

//******************************************************************************
/**
 * tlReadCurrent() - Return thread data via iter pointer
 * @list:       Pointer to the list
 */
ThreadCB* tlReadCurrent(TList *list)
{
    if (list->iter != NULL)
        return list->iter->data;    // return data ptr
    else
        return NULL;
}

