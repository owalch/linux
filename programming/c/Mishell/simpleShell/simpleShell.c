/******************************************************************************
//    Aufgabe:    Simple Shell   
//    File:       sishell.c
//    Fach:       Betriebssysteme
//    Autor:      M. Thaler, 2/2010
//    Modified:   O. Walch / 3/2012
******************************************************************************/

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <fcntl.h> 
#include <sys/wait.h>

#include "readline.h"

//*****************************************************************************

#define MAX_argv 16                     // max number of command line arguments
#define STR_LEN  32                     // max length of command line arguments

//*****************************************************************************

int main(void) {
    char argstr[MAX_argv][STR_LEN];     /* storage for command line arguments */
    char *argv[MAX_argv];               /* pointer to command line arguments */
    char *token;                        /* pointer to token */
    char *copy;
    char string[STR_LEN];               /* character string for command line */
    char delimiter[] = " |\t\n";        /* delimiter for the commands */
    int idx = 0;                        /* index variable */
    pid_t PID;                          /* process identifier */

    copy = malloc(sizeof(char) *STR_LEN);
    
    
    while (1) {
        printf("# ");
        readline(string, STR_LEN);      /* read one line from stdin */
        strcpy(copy, string);

        /* get first token */
        token = strtok(copy, delimiter);
        while (token != NULL)
        {
            strcpy(&(argstr[idx][0]), token);
            argv[idx] = argstr[idx];        /* set pointer to argument string */
            idx++;
            token = strtok(NULL, delimiter);
            printf("%s\n", token);
        }
        free(copy);
        
        argv[idx] = NULL;               /* terminate arguments with NULL pointer */
        
        if ((PID = fork()) == 0) {      /* fork child process */
            strcpy(string, "/bin/");    /* "compose" path of command (1st arg) */
            strcat(string, argv[0]);    /* add command */
            execv(string, &argv[0]);    /* execute command */
            printf("!!! panic !!!\n");  /* should not come here */
        }
        else if (PID < 0) {
            printf("fork failed\n");    /* fork didn't succeed */
            exit(-1);                   /* terminate sishell */
        }
        else                            /* here we are parents */
            wait(0);                    /* wait for child process to terminate */
    }
}

//*****************************************************************************
