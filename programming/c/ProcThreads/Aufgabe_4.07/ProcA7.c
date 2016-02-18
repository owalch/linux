//***************************************************************************
// ProcA7.cc
// Author:      M. Thaler
// Date:        29.9.99 (Rev. 8/2004)
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

//***************************************************************************
// Function: main(), parameter: none
//***************************************************************************

int main(void) {

	pid_t	pid;
	int	j;

	for (j = 0; j < 3; j++) {	    // generate 3 processes
		pid = fork();
		switch (pid) {
		  case -1:
			perror("Could not fork");
			break;
		  case 0:
			sleep(j+2);	            // process j sleeps for j+2 sec
			exit(0);	            // then exits
			break;
		  default:                  // parent
			break;
		}
	}

    /* Prevent zombie process */
    if (fork() == 0) {
        if (fork != 0)
            exit(0);
    } else {
        wait(NULL);
        exit(0);
    }
    
// 	sleep(6);	// parent process sleeps for 6 sec
// 	wait(NULL);	// consult manual for "wait"
// 	sleep(2);
// 	wait(NULL);
// 	sleep(2);
// 	wait(NULL);
// 	sleep(2);
// 	exit(0);
}
