/*********************************************************************
* File:     MrTimeDaemon.cc
* Aufgabe:  einen Daemon-Prozess erzeugen
* Autor:    M. Thaler
* Datum:    Februar 2000, 3/2008
*********************************************************************/

#include <stdio.h>

#include "Daemonizer.h"
#include "TimeDaemon.h"

//--------------------------------------------------------------------

int main(void) {
    
    const char *lockfilePath = "/tmp/timeDaemon.lock";
    const char *logfilePath = "/tmp/timeDaemon.log";
    const char *livingPath = "/tmp";
    const char *MyName = "I am Mr. Time Daemon\n";
        
    Daemonizer(TimeDaemon, (void *)MyName, 
                NULL, logfilePath, livingPath);
}

//--------------------------------------------------------------------
