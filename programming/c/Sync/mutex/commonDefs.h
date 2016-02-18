#ifndef MY_DEFINITIONS_HEADER_H
#define MY_DEFINITIONS_HEADER_H

//******************************************************************************
// Author   M. Thaler, ZHAW, 2011
// Purpose  common definitions
// File     commonDefs.h
//******************************************************************************

#define SEMAPHOR    "/my_semaphor_1_name_mutex"
#define SHAREDMEM   "/my_shared_memory_name_mutex"

#define ITERATIONS  100*1000*1000

//******************************************************************************

#define CUSTOMERS   10          // number of customers to be started

//******************************************************************************
// common data

typedef struct {
    int coinCount;              // number of paid coffees
    int selCount1;              // number of chosen coffees of type 1
    int selCount2;              // number of chosen coffees of type 2
    pthread_mutex_t mutex;      // common mutex
} cData;

//******************************************************************************

#endif /* MY_DEFINITIONS_HEADER_H */

