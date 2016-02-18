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
#include <errno.h>
#include <sys/types.h>
#include <fcntl.h> 
#include <sys/wait.h>
#include <ctype.h>
#include <curses.h>

#include "char_handling.h"

/******************************************************************************/
/* Definitions */
/******************************************************************************/
#define MAX_argv    16                  // max number of command line arguments
#define STR_LEN     32                  // max length of command line arguments
#define PWD_LEN     50                  // max length of pwd name

/******************************************************************************/
/* private functions*/
/******************************************************************************/
/**
 * exit_logout() - Function to exit the miShell
 * @argv:       Ptr to the token array
 */
static void exit_logout(char *argv[])
{
    /* check if logout or exit */
    if (strcmp(argv[0], "logout") == 0)
        exit(0);
    if (strcmp(argv[0], "exit") == 0)
        exit(0);
}

/******************************************************************************/
/**
 * cd_cmd() - Function to change the directory
 * @argv:       Ptr to the token array
 * @pwd:        Ptr to the current directory path
 * @ret:        return value, 0 if dir has changed, 1 if no change is done
 */
static int cd_cmd(char *argv[], char *pwd)
{
    int ret;
    
    if (strcmp(argv[0], "cd") == 0) {
        if (argv[1] == NULL) {
            /* if no parameter is given, go to root */
            ret = chdir(getenv("HOME"));
        }
        else if (strcmp(argv[1], "-") == 0) {
            ret = chdir(pwd);
        }
        /* goto path */
        else {
            getcwd(pwd, PWD_LEN);   // get current directory
            ret = chdir(argv[1]);

            /* error handling */
            switch (ret) {
                case -1:
                    fprintf(stdout, "\"%s\" is no valid path\n", argv[1]);
                    break;
                case 0:             // success
                    break;
                case ENOENT:
                    printf("dir not found\n");
                    break;
                default:
                    break;
            }
        }
    }
    else
        return 1;
    return 0;
}

/******************************************************************************/
/** get_output_name() - Function to get the output file name
 * @argv:       Ptr to the token array
 * @max_args:   Size of tokens
 * @fname_ptr:  returns ptr to the file name
 */
static char * get_output_name(char *argv[], int max_args)
{
    int i;
    char *fname_ptr;
    
    for (i=0; i<max_args; i++) {
        if (strcmp(argv[i], ">") == 0) {
            fname_ptr = argv[i+1];
            argv[i] = NULL;             // set < token as last token
            break;
        }
    }
    return fname_ptr;
}

/******************************************************************************/
/* main */
/******************************************************************************/
int main(void) {
    char argstr[MAX_argv][STR_LEN];     // storage for command line arguments
    char *argv[MAX_argv];               // ptr array to command line arguments
    char *token;                        // ptr to command line token
    char buffer[STR_LEN];               // character buffer for command line
    char delimiter[] = " |\n\t";        // delimiter for the commands
    int idx;                            // index variable
    pid_t PID;                          // process identifier
    int fdw;                            // write file descriptor
    int ret;                            // ret value
    char pwd_buffer[PWD_LEN];
    char *fname_ptr = NULL;             // ptr to the output file name

    /* init curses */
    inti_curses();
    
    /* get current directory as default */
    getcwd(pwd_buffer, PWD_LEN);
    
    while (1) {
        printw("# ");                   // set prompt
        readline(buffer, STR_LEN);      // read one line from stdin
        idx = 0;                        // set index back

        /* get token */
        token = strtok(buffer, delimiter);
        while (token != NULL) {
            strcpy(&(argstr[idx][0]), token);
            argv[idx] = argstr[idx];
            idx++;
            token = strtok(NULL, delimiter);
        }
        argv[idx] = NULL;               // terminate arguments with NULL pointer

        /* get output name if is set */
        fname_ptr = get_output_name(argv, idx);

        /* check if logout or exit */
        exit_logout(argv);
        
        /* check if cd */
        ret = cd_cmd(argv, pwd_buffer);

        /* execute command */
        if (ret) {
            if ((PID = fork()) == 0) {      // fork child process
                /* check if write ptr is set */
                if (fname_ptr != NULL) {
                    close(1);               // close stdout, redirect to file
                    fdw = open (fname_ptr, O_CREAT | O_TRUNC | O_WRONLY, 0644);
                    if (fdw < 0 ){
                        fprintf(stderr, "Could not write to file %s\n", fname_ptr);
                        exit(-1);
                    }
                }
                strcpy(buffer, "/bin/");    // "compose" path of command (1st arg)
                strcat(buffer, argv[0]);
                execv(buffer, &argv[0]);
                strcpy(buffer, "/usr/bin/");
                strcat(buffer, argv[0]);
                execv(buffer, &argv[0]);
                printf("%s: command not found\n", argv[0]);
                exit(0);                    // kill process
            }
            else if (PID < 0) {
                printf("fork failed\n");    // fork didn't succeed
                exit(-1);                   // terminate sishell
            }
            else                            // here we are parents
                wait(0);                    // wait for child process to terminate
        }
        refresh();
    }
}

