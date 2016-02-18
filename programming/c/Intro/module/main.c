/*******************************************************************************
* Beispiel:   Modulare Programmierung in C (und C++), 
* File:      "main.cc"  (Hauptprogr. mit Headerdateien der ext. Module)
* Fach:       Betriebssysteme, ZHW, J. Zeman, Sept. 99 
* Update:     ZHAW, M. Thaler, Jan 2011
*******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include "mydefs.h"     /* Headerdatei mit eigenen Typen und Konstante */
#include "func1.h"      /* Headerdatei fuer externes Modul func1.cpp   */
#include "func2.h"      /* Headerdatei fuer externes Modul func2.cpp   */
#include "func3.h"      /* header for the sphere calculation */


/*----------------------------------------------------------------------------*/
/* Funktionsprototypen: (lokale Funktionen in diesem Modul) */

void eingabe(my_float *x);

/*----------------------------------------------------------------------------*/
/* Hauptprogramm                                                              */

int main(void) 
{
    my_float R, F, U, V;

    eingabe(&R);
    printf("\n\n Kreisberechnung");
    printf(" (berechnet mit pi = %lf)\n", my_pi);  /* aus mydefs.h */
    F = flaeche(R);
    U = umfang(R);
    V = kugelvolumen(R);
    printf("\n Radius =\t%lf \n Flaeche =\t%lf \n Umfang =\t%lf\n Volumen = \t%lf\n", R , F, U, V);
    getchar(); getchar();                       /* dummy input -> warte hier */

    exit(0);
}

/*----------------------------------------------------------------------------*/
/* lokale Funktion                                                            */

void eingabe(my_float *x)
{
    printf("\n Kreisberechnung; Radius = ? ");
    scanf("%lf", x);
}

/*----------------------------------------------------------------------------*/
