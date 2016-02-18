/*********************************************************************
* File:     PlapperMaul.cc
* Aufgabe:  plappern
* Autor:    M. Thaler
* Datum:    Februar 2000 (Rev. 8/2004)
*********************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

//--------------------------------------------------------------------

int main(void) {
    
    while (1) {
        printf("Hallo, ich bins....  Pidi %d\n", getpid());
        usleep(500000);
    }
}

//--------------------------------------------------------------------
