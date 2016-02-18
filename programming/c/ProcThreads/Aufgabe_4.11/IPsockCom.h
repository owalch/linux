//***************************************************************************
// ipCom.h: IP Socket Functions
// Author:  M. Thaler, ZHW
// Date:    11.2.2000
// History:	29/03/2008 M. Thaler: single connection socket server
//***************************************************************************

#ifndef IP_COM_SOCKETS
#define IP_COM_SOCKETS

#define COM_BUF_SIZE 512

#define PIDperror()\
	 fprintf(stderr,"fatal error, daemon with PID %d: ",getpid());

int getTimeFromServer(char *host, int port, char *buffer, int bufferLen);
int StartTimeServer(int PortNumber);
int WaitForClient(int sfd, char *buffer);

#endif

//***************************************************************************
