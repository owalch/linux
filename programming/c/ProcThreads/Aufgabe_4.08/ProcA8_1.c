//***************************************************************************
// ProcA8_1.cc
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

// globaler array

#define ARRAY_SIZE 8
char GArray[ARRAY_SIZE][ARRAY_SIZE];

//***************************************************************************
// Function: main(), parameter: none
//***************************************************************************

int main(void) {

    pid_t  pid;
    int    i,j;

    
    for (i = 0; i < ARRAY_SIZE; i++)
        for (j = 0; j <  ARRAY_SIZE; j++)
            GArray[i][j] = '-';

    printf("Array vor fork()\n\n");
        for (i = 0; i < ARRAY_SIZE; i++) {
            for (j = 0; j <  ARRAY_SIZE; j++)
                printf("%c ", GArray[i][j]);
        printf("\n");
    }

    pid = fork();
    switch (pid) {
      case -1:
            perror("Could not fork");
            break;
      case 0:   // --- child fills upper half of array ---
            sleep(2);
            for (i =  ARRAY_SIZE / 2; i < ARRAY_SIZE; i++)
                for (j = 0; j <  ARRAY_SIZE; j++)
                    GArray[i][j] = 'c';
            break;
      default:  // --- parent fills lower half of array ---
            sleep(1);                           // parent sleeps 
            for (i =  0; i < ARRAY_SIZE / 2; i++)
                for (j = 0; j <  ARRAY_SIZE; j++)
                    GArray[i][j] = 'p';
        break;
    }

    if (pid == 0)
        printf("\nKinderarray\n\n");
    else
        printf("\nElternarray\n\n");

    for (i = 0; i < ARRAY_SIZE; i++) {
        for (j = 0; j <  ARRAY_SIZE; j++)
            printf("%c ", GArray[i][j]);
        printf("\n");
    }
    wait(NULL);                                 // wait for child
    exit(0);
}

//***************************************************************************
