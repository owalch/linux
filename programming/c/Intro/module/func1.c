/* Beispiel:   Modulare Programmierung in C und C++,
   File:       "func1.cc"  
   Fach:       Betriebssysteme, ZHW, J. Zeman, Sept. 99 
   In dieser Datei wird die Funktion "Flaeche" ausprogrammiert.
*/

#include "mydefs.h"
#include "func1.h"

my_float flaeche(my_float radius)
{
   return (my_pi * radius * radius);
}
