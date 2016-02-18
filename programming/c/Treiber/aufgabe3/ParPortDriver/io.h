#ifndef REDEFINITION_IO_OPERATIONS
#define REDEFINITION_IO_OPERATIONS

extern void outbEmul(char byte, int addr);
extern char inbEmul(int addr);

#define inb_p inb
#define outb_p outb
#define inb(x) inbEmul(x)
#define outb(x,y) outbEmul(x,y)

/* ignore the following functions */

#define request_region(x, y, z) (struct resource *)1
#define check_region(x, y, z)   (struct resource *)1
#define release_region(x, y)    {}


#endif
