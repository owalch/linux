/******************************************************************************
* File:     coffeTeller.c
* Purpose:  mutex with pthreads
* Author:   M. Thaler, 1/2011, BSy
******************************************************************************/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

#include <pthread.h>

#include "commonDefs.h"

//*****************************************************************************

void *coffeeTeller(void* data) {

    int i;
    cData *cD = (cData *) data;


    /* now start selling coffee */
    printf("\nCoffee teller machine starting\n\n");
    
    i = 0;
    
    while (i < ITERATIONS) {
        if (cD->coinCount != cD->selCount1 + cD->selCount2) {
            printf("error c = %5d  s1 =%6d   s2 =%6d   diff: %4d\ti = %d\n",
                   cD->coinCount, cD->selCount1, cD->selCount2, 
                   cD->coinCount - cD->selCount1 - cD->selCount2, 
                   i);
            pthread_mutex_lock(&(cD->mutex));
            cD->coinCount = 0;
            cD->selCount1 = cD->selCount2 = 0;
            pthread_mutex_unlock(&(cD->mutex));

        }
        if (i%1000000 == 0) {
            printf("working\n");
        }
        i++;
    }

    return cD;
}

//*****************************************************************************
