/******************************************************************************
* ParaModule.c
* 27.08.2004 tha: Kernel 2.6
* 10.02.2008 tha: changed to module_param
******************************************************************************/

#include <linux/module.h>
#include <linux/moduleparam.h>

int globalInt    = 10;
char* globalChar = "default text";

module_param(globalInt,  int,   S_IRUGO);
module_param(globalChar, charp, S_IRUGO);

int init_module(void) {
    printk("<0>*** ParaModule: %d - %s ***\n", globalInt, globalChar);
	return(0);
}

void cleanup_module(void) {
    printk("<0>*** Good Bye from ParaModule ***\n");
}

/******************************************************************************/
