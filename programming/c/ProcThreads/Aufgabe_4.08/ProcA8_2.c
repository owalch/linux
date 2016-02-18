//***************************************************************************
// ProcA8_2.cc
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
#include <sched.h>


#include "workerUtils.h"

#define ANZAHL      15
#define WORK_HARD   10000000

//***************************************************************************
// Function: main(), parameter: none
//***************************************************************************

int main(void) {

    FILE   *fdes;
    pid_t  pid, worker;
    int    i, x, y;

    worker = startWorker();         // start CPU load to force context 
                                    // switches
    fdes = fopen("AnyOutPut.txt", "w");
    if (fdes == NULL) perror("Cannot open file");

    usleep(500000);

    pid = fork();
    switch (pid) {
        case -1:
            perror("Could not fork");
            break;
        case 0:
            for (i = 1; i <= ANZAHL; i++) {
                for (x=10e6;x<10e8;x++) {}
                fprintf(fdes, "Fritzli\t%d\n", i);
                fflush(fdes);       // make sure date is written to file
                justWork(WORK_HARD);
            }
            break;
      default:
            for (i = 1; i <= ANZAHL; i++) {
                for (y=10e6;y<10e8;y++) {}
                fprintf(fdes, "Mami\t%d\n", i);
                fflush(fdes);       // make sure date is written to file
                justWork(WORK_HARD);
            }
            wait(NULL);
            stopWorker(worker);
            break;
    }
    printf("We are done\n");
    exit(0);
}

//***************************************************************************

