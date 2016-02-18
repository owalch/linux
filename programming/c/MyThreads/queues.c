/**
 * @file    queues.c
 * @brief   Implementation file for wait and ready Queues
 *
 * This file contains the queue handling as well as the list instantiation.
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
#include <sys/types.h>
#include <sys/times.h>
#include <unistd.h>
#include <stdio.h>

#include "mylist.h"
#include "mythread.h"
#include "queues.h"

/******************************************************************************/
// local function prototypes
/******************************************************************************/
unsigned getTime(void);


/******************************************************************************/
// Static data of queueing system
/******************************************************************************/
unsigned    queueState = 0;                     // state of queue
time_t      sTimeS;                             // start time seconds
suseconds_t sTimeU;                             // start time microseconds

TList*      readyQueue[READY_QUEUES];           // the ready queue
TList*      waitQueue;                          // the wait queue


/******************************************************************************/
// Queueing functions
/******************************************************************************/
/**
 * @fn      void initQueues(void)
 * @brief   Initialize the queueing system
 *
 * This function initializes the ready queues as well as a wait queu. Each \n
 * queu contains a blank list at startup.
 */
void initQueues(void) {
    int i;
    struct timeval tv;
    if (queueState == 0) {                      // start only if no queue is up
        queueState = 1;
        for (i = 0; i < READY_QUEUES; i++) {
            readyQueue[i] = tlNewList();        // create new ready queues
        }
        waitQueue = tlNewList();                // create new wait queue

        gettimeofday(&tv, NULL);
        sTimeS = tv.tv_sec;
        sTimeU = tv.tv_usec;   
    }
}

/******************************************************************************/
/**
 * @fn      void delQueues(void)
 * @brief   Clean up dynamically allocated data and remove the queues
 *
 * This function will be called by scheduler before termination to remove all \n
 * allocated queues. 
 */
void delQueues(void) {
    int i;

    for (i=0; i<READY_QUEUES; i++) {
        tlDelList(readyQueue[i]);               // clean and remove queue
        printf("\n*** cleaning readyQueue %d ***\n", i);
    }
    tlDelList(waitQueue);
    printf("\n*** cleaning waitQueue ***\n");

    queueState = 0;                             // reset start flag
}

/******************************************************************************/
/**
 * @fn      ThreadCB* getNextThread(void)
 * @brief   Returns thread with highest priority in the ready queues
 * @return  A ThreadCB pointer to the thread or NULL
 *
 * This function returns the thread with the highes priority in the ready \n
 * queue. If there is a thread in the wait queue, ready to run, the thread \n
 * will be enquede in the ready queue.
 *
 */
ThreadCB* getNextThread(void) {
    ThreadCB* tcb = NULL;
    int i = 0;
    int time = getTime();

    tlSetPtrFirst(waitQueue);                   // set iter ptr to first element
    tcb = tlReadCurrent(waitQueue);             // read current node

    while (tcb != NULL) {
        if (tcb->readyTime <= time) {           // check ready Time
            tcb->tPrio = P_HIGH;                // set priority to high
            addToReadyQueue(tcb);               // enquede if ready
            tlDequeue(waitQueue);               // deque thread in wait queue
            fprintf(stdout, "DEGUB: Thread dequed from waitQueue\n");
        }
        tlSetPtrNext(waitQueue);                // set ptr to the next thread
        tcb = tlReadCurrent(waitQueue);
    }

    for (i=0; i<READY_QUEUES;i++) {             // start with dequing high prio
        tcb = tlDequeue(readyQueue[i]);
        if (tcb != NULL) {
            fprintf(stdout, "DEUBG: Thread deque from readQueue\n");
            break;                              // got new thread
        }
    }
    return tcb;                                 // return thread
}

/******************************************************************************/
/**
 * @fn      void addToReadyQueue(ThreadCB *tcb)
 * @brief   Append a thread to the end of the read queue
 * @param       tcb Pointer to a thread control block
 *
 * This function appends a thread to the end of the ready queue. The prio \n
 * attribute gets checked to get the right queue. Each thread gets a \n
 * timestamp when first going into ready queue.
 *
 */
void addToReadyQueue(ThreadCB *tcb) {

    tcb->readyTime = getTime();                 // timestamp new thread

    switch (tcb->tPrio) {
        case HIGH:
            tlEnqueue(readyQueue[P_HIGH], tcb);
            break;
            
        case MEDIUM:                            // medium prio
            tlEnqueue(readyQueue[P_MED], tcb);
            break;

        case LOW:                               // low prio
            tlEnqueue(readyQueue[P_LOW], tcb);
            break;

        default:                                // error handling
            fprintf(stdout, "new Thread must have a prio\n");
            fprintf(stdout, "Thread added to low prio queue\n");
            tlEnqueue(readyQueue[P_LOW], tcb);
            break;
    }
}

/******************************************************************************/
/**
 * @fn      void addToWaitQueue(ThreadCB* tcb, int sleepTime)
 * @brief   Sort a thread into the wait queue
 * @param   tcb Pointer to a thread control block
 * @param   sleepTime Time to sleep in milliseconds
 *
 * This function sorts a thread into the wait queue according to the sleep \n
 * time.
 */
void addToWaitQueue(ThreadCB* tcb, int sleepTime) {
    int time;

    time = getTime();

    tcb->readyTime = time + sleepTime;
    tlSortIn(waitQueue, tcb);
}   

/******************************************************************************/
/**
 * @fn      unsigned CheckWaitQueue(void)
 * @brief   Return the number of threads in the wait queue
 * @return  a unsigned number of threads in the wait queue
 *
 * This function returns the number of threads in the wait queue.
 */
unsigned checkWaitQueue(void) {
    int numNodes;
    
    numNodes = tlGetNumNodes(waitQueue);
    return numNodes;
}

/******************************************************************************/
/**
 * @fn      void printWaitQueue(void)
 * @brief   Print a list with threads in the wait queue
 *
 * This function prints a list with all threads in the wait queue and some \n
 * thread specific information.
 */
void printWaitQueue(void) {
    int i = 0;
    ThreadCB* tcb = NULL;
    
    tlSetPtrFirst(waitQueue);                   // set iter ptr to first element
    tcb = tlReadCurrent(waitQueue);             // read current node
    fprintf(stdout, "%d Nodes(s) in the waitQueue\n",
            (tcb == NULL ? 0 : checkWaitQueue()));

    while (tcb != NULL) {
        mtPrintTCB(tcb);       
        tlSetPtrNext(waitQueue);
        tcb = tlReadCurrent(waitQueue);
        i++;                                    // increment tmp node counter
    }
}

/******************************************************************************/
/**
 * @fn      unsigned checkReadyQueue(int prio)
 * @brief   Get the number of threads in the ready queue
 * @param   prio int index to the ready queue
 * @return  unsigned number of threads in the ready queue
 *
 * This function prints the number of threads in the ready queue. Prio is the \n
 * the ready queue index.
 */
unsigned checkReadyQueue(int prio) {
    int numNodes;

    numNodes = tlGetNumNodes(readyQueue[prio]);
    return numNodes;
}

/******************************************************************************/
/**
 * @fn      void printReadyQueueStatus(void)
 * @brief   Print status information about the ready queues
 *
 * This function prints the number of threads in the ready queues as well as \n
 * some status information.
 */
void printReadyQueueStatus(void) {
    int nodeIdx;
    int prio;
    ThreadCB* tcb = NULL;

    for(prio=0; prio<3; prio++) {
        nodeIdx = 0;
        tlSetPtrFirst(readyQueue[prio]);        // set iter ptr to first element
        tcb = tlReadCurrent(readyQueue[prio]);  // read current node
        fprintf(stdout, "%d Nodes(s) in the readQueue %d\n",
                (tcb == NULL ? 0 : checkReadyQueue(prio)), prio);

        while (tcb != NULL) {
            mtPrintTCB(tcb);
            tlSetPtrNext(readyQueue[prio]);
            tcb = tlReadCurrent(readyQueue[prio]);
            nodeIdx++;                          // increment tmp node counter
        }
        fprintf(stdout, "\n");
    }
}

/******************************************************************************/
/**
 * @fn      unsigned getTime(void)
 * @brief   Get wall clock time in 1ms resolution
 * @return  unsigned clock time in 1ms resolution
 *
 * This function returns the wall clock time in 1ms resolution to get \n
 * timestamps for the threads.
 */
unsigned getTime(void) {
    unsigned time;
    struct timeval tv;
    gettimeofday(&tv,NULL);
//     time = (unsigned)((tv.tv_sec  - sTimeS)*1000 + (tv.tv_usec - sTimeU)/1000);
    time = (unsigned)(tv.tv_sec*1000 + tv.tv_usec);

    return time;
}

/******************************************************************************/

