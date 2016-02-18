/**************************************************************************
* Parport Device Driver
* 
* Author:		M. Thaler, A. Schmid
* File:			ParDriver.c
* Grundversion:	17.9.1999	A. Schmid
* Erweiterung, 
* Anpassungen:	25.11.2001	M. Thaler
*				27.08.2004	M. Thaler	-->> Kernel 2.6
*				- slab.h
*				- use_count: global variable
*				- include files adapated
*               18.02.2009  M. Thaler
*               - include "io.h" for par port emulation
*               20.01.2011  M. Thaler
*               - removed autoconf.h
***************************************************************************/

#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/slab.h>
#include <linux/fs.h>
#include <asm/uaccess.h>
#include <asm/system.h>
#include <asm/io.h>         // comment, when using with parallel port emulation

//#include "io.h"           // uncomment to use with parallel port emulation

MODULE_LICENSE("GPL");

/*---------------------------------------------------------------------------*/
int use_count;
/*---------------------------------------------------------------------------*/

#define BASE_ADDR 0x378		/* IO base addr of lp1 */

#define MY_MAJOR 121		/* experimental MAJOR: 120 - 127*/

int 	ParOpen(struct inode*, struct file*);
int 	ParRelease(struct inode*, struct file*);
ssize_t ParRead(struct file *filp, char *buf, size_t count, loff_t *anything);
ssize_t ParWrite(struct file *filp, const char *buf, 
                                            size_t count, loff_t *anything);

/*---------------------------------------------------------------------------*/

/* using the tagged method -> portable */

struct file_operations ParFops = {
  .open=	ParOpen,
  .release=	ParRelease,
  .read=	ParRead,
  .write=	ParWrite,
};

/*---------------------------------------------------------------------------*/

int init_module(void) {

}

void cleanup_module(void) {

}

/*---------------------------------------------------------------------------*/

int ParOpen(struct inode *inode, struct file *filp) {

}

int ParRelease(struct inode *inode, struct file *filp) {

}

ssize_t ParRead(struct file *filp, char *buf, size_t count, loff_t *offset) {

}

ssize_t ParWrite(struct file *filp, const char *buf, 

}

/*****************************************************************************/
