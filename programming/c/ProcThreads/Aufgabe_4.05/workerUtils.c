//*******************************************************************
// Author:	M. Thaler, ZHW
// Date:	11.12.2004
// Purpose:	helper applications to consume cpu time
//*******************************************************************

#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <signal.h>
#include <sys/types.h>

void setRandom(void) {
    srandom((unsigned int)time(NULL));	// new random sequence
}

void justWork(unsigned load) {
    unsigned j;
    for (j = 0; j < load; j++) {};    // just work
}

void workHard(unsigned low, unsigned high) {
    double rv;
    unsigned us, j;
    high = high - low;
    rv = ((double)random())/RAND_MAX;	// make random value (0..1)
    us = low + (unsigned)(rv * high);	// between lower and higher limit	
    for (j = 0; j < us; j++) {};	// just work 
    setRandom();			// reseed random generator
}

void randomSleep(unsigned low, unsigned high) {
    double rv;
    unsigned us;
    high = high - low;
    rv = ((double)random())/RAND_MAX;	// make random value (0..1)
    us = low + (unsigned)(rv * high);	// between lower and higher limit	
    usleep(us*1000);
}


pid_t startWorker(void) {		// make a hard working process
    pid_t pid = fork();
    if (pid == 0) {			// child: pid = 0 -> ifinite loop
        while (1) {
                workHard(50, 800);	// work hard (choose random interval
        }                               // between 50us and 800us)
    }
    return pid;				// return pid if parent
}

void stopWorker(pid_t worker) {
    kill(worker, SIGKILL);		// terminate worker process
}
