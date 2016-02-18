/* Beispiel:   Modulare Programmierung in C und C++,
   File:       "func2.cc"  
   Fach:       Betriebssysteme, ZHW, J. Zeman, Sept. 99 

   In dieser Datei wird die Funktion "Umfang" ausprogrammiert.
*/

#include "mydefs.h"
#include "func2.h"

my_float umfang(my_float radius)
{
   return (2 * my_pi * radius);
}
