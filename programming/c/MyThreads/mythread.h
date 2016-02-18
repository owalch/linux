/**
 * @file    mythread.h
 * @brief   Header file for MyThread package
 *
 * This file contains the public thread information.
 * Scheduling can be chosen to be FIFO (cooperative) or PREEMPT (preemptive)
 * scheduling interval can be set >= 100us (default 1ms)
 * sleep function in wall clock time at resolution of 1ms
 * 
 * @author  J. Zeman
 * @author  M. Thaler
 * @author  O. Walch
 * 
 * 
 * @date    2012-04-17
 * @version 1.0
 */
#ifndef MYTHREAD_HEADER
#define MYTHREAD_HEADER

/******************************************************************************/
// defines
/******************************************************************************/
/* MyThread                   thread typ
 * myThreadStart()            start threading: PREEMPT, scheduling interval 1ms
 * myThreadStartInterval(x)   start threading: PREEMPT, set scheduling interval
 * myThreadStartFIFO()        start threading: FIFO
 *   
 * myThreadYield()            yield thread
 * myThreadExit()             terminate thread
 * myThreadSleep(x)           sleep x ms
 * myThreadCreate(t, f,a,p,s) create a new thread and appends it to ready queue
 *                            t: thread handle, f: function, a: argument,
 *                            p: prio s: stack size
 */
#define MyThread                    ThreadCB
#define myThreadStart()             taskSwitch(INIT)
#define myThreadStartInterval(x)    initScheduler(PREEMPT, x); taskSwitch(INIT)
#define myThreadStartFIFO()         initScheduler(FIFO, 0);    taskSwitch(INIT)
#define myThreadCreate(t,f,a,p,s)   t = mtNewThread(f,a,p,s); \
                                    initQueues(); \
                                    addToReadyQueue(t)
#define myThreadYield()             taskSwitch(YIELD)
#define myThreadExit()              taskSwitch(ZOMBIE)
#define myThreadSleep(x)            taskSwitch(x)

#define MIN_STACK_SIZE              4096

/******************************************************************************/
// Type definitions
/******************************************************************************/
// Thread priorities
typedef enum TPriority { HIGH, MEDIUM, LOW } TPriority;

// Type for: void* function(void *)
typedef void (*TMethod)(void *);

/******************************************************************************/
// Thread control block
/******************************************************************************/
typedef struct ThreadCB {
    unsigned      tID;              // thread-ID
    TPriority     tPrio;            // thread priority
    unsigned      readyTime;        // time, when a a waiting tcbread
                                    // can be activated, in clock ticks

    TMethod       startMethod;      // pointer to the user thread metuod
    void          *arg;             // poniter to the argument of the method

    unsigned long stackpointer;     // current stackpointer of the thread
    unsigned long stack;            // bottom of stack

    int          firstCall;         // thread runs for the first time
} ThreadCB;

/******************************************************************************/
// function prototypes
/******************************************************************************/
ThreadCB* mtNewThread(TMethod method, void* arg, TPriority prio, unsigned stacksize);
void      mtDelThread(ThreadCB* tcb);
long      mtGetFreeStackSize(ThreadCB* tcb);
void      mtPrintTCB(ThreadCB* tcb);


/******************************************************************************/
// "single variable access" functions
/******************************************************************************/
void      mtSetID(ThreadCB* tcb, unsigned tid);
unsigned  mtGetID(ThreadCB* tcb);
void      mtSetPrio(ThreadCB* tcb, TPriority prio);
TPriority mtGetPrio(ThreadCB* tcb);
void      mtSetReadyTime(ThreadCB* tcb, unsigned rtime);
unsigned  mtGetReadyTime(ThreadCB* tcb);

TMethod   mtGetStartMethod(ThreadCB* tcb);
void*     mtGetArgPointer(ThreadCB* tcb);

void      mtSaveSP(ThreadCB* tcb, unsigned long sp);
unsigned  mtGetSP(ThreadCB* tcb);

int       mtIsFirstCall(ThreadCB* tcb);
void      mtClearFirstCall(ThreadCB* tcb);

/*
//macros to substitute single variavle functions -> inline -> faster

    #define   mtSetID(x,y)          x->tID = y
    #define   mtGetID(x)            x->tID;
    #define   mtSetPrio(x,y)        x->tPrio = y
    #define   mtGetPrio(x)          x->tPrio
    #define   mtSetReadyTime(x,y)   x->readyTime = y
    #define   mtGetReadyTime(x)     x->readyTime
    #define   mtGetStartMethod(x)   x->startMethod
    #define   mtGetArgPointer(x)    x->arg
    #define   mtSaveSP(x,y)         x->stackpointer = y
    #define   mtGetSP(x)            x->stackpointer
    #define   mtIsFirstCall(x)      x->firstCall
    #define   mtClearFirstCall(x)   x->firstCall = false

*/
    
//******************************************************************************

#endif // MYTHREAD_HEADER
