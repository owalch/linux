/******************************************************************************
* Hello World Module 
* HelloWorld.c
* 27.8.2004, tha: kernel 2.6
* 20.1.2012, tha: autoconf.h removed
******************************************************************************/

#include <linux/kernel.h>
#include <linux/module.h>

MODULE_LICENSE("GPL");

int init_module(void) {
    printk("<0>*** Hello World from Module ***\n");
	return(0);
}

void cleanup_module(void) {
    printk("<0>*** Good Bye from Module ***\n");
}

/*****************************************************************************/
