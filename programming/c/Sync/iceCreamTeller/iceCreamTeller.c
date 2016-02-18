/******************************************************************************
* File:     iceCreamTeller.c
* Purpose:  ice cream teller machine
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

    int   i, count, currentStock = 0;
    char  string[8];
    sem_t   *teller, *supplier, *coin;

    // get the semaphor
    teller  = sem_open(TELLER_SEMAPHOR, 0);
    supplier = sem_open(SUPPLIER_SEMAPHOR, 0);
    coin = sem_open(COIN_SEMAPHOR, 0);

    // now start selling
    printf("\nice cream teller machine starting\n");

    count = REFILLS*QUANTITY;
    
    while (count > 0) {

        printf("teller: got money");

        printf(" -> dispense ice cream (stock left %d)\n", currentStock);

        count--;
    }
    exit(0);
}
