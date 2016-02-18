/******************************************************************************
* File:     WhatsTheTimeMr.cc
* Aufgabe:  Ask MrTimeDaemon for the time
* Autor:    M. Thaler, ZHW
* Datum:    Februar 2000 (Rev. 8/2004)
* History:  29/03/2008 M. Thaler, single connection socket server
*           removed -> (6.1.2002: added GetActualHostName() by M. Pellaton, ZHW,
*           to get hostname by first reading the IP-address
*           form eth0 or eth1, then getting the actual
*           hostname through DNS)
*           
******************************************************************************/

//*****************************************************************************
// system includes
//*****************************************************************************

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <sys/un.h>
#include <netdb.h>
#include <arpa/inet.h>                // required by inet_aton

//*****************************************************************************
// local includes
//*****************************************************************************

#include "TimeDaemon.h"
#include "TimeDaemonDefs.h"
#include "IPsockCom.h"

//*****************************************************************************
// Function:    main()
// Parameter:  hostname or IP address in dot format
//*****************************************************************************

int main(int argc, char *argv[]) {

    char        buffer[COM_BUF_SIZE];
    TimeDataPtr tDataPtr;
    int         j;

    if (argc < 2)  {
        printf("*** need hostname or IP-address of server   ***\n");
        exit(-1);
    }

    strcpy(buffer,REQUEST_STRING);
    j = getTimeFromServer(argv[1], TIME_PORT, buffer, sizeof(buffer));
    if (j < 0)
        printf("no response from %s\n", argv[1]);
    else {
        tDataPtr = (TimeDataPtr)(buffer);
        printf("\nIt's ");
        printf("%d:%d:%d", 
                tDataPtr->hours, tDataPtr->minutes,tDataPtr->seconds);
        printf(" and it's the %d.%d.%d\n\n",
                tDataPtr->day, tDataPtr->month,tDataPtr->year);
    }
    exit(0);
}

//*****************************************************************************

