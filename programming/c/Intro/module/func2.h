#ifndef _FUNC2    /* Standard-Konstruktion, eine mehrfache */
#define _FUNC2    /* Deklaration zu unterbinden   */
/* 
   Beispiel:   Modulare Programmierung in C und C++, 
   File:      "func2.h"  
   Fach:       Betriebssysteme, ZHW, J. Zeman, Sept. 99 

   Diese Datei enthaelt die Deklarationen der Funktionen, welche
   aus dem Modul func2.c exportiert werden (hier die Funktion "Umfang")
   Sie muss wird in beide Module mit der "include-Anweisung" eingebunden:
      a) das Modul "main.c", in welchem die Funktionen verwendet (importiert) wird
             und
      b) das Modul "func2.c", in welchem die Funktionen ausprogrammiert ist (export)
   Damit kann die Parametertypenueberpruefung auch bei separater 
   Modulkompilation gewaehrleistet werden !
*/

#include "mydefs.h"

   extern my_float umfang(my_float);


#endif
