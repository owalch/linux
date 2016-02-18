//******************************************************************************
// Implementation file for MyThread package
//
// Operating Systems, J. Zeman, Okt. 99
// File: mythread.h
//
// Modifications:   M. Thaler Sept. 2003
//                  - priority names changed
//                  - thread method type
//                  - priority type
//                  - english comments
//                  M. Thaler Jun. 2007
//                  - mythread_start: scheduling parameter
//                  M. Thaler Feb. 2011
//                  - converted to C (from C++)
//                  - naming changed
//******************************************************************************

#include <stdlib.h>
#include <stdio.h>
#include "mythread.h" 

//******************************************************************************
// Method:	mtNewThread
// Purpose:	set up data structure for new thread

ThreadCB* mtNewThread(unsigned id, unsigned prio, unsigned readyTime)
{
    ThreadCB* tcb     = (ThreadCB*)malloc(sizeof(ThreadCB));
    tcb->tID          = id;
    tcb->tPrio        = prio;
    tcb->readyTime    = readyTime;
    tcb->stack        = (unsigned long)malloc(8);

}

//******************************************************************************
// clean up thread

void mtDelThread(ThreadCB* tcb)
{
    free((void*)(tcb->stack));
    free(tcb);
}

//******************************************************************************

void mtSetID(ThreadCB* tcb, unsigned tid) {
	tcb->tID = tid;
}

unsigned mtGetID(ThreadCB* tcb) {
	return(tcb->tID);
}

//******************************************************************************

void mtSetPrio(ThreadCB* tcb, TPriority prio) {
	tcb->tPrio = prio;
}

unsigned mtGetPrio(ThreadCB* tcb) {
	return(tcb->tPrio);
}

//******************************************************************************

void mtSetReadyTime(ThreadCB* tcb, unsigned rTime) {
	tcb->readyTime = rTime;
}
	
unsigned mtGetReadyTime(ThreadCB* tcb) {
	return(tcb->readyTime);			// get ready time (clock ticks)
}

//******************************************************************************

