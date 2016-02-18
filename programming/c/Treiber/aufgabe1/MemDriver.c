/*************************************************************************
* Memory Device Driver (Aufgabe 1)
* 
* Author:       M. Thaler, A. Schmid
* File:         MemDriver.c
* Grundversion: 17.9.1999    A. Schmid
* Erweiterung, 
* Anpassungen:  25.11.2001    M. Thaler
*               27.08.2004    M. Thaler    -->> Kernel 2.6
*                - slab.h
*                - deviceOpen: handles number of opens
*                - include files adapated
*               14.02.2010  M. Thaler
*                - try_moudle_get/module_put: new USE_COUNT
*               20.01.2011  M. Thaler
*                - autoconf.h removed
***************************************************************************/

#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/slab.h>
#include <linux/fs.h>
#include <asm/uaccess.h>
#include <asm/system.h>

#include "MemDriver.h"

MODULE_LICENSE("GPL");

/*-----------------------------------------------------------------------*/
/* using struct intialization of C99 (and GNU) -> portable               */

static struct file_operations MemFops = {
  .owner    = THIS_MODULE,
  .open     = MemOpen,
  .release  = MemRelease,
  .read     = MemRead,
  .write    = MemWrite,
};

static DataBuffer DatBuf = {
    0,
    NULL,
};

static int deviceOpen = 0;

/*-----------------------------------------------------------------------*/

int init_module(void) {
    int res;
    printk("<0>Hello from Module\n");
    deviceOpen = 0;
    res = register_chrdev(MY_MAJOR, "MemDriver", &MemFops);
    if (res < 0)
        printk("<0>cannot register MemDriver");
    return(res);
}

void cleanup_module(void) {
    printk("<0>bye bye\n");
    if (DatBuf.buffer != NULL)
        kfree(DatBuf.buffer);
    unregister_chrdev(MY_MAJOR, "MemDriver");
}

/*-----------------------------------------------------------------------*/

int MemOpen(struct inode *inode, struct file *filp) {
    printk("<1>we are in the OPEN\n");
    if (deviceOpen != 0)                /* check if not already in use */
        return(-EBUSY);                 /* if yes return with error    */
    else
        deviceOpen++;
    filp->private_data = &DatBuf;
    if (try_module_get(THIS_MODULE) == 0)
        return(-1);
    return(0);
}

int MemRelease(struct inode *inode, struct file *filp) {
    printk("<1>we are in RELEASE\n");
    deviceOpen--;
    module_put(THIS_MODULE);
    return(0);
}

ssize_t MemRead(struct file *filp, char *buf, size_t count, loff_t *offset) {
    size_t lcount;
    DataBuffer *mem;
    printk("<1>we are in the READ\n");    
    mem = filp->private_data;
    if (count > mem->length)
        lcount = mem->length;
    else
        lcount = count;
    if (copy_to_user(buf, mem->buffer, lcount) != 0)
        lcount = -1;
    return(lcount);
}

ssize_t MemWrite(struct file *filp, const char *buf, size_t count, loff_t *offset) {
    DataBuffer *mem;
    printk("<1>we are in the WRITE");
    mem = filp->private_data;
    kfree(mem->buffer);
    mem->buffer = (void *)kmalloc(count, GFP_KERNEL);
    if (mem->buffer == NULL) {
        printk("<0> could not allocate kernel memory\n");
        return(-ENOMEM);
    }
    mem->length = count;
    if (copy_from_user(mem->buffer, buf, count) != 0)
        count = -1;
    return(count);
}

/**************************************************************************/
