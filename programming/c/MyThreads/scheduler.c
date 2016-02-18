//******************************************************************************
// Implementation file for class scheduler
// Working implementation of the thread scheduler 
//
// Operating Systems, J. Zeman, Okt. 99
// File: scheduler.c
//
// Modifications:   M. Thaler Sept. 2003
//                  - scheduler and queues class
//                  - method names
//                  - scheduler returns (not exit) on CTRL-C & empty ready queue
//                  - scheduler: singleton
//                  - english comments
//                  M. Thaler May 2007
//                  - changed how to start or restart threads 
//                  - the assembly language calls     
//                      SAVE_REGS();
//                      SAVE_SP(scheduSP);
//                      RESTORE_SP(threadSP);    
//                      must be within the if-statement, otherwise newer GNU-
//                      compiler will arrange instructions such that there
//                      will be segmenatation faults
//                  M. Thaler Jun. 2007
//                  - preemptive
//                  M. Thaler Jan. 2011
//                  - made compatible for 64-Bit CPUs (assmbler macros)
//                  - unsigned long for stack pointer storage (unsigned before)
//                  M. Thaler Feb, 2011
//                  - converted to pure C
//****************************************************************************** 

#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

#include "scheduler.h"
#include "mythread.h"
#include "queues.h"

#define DEBUG_OUTPUT    0

//******************************************************************************
// Method:  signalhandlers
// Purpose: - catch CTRL-C and sets the shutdown to true, to allow
//            the scheduler to shut down at a save location
//          - catch SIGVTALRM -> preempt currenr thread    
// Parameter: dummy


int shutdown = 0;               // flag, to indicate reception of CTRL-C

void signalhandler(int sig) {
    shutdown = 1;               // set shutdown flag
}

void switcher(int sig) {        // preempt current thread
    taskSwitch(YIELD);
}

//******************************************************************************
// Assembler-Macros

// 64-Bit CPU 
#ifdef __x86_64
    #include "asm64.h"

// 32-Bit CPU
#else
    #define SAVE_REGS() asm volatile (  \
                        "   PUSHA \n\t" \
                        "   PUSHF     ")

    #define RESTORE_REGS()  asm volatile (  \
                        "   POPF  \n\t" \
                        "   POPA      ")

    #define SAVE_SP(VAR)    asm volatile ("  MOVL %esp, "#VAR"");
    #define RESTORE_SP(VAR) asm volatile ("  MOVL "#VAR", %esp");

#endif

//******************************************************************************
// local function prototypes

void startTimer(void);
void stopTimer(void);
void startPreempting(void);
void stopPreempting(void);

//******************************************************************************
// Static data of scheduler

int              schedulerState = 0;    // state of scheduler: not initialized

unsigned long    threadSP;              // storage for stackptr of thread 
unsigned long    scheduSP;              // storage for stackptr of scheduler

int              schedArg;              // parameter passed to scheduler
struct sigaction sigAction;             // for signalhandler
ThreadCB*        activeThread;          // currently active thread
int              schedType;             // the scheduler type
int              preemptInterval;       // the preemption interval

//******************************************************************************
//
// Functions of scheduler
//
//------------------------------------------------------------------------------
// Function initScheduler
// Purpose: initialize scheduler: set signal handlers, scheduling type, etc 
//          behaves as singleton

void initScheduler(int type, int interval) {
    if (schedulerState == 0) {
        sigAction.sa_flags = SA_RESTART;
        sigemptyset(&sigAction.sa_mask);

        sigAction.sa_handler = signalhandler;           // signal handler CTRLC
        sigaction(SIGINT, &sigAction, NULL);

        sigAction.sa_handler = switcher;                // signal handler timer
        sigaction(PREEMPT_SIGNAL, &sigAction, NULL);    // 

        if ((type == PREEMPT) || (type == FIFO))
            schedType = type;
        else {
            printf("*** no valid scheduler type\n ***");
            schedType = FIFO;
        }

        if (interval < MIN_TIMER_INT)
            preemptInterval = MIN_TIMER_INT;
        else                        
            preemptInterval = interval; 

        schedulerState = 1;                              // set to initialized
    }
}

//------------------------------------------------------------------------------
// Methode TaskSwitch
// executes the thread switching
//
// Arguments
// 
//     INIT:   first call of scheduler
//     ZOMBIE: active thread terminates
//     YIELD:  active thread yields
//     n > 0:  active thread waits for n clocks

void taskSwitch(int argument)
{
    TMethod   startMethod;              // start method of a thread
    long      stacksize;                // current stack size

    if (schedType == PREEMPT) {         // stop preemting
        stopPreempting();               
        stopTimer();
    }

    schedArg = argument;            // save argument to static variable

    /* --- check how we were called ----------------------------------------- */

    switch (schedArg)    {
        case INIT:
            if (schedulerState == 0)
                initScheduler(PREEMPT, DEF_TIMER_INT); // init with defaults
            break;
        case ZOMBIE :                       // thread exits with mythread_exit()
            {
            RESTORE_SP(scheduSP);           // scheduler: restore stackpointer
            RESTORE_REGS();                 // scheduler: restore regs and flags
            } 
            mtDelThread(activeThread);      // thread:    is deleted
        break;
        default :                           // thread yields or waits
            {
            SAVE_REGS();                    // thread:    save regs and flags
            SAVE_SP(threadSP);              // thread:    save stackpointer
            RESTORE_SP(scheduSP);           // scheduler: restore stackpointer
            RESTORE_REGS();                 // scheduler: restore regs and flags
            }                                          
            mtSaveSP(activeThread, threadSP); // thread:    store stackpointer

            stacksize = mtGetFreeStackSize(activeThread);
            if (stacksize <= 0)
                fprintf(stderr, "Run out of stack\n");
 
            if (schedArg == YIELD)
                    addToReadyQueue(activeThread);
            else
                    addToWaitQueue(activeThread, schedArg);
            break;
    }

    /* --- debug ------------------------------------------------------------ */
    if (DEBUG_OUTPUT) {printf("\n\t-> Ready queue\n"); printReadyQueueStatus();}


    /* --- Now we have to look for the next thread to be scheduled ---------- */
        
    activeThread = getNextThread();                     // get next ready thread


    if  ((shutdown) || (activeThread == NULL)) {
        if (shutdown) {
            printf("\n*** got CTRL_C\n");
            delQueues();
        }
        else {
            printWaitQueue(); //DEBUG_OUTPUT

            if (checkWaitQueue() == 0) {
                fprintf(stdout, "no more threads in waitQueue to schedule\n");
                delQueues();
            }
            else{
                // wait until a new waitQueue thread is ready
//                 startPreempting();
//                 startTimer();
            }
        }
    }
    else {

        /* --- debug ---------------------------------------------------------*/
        if (DEBUG_OUTPUT) { printf("\n\t-> Scheduler starting thread: \n\t");
                            mtPrintTCB(activeThread); }

        /* --- now start or restart thread -----------------------------------*/

        threadSP = mtGetSP(activeThread);           // thread:    get stackptr

        if (mtIsFirstCall(activeThread)) {          // if thread never run
            mtClearFirstCall(activeThread);         // thread: mark as started
            {  
              SAVE_REGS();                          // scheduler: save regs
              SAVE_SP(scheduSP);                    // scheduler: save SP
              RESTORE_SP(threadSP);                 // thread:    set SP
            }
            startMethod = mtGetStartMethod(activeThread);   // get start method
            startPreempting();
            startTimer();
            startMethod(mtGetArgPointer(activeThread));     // call start method
        }
        else {
            SAVE_REGS();                            // scheduler: save regs
            SAVE_SP(scheduSP);                      // scheduler: save stackptr
            RESTORE_SP(threadSP);                   // thread:    set stackptr
            RESTORE_REGS();                         // thread:    restore regs
            startPreempting();                      // enable preempting
            startTimer();                           // start timer
        }
    }

    return;
}

//******************************************************************************
// Timer stuff for preemptive scheudling
// use interval timer ITIMER_VIRTUAL to prevent problems with sleep and alarm
// a specific signals is blocked during execution of a handler and only
// deblocked on exiting the handler: since we use a handler to switch
// a thread, the signal stays blocked, which can be avoided by setting
// the  SA_NODEFER flag on the signal
//------------------------------------------------------------------------------

// configure timer

void setPreemptionInterval(int intval) {
    if (intval >= MIN_TIMER_INT)
        preemptInterval = intval;
}

//------------------------------------------------------------------------------
// use it as one shot timer

void startTimer(void) {
    struct itimerval it;
    if (schedType == PREEMPT) {
        it.it_interval.tv_sec  = 0;
        it.it_interval.tv_usec = 0;
        it.it_value.tv_sec     = 0;
        it.it_value.tv_usec    = preemptInterval;
        setitimer(PREEMPT_TIMER, &it, NULL);
    }
}

//------------------------------------------------------------------------------
// just stop the timer

void stopTimer(void) {
    struct itimerval it;
    it.it_value.tv_usec    = 0;
    setitimer(PREEMPT_TIMER, &it, NULL);
}

//------------------------------------------------------------------------------

void stopPreempting(void)  {
    sigset_t sigSet;
    if (schedType == PREEMPT) {
        sigemptyset(&sigSet);
        sigaddset(&sigSet, SIGVTALRM);
        sigprocmask(SIG_BLOCK, &sigSet, NULL);
    }
}

//------------------------------------------------------------------------------

void startPreempting(void) {
    sigset_t sigSet;
    if (schedType == PREEMPT) {
        sigemptyset(&sigSet);
        sigaddset(&sigSet, SIGVTALRM);
        sigprocmask(SIG_UNBLOCK, &sigSet, NULL);    
    }
}

//******************************************************************************

