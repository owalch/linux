/******************************************************************************
* File:     startApp.c
* Purpose:  basic sequence with semaphores
* Author:   M. Thaler, 1/2011, BSy
******************************************************************************/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

#include <sys/mman.h>
#include <fcntl.h>
#include <semaphore.h>

#include "commonDefs.h"


int main(void) {

    int      j;
    char     string[8];
    sem_t    *coin, *lock;
    pid_t    tellerPID;

    sem_unlink(LOCK_SEMAPHOR);          // delete seamphor if it still exists
    sem_unlink(COIN_SEMAPHOR);          // delete seamphor if it still exists

    // set up a semaphore
    lock = sem_open(LOCK_SEMAPHOR, O_CREAT, 0700, 0);
    coin = sem_open(COIN_SEMAPHOR, O_CREAT, 0700, 1);

    // now that the resources are set up, the supervisor can be started
    for (j = 1; j <= CUSTOMERS; j++) {
        if (fork() == 0) {
            sprintf(string, "%d", j);
            execl("./customer.e", "customer.e", string, NULL);
            printf("*** could not start customer.e ***\n");
        }
    }
    
    if ((tellerPID = fork()) == 0) {
            execl("./coffeeTeller.e", "coffeeTeller.e", "0", NULL);
            printf("*** could not start coffeTeller ***\n");
    }
    
    waitpid(tellerPID, NULL, 0);
    system("killall coffeeTeller.e");
    system("killall customer.e");       // kill all customers

    // clean up resources
    sem_unlink(LOCK_SEMAPHOR);
    sem_unlink(COIN_SEMAPHOR);
    printf("\n");
}
