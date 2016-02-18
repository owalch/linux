/**
 * @file    test.c
 * @brief   Testing file for the whole scheduler implementation
 *
 * This file contains the whole testing implementation.
 *
 *
 *
 *
 * @author  O. Walch
 *
 * @date    2012-04-17
 * @version 1.0
 */
#include <stdio.h>
#include <unistd.h>
#include <assert.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>


#include "mylist.h"
#include "mythread.h"
#include "queues.h"
#include "scheduler.h"


#define ITERS       5
#define MAX_ARGS    10
#define STR_LEN     50

/******************************************************************************/
// prototype of local functions
/******************************************************************************/
void beginTest(const char *str);
void endTest(void);
void shuffleIntArray(int *ar, int size);
void printMessage(void *ptr);
void printMessageSleep(void *ptr);
void threadInThread(void *ptr);

/******************************************************************************/
/**
 * @fn      int main(void)
 * @return  int value, 0 if succeeded, -1 if failed
 *
 * This is the main testing function. This function is responsible to test all
 * possible cases.
 */
int main(void){

    int i;
    int rand_prio;
    int func_idx;                               // function index
    MyThread *th;
    char mes_args[MAX_ARGS][STR_LEN];

    
    /* add threads -----------------------------------------------------------*/
    beginTest("Adding threads");
    
    func_idx = 0;
    for (i=0; i<MAX_ARGS; i++) {                // create auto generated threads

        rand_prio = rand()%10;
        if (rand_prio <= 3)
            rand_prio = HIGH;
        else if (rand_prio >3 && rand_prio <=6)
            rand_prio = MEDIUM;
        else
            rand_prio = LOW;

        /* generate random messages */
        sprintf(&(mes_args[i][0]), "rand_Th_%d prio %d", i, rand_prio);
        if (func_idx == 0) {
            myThreadCreate(th, printMessage, (void *)&(mes_args[i][0]), rand_prio, 4096);
        }
        if (func_idx == 1) {
            myThreadCreate(th, printMessageSleep, (void *)&(mes_args[i][0]), rand_prio, 4096);
        }
        if (func_idx == 2) {
            myThreadCreate(th, threadInThread, (void *)&(mes_args[i][0]), rand_prio, 4096);
        }

        func_idx++;                             // handle function indec counter
        func_idx %= 3;
    }



    printReadyQueueStatus();
    sleep(2);
    beginTest("Start scheduling");
    myThreadStart();



    
    endTest();


    sleep(10);
    return 0;
}


/******************************************************************************/

void beginTest(const char *str) {
    printf("\n*************************************************************\n");
    if (str != NULL)
        printf("%s\n", str);
}


void endTest(void){
    printf("Test successfully finished\n");
    printf("\n*************************************************************\n");
}

//******************************************************************************
void printMessage(void* ptr)                // user defined method for threads
{
    char *message;
    unsigned i,j;

    message = (char*) ptr;
    for (i = 0; i < ITERS; i++) {
        printf("%s  \n", message);
        for (j = 0; j < 500000; j++) {}    // do some work
    }
    myThreadSleep(4000);
    myThreadExit();
}

/******************************************************************************/

void printMessageSleep(void* ptr)             // user defined method for threads
{
    char *message;
    unsigned i,j;

    message = (char*) ptr;
    for (i = 0; i < ITERS; i++) {
        printf("%s  \n", message);
        for (j = 0; j < 500000; j++) {}    // do some work
    }
    myThreadSleep(2000);
    for (i = 0; i < 10; i++) {
        if (!(i%2))
            printf("%s -> tic\n", message);
        else
            printf("%s -> tac\n", message);
        myThreadSleep(1000);
    }
    myThreadExit();
}

/******************************************************************************/
void threadInThread(void* ptr)                  // user def method for threads
{
    MyThread *th;
    const char *mes1 = "Th 11 in Th child high";
    const char *mes2 = "Th 12 in Th child high";
    const char *mes3 = "Th 13 in Th child high";
    char *message;
    unsigned i,j;

    myThreadCreate(th, printMessage, (void *)mes1, HIGH, 4096);
    myThreadCreate(th, printMessage, (void *)mes2, MEDIUM, 4096);
    myThreadCreate(th, printMessage, (void *)mes3, LOW, 4096);
    
    message = (char*) ptr;
    for (i = 0; i < ITERS; i++) {
        printf("%s  \n", message);
        for (j = 0; j < 500000; j++) {}    // do some work
    }

    myThreadSleep(4000);
    myThreadExit();
}

