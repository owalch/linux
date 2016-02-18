/**
 * @file    mythread.c
 * @brief   Implementation file for MyThread package
 *
 * This file contains the whole thread implementation.
 *
 *
 * @author  J. Zeman
 * @author  M. Thaler
 * @author  O. Walch
 *
 * @date    2012-04-17
 * @version 1.0
 */
#include <stdlib.h>
#include <stdio.h>
#include "mythread.h" 

//******************************************************************************

long currentTID = 0;                            // global threadID counter

//******************************************************************************
// Method:	mythread_t::mythread_t
// Purpose:	constructor of class mythread_t

/**
 * @fn      ThreadCB* mtNewThread(TMethod method, void* arg, TPriority prio, unsigned stacksize)
 * @brief   Create new thread
 * @param   method TMethod method belongs to the thread
 * @param   arg void pointer to the argument given to the method
 * @param   prio TPriority value of the thread
 * @param   stacksize unsigned stack size value
 * @return  pointer to the created thread
 *
 * This function creates a new thread and initializes its agruments.
 */
ThreadCB* mtNewThread(TMethod method, void* arg, TPriority prio, 
                                                            unsigned stacksize)
{
    ThreadCB* tcb     = (ThreadCB*)malloc(sizeof(ThreadCB));
    tcb->tID          = currentTID++;
    tcb->tPrio        = prio;
    tcb->readyTime    = 0;

    tcb->startMethod  = method;
    tcb->arg          = arg;

    if (stacksize < MIN_STACK_SIZE) {
        stacksize = MIN_STACK_SIZE;
        printf("setting stack size to %d\n", MIN_STACK_SIZE);
    }

    tcb->stack        = (unsigned long)malloc(stacksize);
    tcb->stackpointer = tcb->stack + stacksize - 32;

    tcb->firstCall    = 1;

    return tcb;
};

/******************************************************************************/
/**
 * @fn      void mtDelThread(ThreadCB *tcb)
 * @brief   Function to remove a thread
 * @param   tcb ThreadCB pointer to the thread
 *
 * This function removes a thread an cleans up the allocated memory
 */
void mtDelThread(ThreadCB* tcb)
{
    free((void*)(tcb->stack));
    free(tcb);
}

/******************************************************************************/
/**
 * @fn      long mtGetFreeStackSize(ThreadCB* tcb)
 * @brief   Function returns the free stack size
 * @param   tcb ThreadCB pointer to the thread
 * @return  long number of free stack size in bytes
 */
long mtGetFreeStackSize(ThreadCB* tcb) {
    long retval;
    if (tcb->stackpointer > tcb->stack)
        retval = (long)(tcb->stackpointer - tcb->stack);
    else
        retval = -1;
    return retval;
}

/******************************************************************************/
/**
 * @fn      void mtPrintTCB(ThreadCB* tcb)
 * @brief   Print thread control block information
 * @param   tcb ThreadCB pointer to the thread
 */
void mtPrintTCB(ThreadCB* tcb) { 
    printf("tid: %d, prio: %d, ready time: %u, ", tcb->tID, tcb->tPrio,
                                                  tcb->readyTime);
    printf("sp: %lu, free stack %ld\n", tcb->stack, mtGetFreeStackSize(tcb));

}

/******************************************************************************/

void mtSetID(ThreadCB* tcb, unsigned tid) {
    tcb->tID = tid;
}

unsigned mtGetID(ThreadCB* tcb) {
    return(tcb->tID);
}

/******************************************************************************/

void mtSetPrio(ThreadCB* tcb, TPriority prio) {
    tcb->tPrio = prio;
}

TPriority mtGetPrio(ThreadCB* tcb) {
    return(tcb->tPrio);
}

/******************************************************************************/

void mtSetReadyTime(ThreadCB* tcb, unsigned rTime) {
    tcb->readyTime = rTime;
}

unsigned mtGetReadyTime(ThreadCB* tcb) {
	return(tcb->readyTime);			// get ready time (clock ticks)
}

/******************************************************************************/

unsigned mtGetSP(ThreadCB* tcb) {
    return tcb->stackpointer;
}

void mtSaveSP(ThreadCB* tcb, unsigned long sp) {
    tcb->stackpointer = sp;
}

/******************************************************************************/

TMethod mtGetStartMethod(ThreadCB* tcb) {
    return tcb->startMethod;
}


void* mtGetArgPointer(ThreadCB* tcb) {
    return tcb->arg;
}

/******************************************************************************/

int mtIsFirstCall(ThreadCB* tcb) {
    return tcb->firstCall;
}

void mtClearFirstCall(ThreadCB* tcb) {
    tcb->firstCall = 0;
}
/******************************************************************************/

