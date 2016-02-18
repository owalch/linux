/******************************************************************************
* File:     customer.c
* Purpose:  customer of ice cream teller machine 
* Author:   M. Thaler, 1/2011, BSy
******************************************************************************/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#include <semaphore.h>

#include "commonDefs.h"
#include "random.h"


int main(int argc, char *argv[]) {

    int     i, flag, myID;
    sem_t   *teller, *supplier, *coin;

    // get the semaphor
    teller  = sem_open(TELLER_SEMAPHOR, 0);
    supplier = sem_open(SUPPLIER_SEMAPHOR, 0);
    coin = sem_open(COIN_SEMAPHOR, 0);

    if (argc > 1)
        myID = atoi(argv[1]);
    else
        myID = -1;

    flag = 1;
    while (flag > 0) {
        printf("\t\t>> customer: %1d\tgot ice\n\n", myID);
        // do something else (not necessarily sleeping)
        usleep(randomNumber(2000000, 400000));
    }
    exit(0);
}
