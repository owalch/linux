//***************************************************************************
// ProcA3.c
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

//***************************************************************************
// Function: main(), parameter: none
//***************************************************************************

int main(void) {

    pid_t  pid;
    int    status;
    int    i, retval;
    char   str[8];

    i = 5;

    printf("\n\ni vor fork: %d\n\n", i);

    pid = fork();
    switch (pid) {
      case -1:
        perror("Could not fork");
        break;
      case 0:
        i++;
        sprintf(str, "%d",i);    // convert integer i to string str
        retval = execl("./ChildProgA3.e", "ChildProgA3.e", str, NULL);
        if (retval < 0) perror("\nexecl not successful");
        break;
      default:
        i--;
        printf("\n... wird sind die Eltern %d mit i %d ", getpid(), i);
        printf("und Kind %d,\n    unsere Eltern sind %d\n", pid, getppid());
        wait(&status);
        break;
    }
    printf("\n. . . . . und wer bin ich ?(pid: %d)\n\n",getpid());
    exit(0);
}

//***************************************************************************
