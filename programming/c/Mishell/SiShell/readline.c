/******************************************************************************
//  File:       readline.c
//  Fach:       Betriebssysteme
//  Autor:      M. Thaler, 2/2010
//  Modified:   O. Walch, 3/2012
******************************************************************************/
#include <stdio.h>
#include <string.h>


/**
 * readline() - Reads at most count characters from stdin into the buffer buf
 * @buf:        Buffer for the whole command
 * @count:      Size of the buffer
 */
int readline(char *buf, int count) {

    char ch;                                    /* char buffer */
    int i = 0;                                  /* character counter */

    memset(buf,0, count);
    while ((ch = getchar()) != EOF && ch != '\n' && i < count-1) {
        buf[i] = ch;
        i++;
    }
    buf[i] = '\0';

    return i;
}

