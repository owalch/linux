/*
   Beispiel:   Modulare Programmierung in C (und C++), 
   File:      "main.cc"  (Hauptprogr. mit Headerdateien der ext. Module)
   Fach:       Betriebssysteme, ZHW, J. Zeman, Sept. 99 
*/

#include <iostream>
using namespace std;

#include "mydefs.h"   /* Headerdatei fuer ext. Modul mit eigenen typen und Konst */
#include "func1.h"    /* Headerdatei fuer ext. Modul func1.cpp */
#include "func2.h"    /* Headerdatei fuer ext. Modul func2.cpp */

/* ..... Funktionsprototypen: (lokale Funktionen in diesem Modul) */


void eingabe(my_float &x);

/* ......Hauptprogramm ............ */
int main(void) 
{
   my_float r ;

   eingabe(r);          /* r ist als Referenzparameter deklariert ! */
   cout << "\n\n Kreisberechnung" ;
   cout << "\n berechnet mit phi= "<< 3.14;  /* aus dem ext. Modul mytypes.f */
   cout << "\n Radius= "<< r <<" -> Flaeche= "<< flaeche(r);
   cout << ", Umfang= " << umfang(r) << endl;
   cin >> r;           /* dummy input -> warte hier */
}

void eingabe(my_float &x)    /* cpp: Referenz-parameter ! */
{
   cout << "\n Kreisberechnung; Radius =?";
   cin >> x;
}

