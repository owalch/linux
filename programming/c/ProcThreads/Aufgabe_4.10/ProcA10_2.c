//***************************************************************************
// ProcA10_2.cc  
// Author:      M. Thaler
// Date:        29.9.99 (Rev. 8/2004, Rev. 3/2008)
//***************************************************************************

//***************************************************************************
// system includes
//***************************************************************************

#include <sys/types.h>
#include <sys/wait.h>
#include <sys/times.h>
#include <time.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>

//***************************************************************************
// Function: main(), parameter: shell command in "..."
//***************************************************************************

int main(int argc, char *argv[]) {

    struct tms  startT, endT;
    clock_t     StartTime, EndTime;
    double      Zeit, ticks, usr, sys, cusr, csys;
    int i;
    
    ticks = sysconf(_SC_CLK_TCK);

    StartTime = times(&startT);

    // ************ playground
//     sleep(3);
//     usleep(500000);
    for (i=10e6; i<10e8;i++) {}
    // ************ playground

    EndTime = times(&endT);

    Zeit = (double)(EndTime - StartTime) / ticks;
    usr  = (double)(endT.tms_utime - startT.tms_utime) / ticks;
    sys  = (double)(endT.tms_stime - startT.tms_stime) / ticks;
    cusr = (double)(endT.tms_cutime - startT.tms_cutime) / ticks;
    csys = (double)(endT.tms_cstime - startT.tms_cstime) / ticks;

    printf("\n\n");
    printf("Befehl:\t\t\t\t%s\n", argv[1]);
    printf("Uhrzeit:\t\t\t%4.3f\n", Zeit);
    printf("User CPU-time:\t\t\t%4.3f\n", usr);
    printf("System CPU-time:\t\t%4.3f\n", sys);
    printf("Children user CPU-time:\t\t%4.3f\n", cusr);
    printf("Children system CPU-time:\t%4.3f\n", csys);

    exit(0);
}

//***************************************************************************
