/******************************************************************************
* File:     customer.c
* Purpose:  basic sequence with semaphores
* Author:   M. Thaler, 1/2011, Bsy
******************************************************************************/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#include <sys/mman.h>
#include <fcntl.h>
#include <semaphore.h>

#include "commonDefs.h"


int main(int argc, char *argv[]) {

    int     i, myID;
    int     coin_val;
    sem_t   *coin, *lock;

    if (argc > 1)
        myID = atoi(argv[1]);
    else
        myID = 0;
    
    printf("Customer starting (%d)\n", myID);

    // get the semaphor
    lock  = sem_open(LOCK_SEMAPHOR, 0);
    coin  = sem_open(COIN_SEMAPHOR, 0);
    
    // now start buying coffe
    for (i = 0; i < ITERS; i++) {
        sem_wait(coin);
        printf("\t\t\tcustomer: put coin(%d)@%d\n", myID,i);
        sem_getvalue(coin, &coin_val);
        if (coin_val == 0)
            sem_post(lock);
    }
}
