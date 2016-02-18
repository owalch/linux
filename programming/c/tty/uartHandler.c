#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <termios.h>
#include <sys/ioctl.h>

/*
 * local header declarations
 */
int uarthandler_init(void);
int uarthandler_config(int fd);
int uarthandler_read(int fd, char *result);
int uarthandler_write(int fd, char *chars);
int uarthandler_getBaud(int fd);

/*
 * globals
 */
char sBuf[254];

/*
 * main(): main function
 */
int main (int argc, char *argv[])
{
    int fd;
    fd = uarthandler_init();                      // set serial device
    fcntl(fd, F_SETFL, O_NONBLOCK);         // nonblocking serial read
    /* main loop */
    char msg[] = "hello world";
    uarthandler_write(fd, msg);
    while(1)
    {
        int bytes;
        ioctl(fd, FIONREAD, &bytes);        // number of data bytes
        if (bytes != 0)                     // && bytes > 1/2 buffer -> performance
        {
            sBuf[0] = 0x00;
            if (uarthandler_read(fd,sBuf))
            {
                int sBuf_length = strlen(sBuf);
                printf("msg(%d)\t: %s\n",sBuf_length,sBuf);
            }
        }
    }
    close(fd);
    return 0;
}
/*
 * uarthandler_init(): config UART
 */
int uarthandler_init(void)
{
    int fd = open("/dev/ttyS0", O_RDWR | O_NOCTTY | O_NDELAY);
    if (fd == -1)
    {
        perror("open_port: Unable to open /dev/ttyS0 - ");
        return 1;
    } else
    {
        fcntl(fd, F_SETFL, 0);
        printf("Serial connection established on /dev/ttyS0\n");
    }
    printf("Default baud\t= %d\n", uarthandler_getBaud(fd));
    uarthandler_config(fd);
    printf("Conifgured baud\t= %d\n", uarthandler_getBaud(fd));

    return fd;                               // success
}

/*
 * uarthandler_config() : Configure terminal interface
 */
int uarthandler_config(int fd)
{
    struct termios options;
    tcgetattr(fd, &options);                // get the current parameters
    cfsetispeed(&options, B115200);         // set input baud rate
    cfsetospeed(&options, B115200);         // set output baud rate
    /* set control mode */
    options.c_cflag |= (CLOCAL | CREAD);    // ignore modem control lines, enable receiver
    options.c_cflag &= ~PARENB;             // enable parity generation on output and parity checking for input
    options.c_cflag &= ~CSTOPB;             // set two stop bits, rather than one
    options.c_cflag &= ~CSIZE;              // Character size mask
    options.c_cflag |= CS8;
    tcsetattr(fd, TCSANOW, &options);       // set the above parameters
    return 1;
}

int uarthandler_write(int fd, char *chars)
{
    int len = strlen(chars);
    chars[len] = 0x0d;                      // ASCII CR after command
    chars[len+1] = 0x00;                    // terminate with Null
    int n = write(fd, chars, strlen(chars));
    if (n < 0)
    {
        fputs("write failed!\n", stderr);
        return 0;
    }
    return 1;
}

/*
 * uarthandler_read() : Read serial device
 */
int uarthandler_read(int fd, char *result)
{
    int n = read(fd, result, 254);
    result[n-1] = 0x00;                     // terminate with Null
    if (n < 0)
    {
        if (errno == EAGAIN) { return 1; }  // try again
        else
        {
            printf("SERIAL read error %d %s\n", errno, strerror(errno));
            return 0;
        }
    }
    return 1;                               // success
}

/*
 * uarthandler_getBaud(): Function to get the Baud rate
 */
int uarthandler_getBaud(int fd)
{
    struct termios termAttr;
    int inRate = -1;
    speed_t baudRate;
    tcgetattr(fd, &termAttr);
    baudRate = cfgetispeed(&termAttr);      //get the input speed
    switch (baudRate)
    {
        case B0:      inRate = 0; break;
        case B50:     inRate = 50; break;
        case B110:    inRate = 110; break;
        case B134:    inRate = 134; break;
        case B150:    inRate = 150; break;
        case B200:    inRate = 200; break;
        case B300:    inRate = 300; break;
        case B600:    inRate = 600; break;
        case B1200:   inRate = 1200; break;
        case B1800:   inRate = 1800; break;
        case B2400:   inRate = 2400; break;
        case B4800:   inRate = 4800; break;
        case B9600:   inRate = 9600; break;
        case B19200:  inRate = 19200; break;
        case B38400:  inRate = 38400; break;
        case B115200: inRate = 115200; break;
    }
    return inRate;
}
