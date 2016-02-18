/******************************************************************************* 
*   Program:    test1 for Intro (single linked list)
*   Course:     BSy, Jan Zeman, Okt.99
*               M. Thaler
*                   Feb. 2011 changed to C version
*                   Jul. 2011 -> unit test using assert
*   File:       test1.c
*******************************************************************************/

#include "mylist.h"
#include "mythread.h"
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <time.h>

// prototype of local functions

void beginTest(const char *str);
void endTest(void);

void shuffleIntArray(int *ar, int size);

//******************************************************************************

int main(void){

    ThreadCB* th;
    unsigned tid, j, count, utmp;

    TList* queue1 = tlNewList();

    // new, empty list ---------------------------------------------------------

    beginTest("check: empty queue and intializiation");

    assert(queue1                != NULL);      // queue exists
    assert(tlGetNumNodes(queue1) == 0);         // queue is empty
    assert(queue1->head == queue1->tail);       // head == tail
    assert(queue1->iter == NULL);               // iter == NULL
    assert(tlReadFirst(queue1)   == NULL);      // no entries
    assert(tlReadCurrent(queue1) == NULL);      // current initialized

    tlSetPtrNext(queue1);
    assert(tlReadCurrent(queue1) == NULL);      // cannot forward iter on empty
                                                // list

    endTest();

    // add four threads --------------------------------------------------------

    beginTest("check: adding threads and list consistency");

    count = 4;
    tid   = 0;
    for (j = 0; j < count; j++) {
          th = mtNewThread(tid++, 1, 10);
          tlEnqueue(queue1, th);
    }

    assert(queue1                != NULL);      // queue exists
    assert(tlGetNumNodes(queue1) == count);     // queue is not empty
    assert(queue1->head != queue1->tail);       // head == tail
    assert(tlReadFirst(queue1)   != NULL);      // no entries
    assert(queue1->head->data == NULL);         // NULL data entry @ head

    assert(tlReadCurrent(queue1) == NULL);      // current empty
    tlSetPtrFirst(queue1);
    assert(tlReadCurrent(queue1) != NULL);      // current initialized

    for (j = 0; j < count; j++) {               // check for list consistency
        th = tlReadCurrent(queue1);
        assert(th->tID == j);                   // list in correct order
        if (j == count - 1)
            assert(queue1->iter == queue1->tail);
        tlSetPtrNext(queue1);
    }
    assert(tlReadCurrent(queue1) == NULL);      // end of list

    endTest();

    // dequeue 2, then all threads  --------------------------------------------

    beginTest("check: dequeing and empty list");

    th = tlDequeue(queue1);
    mtDelThread(th);

    th = tlDequeue(queue1);
    assert(th->tID == 1);                       // threads 0 and 1 dequeued
    mtDelThread(th);
    

    while ((th = tlDequeue(queue1)) != NULL) {mtDelThread(th);}

    assert(tlGetNumNodes(queue1) == 0);         // queue is empty

    tlSetPtrFirst(queue1);                      // empty list
    th = tlReadCurrent(queue1);
    assert(th == NULL);

    tlSetPtrNext(queue1);
    assert(tlReadCurrent(queue1) == NULL);      // cannot iterate empty list

    assert(queue1->head->data == NULL);         // NULL data entry @ head

    endTest();

    // dequeue from empty queue ------------------------------------------------

    beginTest("check: dequeue from empty list");
    assert(tlDequeue(queue1) == NULL);
    endTest();


    // enqueue sorted to empyt list --------------------------------------------
    
    beginTest("check: enqueue sorted into empty list");

    assert(tlGetNumNodes(queue1) == 0);         // queue is empty 
    tlSetPtrFirst(queue1);
    assert(tlReadCurrent(queue1) == NULL);

    tid = 0;
    th = mtNewThread(tid++, 1, 10);
    tlSortIn(queue1, th);

    assert(tlGetNumNodes(queue1) == 1);         // queue is not empty
    tlSetPtrFirst(queue1);
    assert(tlReadCurrent(queue1) != NULL);      

    th = mtNewThread(tid++, 1, 20);             // add at end
    tlSortIn(queue1, th);
    assert(tlGetNumNodes(queue1) == 2);         // queue is not empty

    tlSetPtrFirst(queue1);                      // path from head -> tail
    tlSetPtrNext(queue1);
    assert(queue1->iter == queue1->tail);
    tlSetPtrNext(queue1);
    assert(tlReadCurrent(queue1) == NULL);

    th = mtNewThread(tid++, 1, 5);              // add as first  
    tlSortIn(queue1, th);
    assert(tlGetNumNodes(queue1) == 3);         // queue is not empty
    th = mtNewThread(tid++, 1, 15);             // add as first  
    tlSortIn(queue1, th);
    assert(tlGetNumNodes(queue1) == 4);         // queue is not empty
    

    tlSetPtrFirst(queue1);                      // path from head -> tail
    tlSetPtrNext(queue1);
    tlSetPtrNext(queue1);
    tlSetPtrNext(queue1);
    assert(queue1->iter == queue1->tail);
    tlSetPtrNext(queue1);
    assert(tlReadCurrent(queue1) == NULL);

    th = mtNewThread(tid++, 1, 25);             // add at end
    tlSortIn(queue1, th);

    tlSetPtrFirst(queue1);                      // check sort order 
    count = 5;
    utmp  = 5;
    for (j = 0; j < count; j++) {
        th = tlReadCurrent(queue1);
        assert(mtGetReadyTime(th) == utmp);
        utmp += 5;
        tlSetPtrNext(queue1);
    }
    assert(tlReadCurrent(queue1) == NULL);
    assert(tlGetNumNodes(queue1) == count);     // number of entries

    endTest();

    // dequeue first -----------------------------------------------------------

    beginTest("check: dequeue");

    th = tlDequeue(queue1);
    mtDelThread(th);

    count--;
    assert(tlGetNumNodes(queue1) == count);     // number of entries

    tlSetPtrFirst(queue1);                      // path from head -> tail
    tlSetPtrNext(queue1);
    tlSetPtrNext(queue1);
    tlSetPtrNext(queue1);
    assert(queue1->iter == queue1->tail);
    tlSetPtrNext(queue1);
    assert(tlReadCurrent(queue1) == NULL);

    endTest();

    // dequeue next thread and add threads sorted ------------------------------

    beginTest("check: add sorted and enque");
    th = tlDequeue(queue1);
    mtDelThread(th);
    count--;

    tlSortIn(queue1,  mtNewThread(tid++, 1,  3));   count++;
    tlSortIn(queue1,  mtNewThread(tid++, 1, 70));   count++;
    tlSortIn(queue1,  mtNewThread(tid++, 1, 21));   count++;
    tlEnqueue(queue1, mtNewThread(tid++, 1, 80));   count++;

    assert(tlGetNumNodes(queue1) == count);     // number of entries

    tlSetPtrFirst(queue1);                      // path from head -> tail
    for (j = 0; j < count-1; j++)
        tlSetPtrNext(queue1);
    assert(queue1->iter == queue1->tail);
    tlSetPtrNext(queue1);
    assert(tlReadCurrent(queue1) == NULL);

    tlSetPtrFirst(queue1);                      // check sort order
    th = tlReadCurrent(queue1);
    utmp = mtGetReadyTime(th);
    tlSetPtrNext(queue1);
    for (j = 1; j < count; j++) {
        th = tlReadCurrent(queue1);
        assert(mtGetReadyTime(th) >= utmp);
        utmp = mtGetReadyTime(th);
        tlSetPtrNext(queue1);
    }

    endTest();

    // check a large list ------------------------------------------------------

    int rt, cnt   = 1000;
    int *iar      = (int *)malloc(cnt*sizeof(int));
    TList* queue2 = tlNewList();

    for (j = 0; j < cnt; j++)
        iar[j] = j+1;
    shuffleIntArray(&iar[0], cnt);
    for (j = 0; j < cnt; j++) {
        tlSortIn(queue2,  mtNewThread(j+1, 1,  iar[j])); 
    }

    tlSetPtrFirst(queue2);
    for (j = 1; j <= cnt; j++) {
        th = tlReadCurrent(queue2);
        rt = mtGetReadyTime(th);
        assert( rt == j);
        tlSetPtrNext(queue2);
    }
    free(iar);
    tlDelList(queue2);
    
    // now dequeue all threads -------------------------------------------------

    beginTest("check: empty whole list");

    for (j = 0; j < count; j++) {
        th = tlDequeue(queue1);
        mtDelThread(th);
    }
    assert(tlGetNumNodes(queue1) == 0);         // no entries
    assert(queue1->head->data == NULL);         // NULL data entry @ head
    assert(queue1->head == queue1->tail);       // head == tail

    tlSetPtrFirst(queue1); 
    tlSetPtrNext(queue1);
    assert(tlReadCurrent(queue1) == NULL);
 

    tlDelList(queue1);                          // cleanup queue

    endTest();

}


//******************************************************************************

void beginTest(const char *str) {
    printf("\n*************************************************************\n");
    if (str != NULL)
        printf("%s\n", str);
}


void endTest(void){
    printf("\n");
}

//******************************************************************************

void shuffleIntArray(int *ar, int size) {
    int j, k, tmp;
    double dran;
    srand((unsigned int)time(NULL));
    // shuffle according to Knuth to avoid sorted lists
    for (j = size-1; j >= 0; j--) {
        dran = (double)rand() / (double)(RAND_MAX);
        k = (int)(j*dran);
        tmp   = ar[j];
        ar[j] = ar[k];
        ar[k] = tmp;
    }
}

//******************************************************************************

