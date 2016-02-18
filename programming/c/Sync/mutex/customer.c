/******************************************************************************
* File:     customer.c
* Purpose:  mutex with pthreads
* Author:   M. Thaler, 1/2011, BSy
******************************************************************************/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>

#include <pthread.h>

#include "commonDefs.h"

//*****************************************************************************

extern cData cD;

void *customer(void* data) {
    struct drand48_data randData;
    double ranNum;
    int i;

    cData *cD = (cData *) data;
    
    srand48_r((long)(time(NULL)), &randData);   // seed random generator

    // put coin and select coffee
    for (i = 0; i < ITERATIONS; i++) {
        drand48_r(&randData, &ranNum);          // get random number (0.0 - 1.0)
        pthread_mutex_lock(&(cD->mutex));
        cD->coinCount      += 1;
        if (ranNum < 0.5)
            cD->selCount1 += 1;
        else
            cD->selCount2 += 1;
        pthread_mutex_unlock(&(cD->mutex));
    }
    
    pthread_exit(0);  
}

//*****************************************************************************
