/**
 * @brief	This module implements a simple UDP socket listener.
 * @author	Oliver Walch
 * @date	2016-03-02
 */

#include "udp_socket.h"

#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>

/**
 * @brief	Main function
 */
int main(int argc, char *argv[])
{
	struct sockaddr_in own_addr;			// Own address
	struct sockaddr_in rem_addr;			// Remote address
	int rx_pkt_len;							// # bytes received
	int fd;									// Own socket
	int rc;									// Bind ret value
	socklen_t addr_len = sizeof(rem_addr);	// Address length
	unsigned char rx_buf[BUFSIZE];			// Receive buffer

	/* Create a new socket */
	if ((fd = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
	{
		perror("Cannot create socket\n");
		return 0;
	}

	/* Bind socket */
	memset((char *)&own_addr, 0, sizeof(own_addr));
	own_addr.sin_family			= AF_INET;
	own_addr.sin_addr.s_addr	= htonl(INADDR_ANY);
	own_addr.sin_port			= htons(UDP_PORT);
	if ((rc = bind(fd, (struct sockaddr *)&own_addr, sizeof(own_addr))) < 0)
	{
		perror("Socket binding failed");
		return 0;
	}

	// Netdebug print
	printf(":: Netdebug waiting for data UDP port %d ::\n", UDP_PORT);

	/* Receive and print data */
	while (1)
	{
		rx_pkt_len = recvfrom(fd, rx_buf, BUFSIZE, 0, (struct sockaddr *)&rem_addr, &addr_len);
		if (rx_pkt_len > 0)
		{
			rx_buf[rx_pkt_len] = 0;
			printf("%s\n", rx_buf);
		}
	}
	return 0;
}
