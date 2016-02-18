/******************************************************************************
* File:     coffeTeller.c
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

    int     i,j;
    sem_t   *coin, *lock;

    // get the semaphor
    lock = sem_open(LOCK_SEMAPHOR, 0);
    coin = sem_open(COIN_SEMAPHOR, 0);
    
    // now start selling coffee
    printf("\nCoffee teller machine starting\n\n");
    i = 0;
    
    while (i < ITERS) {
        sem_wait(lock);
        printf("(%d) teller: dispense coffee & unlock\n",i); 
        i++;
        for (j=0; j<NUM_COINS; j++) {
            sem_post(coin);
        }
    }
}
