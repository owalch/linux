/******************************************************************************
//  File:       char_handling.c
//  Fach:       BSy
//  Autor:      O. Walch, 3/2012
******************************************************************************/
#include <stdio.h>
#include <string.h>
#include <curses.h>                     // LDFLAGS = -lncurses


void inti_curses(void)
{
    initscr();                          /* Set curses mode*/
    raw();
    keypad(stdscr, TRUE);
    echo();
}


/**
 * readline() - Reads at most count characters from stdin into the buffer buf
 * @buf:        Buffer for the whole command
 * @count:      Size of the buffer
 * @return:     Size of detected chars
 */
int readline(char *buf, int count) {

    int ch;
    int i = 0;                                  /* character counter */
    memset(buf,0, count);
    while ((ch = getch()) != EOF && ch != '\n' && i < count-1) {
        buf[i] = ch;
        i++;
    }
    buf[i] = '\0';

    return i;
}

