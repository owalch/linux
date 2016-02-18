//***************************************************************************
// ProcA9.c
// Author:      M. Thaler
// Date:        29.9.99 (Rev. 8/2004, Rev. 3/2008)
//***************************************************************************

//***************************************************************************
// system includes
//***************************************************************************

#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>

#include <pthread.h>

// globaler array

#define ARRAY_SIZE 8

char     GArray[ARRAY_SIZE][ARRAY_SIZE];

// *************************************************************************

void *ThreadF(void *letter) {
    int    i,j;
    int    LowLim, HighLim;
    char    letr;

    letr =  *(char *)letter;
    if ( letr == 'p') {     // paremeter = p: fill lower half of array
        LowLim = 0; HighLim = ARRAY_SIZE / 2;
    }
    else {            //  paremeter != p: fill upper half of array
        LowLim = ARRAY_SIZE / 2; HighLim = ARRAY_SIZE;
    }

    for (i = LowLim; i < HighLim; i++) {    // fill corresponding half
        for (j = 0; j <  ARRAY_SIZE; j++)
            GArray[i][j] = letr;
    }
    
    for (i = 0; i < ARRAY_SIZE; i++) {      // print whole array
                   for (j = 0; j <  ARRAY_SIZE; j++)
            printf("%c", GArray[i][j]);
        printf("\n");
    }
    printf("\n");
    pthread_exit(0);
}

//***************************************************************************
// Function: main(), parameter: none
//***************************************************************************

int main(void) {

    pthread_t   thread1, thread2;
    int         i,j;
    int         pthr;
    char        let1 = 'p';
    char        let2 = 'c';
    
    for (i = 0; i < ARRAY_SIZE; i++)
        for (j = 0; j <  ARRAY_SIZE; j++)
            GArray[i][j] = '-';

    printf("\nArray vor Threads\n\n");
        for (i = 0; i < ARRAY_SIZE; i++) {
                for (j = 0; j <  ARRAY_SIZE; j++)
                        printf("%c", GArray[i][j]);
        printf("\n");
    }

    pthr = pthread_create(&thread1, NULL, ThreadF, (void *)&let1);
    if (pthr < 0) perror("Could not create thread");

    pthr = pthread_create(&thread2, NULL, ThreadF, (void *)&let2);
    if (pthr < 0) perror("Could not create thread");

    pthread_join(thread1, NULL);    // program has to wait for the thread
    pthread_join(thread2, NULL);    // program has to wait for the thread

    printf("\n... nach Threads\n");
        for (i = 0; i < ARRAY_SIZE; i++) {
            for (j = 0; j <  ARRAY_SIZE; j++)
                printf("%c", GArray[i][j]);
        printf("\n");
    }
}

//***************************************************************************

