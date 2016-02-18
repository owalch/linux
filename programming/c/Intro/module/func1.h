#ifndef FUNC1    /* Standard-Konstruktion, um eine mehrfache */
#define FUNC1    /* Deklaration zu unterbinden   */

/* 
   Beispiel:   Modulare Programmierung in C und C++,
   File:      "func1.h"
   Fach:       Betriebssysteme, ZHW, J. Zeman, Sept. 99 

   Diese Datei enthaelt die Deklarationen der Funktionen, welche
   aus dem Modul func1.c exportiert werden (hier die Funktion "Flaeche")
   Sie muss wird in beide Module mit der "include-Anweisung" eingebunden:
      a) das Modul "main.c", in welchem die Funktionen verwendet (importiert) wird
             und
      b) das Modul "func1.c", in welchem die Funktionen ausprogrammiert ist (export)
   Damit kann die Parametertypenueberpruefung auch bei separater 
   Modulkompilation gewaehrleistet werden !
*/


#include "mydefs.h"

   extern my_float flaeche(my_float);


#endif
