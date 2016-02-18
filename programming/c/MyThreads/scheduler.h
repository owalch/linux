#ifndef SCHEDULER_HEADER
#define SCHEDULER_HEADER
//******************************************************************************
// Implementation file for module scheduler
// working implementation of the thread scheduler 
//
// Operating Systems, J. Zeman, Okt. 99
// File: scheduler.cc
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
//                      SAVE_SP(SCHEDU_SP);
//                      RESTORE_SP(THREAD_SP);    
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

#include "mythread.h"

#define YIELD            0
#define ZOMBIE          -1
#define INIT            -2
#define PREEMPT        100
#define FIFO           101
#define MIN_TIMER_INT  100      // minimal preemption timer interval (0.1ms)
#define DEF_TIMER_INT 1000      // default preemption timer interval (1ms)

#define STACK_MIN 2*2048        // needs to be that to avoid segmentation error
                                // when using printf in thread function

#define PREEMPT_SIGNAL  SIGVTALRM
#define PREEMPT_TIMER   ITIMER_VIRTUAL

//******************************************************************************

void initScheduler(int type, int interval); // init scheduler
void taskSwitch(int argument);              // the thread switcher
void setPreemptionInterval(int intval);     // set preeption interval

//******************************************************************************
#endif // SCHEDULER_HEADER
