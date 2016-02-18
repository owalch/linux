#ifndef MYTHREAD_HEADER
#define MYTHREAD_HEADER

//******************************************************************************
// Header file for MyThread package
//
// Operating Systems, J. Zeman, Okt. 99
// File: mythread.h
//
// Modifications:   M. Thaler Sept. 2003
//                  - priority names changed
//                  - thread metcbod type
//                  - priority type
//                  - english comments
//                  M. theler Jun. 2007
//                  - mythread_start: scheduling parameter
//                  M. theler Feb. 2011
//                  - converted to C (from C++)
//                  - naming changed
//******************************************************************************

#define MIN_STACK_SIZE 4*4096

//******************************************************************************
// Type definitions
//------------------------------------------------------------------------------
// Thread priorities

typedef enum TPriority { HIGH, MEDIUM, LOW } TPriority;

// Type for: void* function(void *)

typedef void (*TMethod)(void *);

//------------------------------------------------------------------------------
// Thread control block

typedef struct ThreadCB {
    unsigned      tID;              // thread-ID
    unsigned      tPrio;            // thread priority
    unsigned      readyTime;        // time, when a a waiting thread
                                    // can be activated, in clock ticks

    TMethod       startMethod;      // pointer to the user thread metcbod
    void          *arg;             // poniter to the argument of the metcbod

    unsigned long stackpointer;     // current stackpointer of the thread
    unsigned long stack;            // bottom of stack

    int          firstCall;         // thread runs for the first time
} ThreadCB;

//******************************************************************************
// function prototypes 

    ThreadCB* mtNewThread(unsigned id, unsigned prio, unsigned readyTime);

    void      mtDelThread(ThreadCB* tcb);

//------------------------------------------------------------------------------
// single variable access functions

    void      mtSetID(ThreadCB* tcb, unsigned tid);
    unsigned  mtGetID(ThreadCB* tcb);
    void      mtSetPrio(ThreadCB* tcb, TPriority prio);
    unsigned  mtGetPrio(ThreadCB* tcb);
    void      mtSetReadyTime(ThreadCB* tcb, unsigned rtime);    
    unsigned  mtGetReadyTime(ThreadCB* tcb);
    
//******************************************************************************

#endif // MYTHREAD_HEADER
