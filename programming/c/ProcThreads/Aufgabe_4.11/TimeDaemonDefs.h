/******************************************************************************
* File:		TimeDaemonDefs.h
* Aufgabe:	Data Definitions for TimeDaemon
* Autor:	M. Thaler, ZHW
* Datum:	Februar 2000
* History:	29/03/2008 M. Thaler: single connection socket server
******************************************************************************/

#ifndef TIME_DAEMON_DEFS
#define TIME_DAEMON_DEFS

#define HOST_NAM_LEN 32

#define TIME_PORT 65534

#define REQUEST_STRING  "requestTimeFromServer"

// data structure receiving from time daemon

typedef struct {
	int	hours;
	int	minutes;
	int seconds;
	int	day;
	int	month;
	int year;
} TimeData, *TimeDataPtr;

#endif

//*****************************************************************************
