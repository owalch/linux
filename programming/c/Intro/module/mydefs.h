#ifndef _MYDEFS    /* Standard-Konstruktion, um eine mehrfache */
#define _MYDEFS    /* Deklaration zu unterbinden   */
/* 
   Beispiel:   Modulare Programmierung in C und C++, 
   File:      "mydefs.h"  
   Fach:       Betriebssysteme, ZHW, J. Zeman, Sept. 99 

   Diese Datei enthaelt die Deklarationen von eigenen Typen und Konstanten,
   welche in mehreren Programmmodulen benoetigt werden.
   Die zentrale Verwaltung solcher Programmbestandteile
   vereinfacht die Aenderungen am Programm.

   Diese Datei wird in allen Source-Code-Modulen, die sie ben÷tigen, 
   mit der "include-Anweisung" eingebunden:
      -> main.c, func1.c, func2.c und 
         (sicherheitshalber)auch in func1.h, func2.h
*/

/* externe Typen, Konstanten, Macros und globale Variablen-Deklarationen */

#include "/usr/include/math.h"



   typedef double my_float;

#define my_pi M_PI

#endif
