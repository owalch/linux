/******************************************************************************
* File:     startApp.c
* Purpose:  ice cream teller
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
    pid_t    tellerPID;
    sem_t   *teller, *supplier, *coin;

    sem_unlink(TELLER_SEMAPHOR);        // delete seamphor if it still exists
    sem_unlink(SUPPLIER_SEMAPHOR);        // delete seamphor if it still exists
    sem_unlink(COIN_SEMAPHOR);          // delete seamphor if it still exists

    // set up a semaphore
    teller = sem_open(TELLER_SEMAPHOR, O_CREAT, 0700, 1);
    supplier = sem_open(SUPPLIER_SEMAPHOR, O_CREAT, 0700, 1);
    coin = sem_open(COIN_SEMAPHOR, O_CREAT, 0700, 1);

    // start the customers
    for (j = 1; j <= CUSTOMERS; j++) {
        if (fork() == 0) {
            sprintf(string, "%d", j);
            execl("./customer.e", "customer.e", string, NULL);
            printf("*** could not start customer.e ***\n");
        }
    }

    // start the supplier
    if (fork() == 0) {
            execl("./supplier.e", "supplier.e", "0", NULL);
            printf("*** could not start supplier ***\n");
    }

    // start the iceCreamTeller
    if ((tellerPID = fork()) == 0) {
            execl("./iceCreamTeller.e", "iceCreamTeller.e", "0", NULL);
            printf("*** could not start coffeTeller ***\n");
    }

    // wait for the teller machine to finish
    waitpid(tellerPID, NULL, 0);
    system("killall customer.e");       // kill all customers
    system("killall supplier.e");       // kill the supplier

    // clean up resources
    sem_unlink(TELLER_SEMAPHOR);          // delete seamphor if it still exists
    sem_unlink(SUPPLIER_SEMAPHOR);        // delete seamphor if it still exists
    sem_unlink(COIN_SEMAPHOR);          // delete seamphor if it still exists

    printf("\n");
}
