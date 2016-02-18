//***************************************************************************
// ProcA5.c
// Author:      M. Thaler
// Date:        29.9.99 (Rev. 8/2004, 3/2008)
//***************************************************************************

//***************************************************************************
// system includes
//***************************************************************************

#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>

#include "workerUtils.h"

#define HARD_WORK 20000000
#define ITERATIONS 20

//***************************************************************************
// Function: main(), parameter: none
//***************************************************************************

int main(void) {

    pid_t    pid, worker1, worker2;
    int    i;

    worker1 = startWorker();     // start CPU load -> worker process with
    worker2 = startWorker();     // randomized load to force context switches
    pid = fork();
    switch (pid) {
      case -1:
        perror("Could not fork");
        break;
      case 0:
        for (i = 0; i < ITERATIONS; i++) {
            justWork(HARD_WORK);
            printf("%d \t\tChild\n", i);
        }
        break;
      default:
        for (i = 0; i < ITERATIONS; i++) {;
            justWork(HARD_WORK);
            printf("%d \tMother\n", i);
        }
        stopWorker(worker1);         // stop (kill) worker process
        stopWorker(worker2);         // stop (kill) worker process
        break;
    }
    printf("I go it ...\n");
    exit(0);
}
//***************************************************************************
