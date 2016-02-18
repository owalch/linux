//******************************************************************************
// Author	M. Thaler, ZHAW, 2011
// Purpose	random functions
// File		random.c
//******************************************************************************

#include <stdlib.h>
#include <time.h>

#include "random.h"

//******************************************************************************

void randomize(void);

//******************************************************************************
// make random number (integer) between high and lwo
//------------------------------------------------------------------------------

unsigned randomNumber(unsigned high, unsigned low) {
    static first = 1;
    double ranVal, retVal;
    unsigned rv;
    long unsigned i;

    if (first) {
        randomize();
        for (i = 0; i < 1000; i++) 
            drand48();
        first = 0;
    }
    ranVal = drand48();
    
    if (high == low)
        retVal = high * ranVal;
    else if (high > low)
        retVal = (double)low + ((high - low) * ranVal);
    else
        retVal = 0;

    rv = (unsigned)(retVal + 0.5);
    return(rv);
}

//******************************************************************************
// toss a coin
//------------------------------------------------------------------------------

unsigned tossCoin(void) {
    if (drand48() >= 0.5)
        return 1;
    else
        return 0;
}

//******************************************************************************
// read the system time and seed the random genrator used by randomNumber()
// => never twice the same result
//------------------------------------------------------------------------------

void randomize(void) {
    srand48((long int)time(NULL));
}

//******************************************************************************
