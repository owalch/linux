/******************************************************************************
* File:     tellerApp.c
* Purpose:  mutex with locks
* Author:   M. Thaler, 2011, BSy
******************************************************************************/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

#include <pthread.h>

#include "commonDefs.h"
#include "coffeeTeller.h"
#include "customer.h"

//*****************************************************************************
// common data

cData cD;

//*****************************************************************************

int main(void) {
    int j;

    pthread_t tellerThread, customerThreads[CUSTOMERS];

    cD.coinCount = 0;
    cD.selCount1 = 0;
    cD.selCount2 = 0;

    pthread_mutex_init(&(cD.mutex), NULL);

    // start teller and customers now that everything is set up    
    pthread_create(&tellerThread, NULL, coffeeTeller, &cD);    
    for (j = 0; j < CUSTOMERS; j++) {
        pthread_create(&(customerThreads[j]), NULL, customer, &cD);
    }

    // wait for all threads to terminate  
    pthread_join(tellerThread, NULL);

    for (j = 0; j < CUSTOMERS; j++) {
        pthread_join(customerThreads[j], NULL);
    }

    return 0;
}

