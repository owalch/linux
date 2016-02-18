/******************************************************************************* 
*   Programm test2 fuer Prakt1b: Listen- und Queue-Objekt
*   Fach BS, Jan Zeman, Okt.99
*   M. Thaler, Feb. 2011 changed to C version
*   File: test2.c
*******************************************************************************/

#include "mylist.h"
#include "mythread.h"
#include <stdio.h>

// prototypes of local functions

void beginTest(void);
void endTest(void);
void printList(TList* list, const char* str);
void printFirst(TList* list, const char* str);

//******************************************************************************

int main(void){

    unsigned tid = 0, i;
    ThreadCB* th;
    TList* queue1 = tlNewList();
    TList* queue2 = tlNewList();
    TList* prioliste1 = tlNewList();
    TList* prioliste2 = tlNewList();
 
    // show empty queues -------------------------------------------------------
    beginTest(); 
    printList(queue1, "queue1 -> empty");
    printList(queue2, "queue2 -> empty");
    printList(prioliste1, "prioliste1 -> empty");
    printList(prioliste2, "prioliste2 -> empty");
    endTest();

    // add one thread to queue 2 -----------------------------------------------
    beginTest();
    th = mtNewThread(tid++, 1, 40);
    tlEnqueue(queue2, th);
    printList(queue2, "queue2, after one put");


    // put last 5 threads ------------------------------------------------------
    tlEnqueue(queue2, mtNewThread(tid++,1,20));
    tlEnqueue(queue2, mtNewThread(tid++,1,30));
    tlEnqueue(queue2, mtNewThread(tid++,2,35));
    tlEnqueue(queue2, mtNewThread(tid++,3,50));
    tlEnqueue(queue2, mtNewThread(tid++,3,10));

    printFirst(queue2, "queue2 after 6 puts");

    printList(queue2, "queue2 after 6 puts");
    endTest();

    // move threads between queues ---------------------------------------------
    beginTest();
    printList(prioliste1, "prioliste1 -> empty");
    tlSortIn(prioliste1, mtNewThread(tid++, 4,1000));
    tlSortIn(prioliste1, mtNewThread(tid++, 4, 999));

    for (i = 1; i <= 6; i++) {
        printFirst(queue2, "--->> queue2, for-loop before pop");
        th = tlDequeue(queue2);
        if (th == NULL)
            printf("\t th == NULL at iteration i = %d", i);
        else {
            printList(queue2, "queue2, for-loop after pop");
            tlEnqueue(queue1, th);        // in andere Queue einreihen
            tlSortIn(prioliste1, th);    // in die sort.Liste einreihen
            printList(prioliste1, "prioliste1, for-loop");
        }
    }
    
    printList(queue2,     "queue2,     after 1. for loop");
    printList(prioliste1, "prioliste1, after 1. for loop");
    printList(queue1,     "queue1,     after 1. for loop");
 
    endTest();   

    //  add a lot of threds to queue 1 then pop 590 threads
    beginTest();
    for (i = 1; i < 200; i++) {
        tlSortIn(prioliste1, mtNewThread(tid++, 5, 500+2*i));
    }
    for (i = 1; i < 200; i++) {
        tlSortIn(prioliste1, mtNewThread(tid++, 6, 401+2*i));
    }
    for (i = 1; i < 200; i++) {
        tlSortIn(prioliste1, mtNewThread(tid++, 7, 600+2*i));
    }
    for (i=1; i<590; i++) {
        th = tlDequeue(prioliste1);
        mtDelThread(th);
    }
    printList(prioliste1, "prioliste1, after 600 SortIns and 590 pops");
    getchar();
    printList(queue1, "queue1 before end");
    getchar();                        // just to wait here
    printList(queue2, "queue2 before end");
    getchar();
    printList(prioliste2, "prioliste2, before end");
    getchar();                        // just to wait here

    tlDelList(queue1);  
    tlDelList(queue2);
    tlDelList(prioliste1);
    tlDelList(prioliste2);

}

//******************************************************************************

void beginTest(void) {
    printf("---------------------------------------------------------------\n");
}

void endTest(void){
    printf("---------------------------------------------------------------\n");
    //printf("\ntype CR ");
    //getchar(); 
}

void printList(TList* list, const char* str) {
    ThreadCB* p;
    printf("-> printing  %s, total %d elements\n", str, tlGetNumNodes(list));
    tlSetPtrFirst(list);
    while((p = tlReadCurrent(list)) != NULL) {
        printf(" > node tid = %d, prio = %d, ready time = %d\n",
                p->tID, p->tPrio, p->readyTime);
        tlSetPtrNext(list);
    }
}


void printFirst(TList* list, const char *string) {
  ThreadCB* th;
  th = tlReadFirst(list);

  printf("-> printing first element of list %s\n", string);
  if (th != NULL)
    printf(" > node tid=%d, prio=%d, ready time=%d\n",
            mtGetID(th), mtGetPrio(th), mtGetReadyTime(th) );
  else
    printf("   list is empty  !!!!");
  printf("\n");
}

//******************************************************************************

