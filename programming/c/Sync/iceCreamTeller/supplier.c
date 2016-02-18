/******************************************************************************
* File:     supplier.cc
* Purpose:  ice cream supplier
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
    
    int   i, flag, refills;
    sem_t   *teller, *supplier, *coin;

    // get the semaphor
    teller  = sem_open(TELLER_SEMAPHOR, 0);
    supplier = sem_open(SUPPLIER_SEMAPHOR, 0);
    coin = sem_open(COIN_SEMAPHOR, 0);

    refills = 0;
    flag = 1;
    while (flag > 0) {
        sleep(DELIVERY_RATE);
        printf("\n********************************");
        printf("\n* refilling items (refill %3d) *", ++refills);
        printf("\n********************************\n");
        
        // check if max refills reached
        if (refills == REFILLS)
            flag = 0;
    }
    exit(0);
}
