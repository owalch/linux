/**
 * @file    queues.h
 * @brief   Header file for scheduling queues
 *
 * This file contains all header information.
 *
 *
 *
 * @author  M. Thaler
 * @author  O. Walch
 *
 * @date    2012-04-17
 * @version 1.0
 */
#ifndef QUEUES_HEADER_H
#define QUEUES_HEADER_H

#include <sys/time.h>

#include "mythread.h"

#define READY_QUEUES        3

#define P_HIGH              0
#define P_MED               1
#define P_LOW               2

/******************************************************************************/
// Public header functions declaration
/******************************************************************************/
void initQueues(void);
void delQueues(void);
ThreadCB* getNextThread(void);
void addToReadyQueue(ThreadCB *tcb);
void addToWaitQueue(ThreadCB* tcb, int sleepTime);
unsigned checkWaitQueue(void);
unsigned checkReadyQueue(int prio);
void printWaitQueue(void);
void printReadyQueueStatus(void);

/******************************************************************************/

#endif // QUEUES_HEADER_H

