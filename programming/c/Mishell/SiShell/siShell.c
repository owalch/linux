/******************************************************************************
//  Aufgabe:    Simple Shell
//  File:       sishell.c
//  Fach:       Betriebssysteme
//  Autor:      M. Thaler,  2/2010
//  Modified:   O. Walch,   3/2012
******************************************************************************/
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include    <errno.h>
#include <sys/types.h>
#include <fcntl.h> 
#include <sys/wait.h>

#include "readline.h"

//*****************************************************************************

#define MAX_argv    16                  // max number of command line arguments
#define STR_LEN     32                  // max length of command line arguments
#define PWD_LEN     50                  // max length of pwd name

//*****************************************************************************
/* Function header declaration */


int main(void) {
    char argstr[MAX_argv][STR_LEN];     // storage for command line arguments
    char *argv[MAX_argv];               // ptr to command line arguments
    char *token;                        // ptr to command line token
    char buffer[STR_LEN];               // character buffer for command line
    char delimiter[] = " |\n\t";        // delimiter for the commands
    int idx;                            // index variable
    int w_ptr;                          // ptr to the output name
    int i;                              // counter variable
    pid_t PID;                          // process identifier
    int fdw;                            // write file descriptor
    int dir;                            // directory ret value
//     char pwd_buf[PWD_LEN];

    fprintf(stdout, "\E[0;0H");
    fprintf(stdout, "\E[2J");

    /* set cursor to home */
    fprintf(stdout, "\E[0;0H");             // set cursor to home 0;0
    fprintf(stdout, "\E[2J");               // clear screen and set cursor to home

    
    while (1) {
        printf("# ");                   // set prompt
        readline(buffer, STR_LEN);      // read one line from stdin
        idx = 0;                        // set index back

        /* get token */
        token = strtok(buffer, delimiter);
        while (token != NULL) {
            strcpy(&(argstr[idx][0]), token);
            argv[idx] = argstr[idx];
            idx++;
            fprintf(stdout, "token %d = %s\n", idx,token);
            token = strtok(NULL, delimiter);
        }
        /* get output name if is set */
        for (i=0; i<idx; i++) {
            if (strcmp(argv[i], ">") == 0) {
                w_ptr = i + 1;              // set write ptr to the file name
                argv[i] = NULL;             // set < token as last token
                break;
            } else
                w_ptr = 0;                  // no file name found
        }

        /* check if logout or exit */
        if (strcmp(argv[0], "logout") == 0 || strcmp(argv[0], "exit") == 0) {
            exit(0);
        }
        /* check if change directory */
        else if (strcmp(argv[0], "cd") == 0) {            
            if (argv[1] == NULL) {
                /* if no parameter is given, go to root */
                dir = chdir(getenv("HOME"));
            }
//             else if (strcmp(argv[1], "-") == 0) {
//                 dir = chdir(pwd_buf);
//             }
            else {
//                 getcwd(pwd_buf, PWD_LEN);   // get current directory
                dir = chdir(argv[1]);
                switch (dir) {
                    case -1:
                        fprintf(stdout, "\"%s\" is no valid directory\n", argv[1]);
                        break;
                    case 0:
                        break;
                    case ENOENT:
                        printf("dir not found\n");
                        break;
                    default:
                        break;
                }
            }
        }
        else {

            if ((PID = fork()) == 0) {      // fork child process
                /* check if write ptr is set */
                if (w_ptr != 0) {
                    close(1);               // close stdout, redirect to file
                    fdw = open (argv[w_ptr], O_CREAT | O_TRUNC | O_WRONLY, 0644);
                    if (fdw < 0 ){
                        fprintf(stderr, "Could not write to file %s\n", argv[w_ptr]);
                        exit(-1);
                    }
                }
                strcpy(buffer, "/bin/");    // "compose" path of command (1st arg)
                strcat(buffer, argv[0]);
                execv(buffer, &argv[0]);
                strcpy(buffer, "/usr/bin/");
                strcat(buffer, argv[0]);
                execv(buffer, &argv[0]);
                printf("!!! panic !!!\n");
            }
            else if (PID < 0) {
                printf("fork failed\n");    // fork didn't succeed
                exit(-1);                   // terminate sishell
            }
            else                            // here we are parents
                wait(0);                    // wait for child process to terminate
        }
    }
}

