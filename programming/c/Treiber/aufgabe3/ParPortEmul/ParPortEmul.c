/**************************************************************************
*
* Parallel port emulator
* Author:   M. Thaler
* File:     ParPortEmul.c
* Version:  2/2009
* Changes:  1/2011 M. Thaler
*           - removed autoconf.h
***************************************************************************/

#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/slab.h>
#include <linux/fs.h>
#include <asm/uaccess.h>
#include <asm/system.h>
#include <asm/io.h>

MODULE_LICENSE("GPL");

/*-----------------------------------------------------------------------*/
/* export global functions to kernel symbol table                        */

void outbEmul(char data, int addr);
char inbEmul(int addr);

EXPORT_SYMBOL_GPL(outbEmul);
EXPORT_SYMBOL_GPL(inbEmul);

/*-----------------------------------------------------------------------*/
/* global variables */

static char dataPort[3] = {0,0,0};            /* output register         */
static char statPort[3] = {0,0,0};            /* status register         */
static char cntlPort[3] = {0,0,0};            /* control register        */

//static int  lpDeviceNumber = 0;            /* lp0, lp1, lp2 */

static int  use_count[3] = {0,0,0};

/*-----------------------------------------------------------------------*/

#define THIS_MAJOR 126        /* experimental THIS_MAJOR: 120 - 127      */

int     ParPortEmulOpen(struct inode*, struct file*);
int     ParPortEmulRelease(struct inode*, struct file*);
ssize_t ParPortEmulRead(struct file *filp, char *buf, 
                                        size_t count, loff_t *anything);
ssize_t ParPortEmulWrite(struct file *filp, const char *buf, 
                                        size_t count, loff_t *anything);

/*-----------------------------------------------------------------------*/
/* using struct intializer (C99 and GNU) -> portable */

struct file_operations ParPortEmulFops = {
  .owner=   THIS_MODULE,
  .open=    ParPortEmulOpen,
  .release= ParPortEmulRelease,
  .read=    ParPortEmulRead,
  .write=   ParPortEmulWrite,
};

/*-----------------------------------------------------------------------*/
/* retrieve minor number from file                                        */

int getMINOR(struct file *fp) {
    int    minor;
    struct inode *inodePtr;
    inodePtr = fp->f_dentry->d_inode;
    minor = MINOR(inodePtr->i_rdev);
    return(minor);
}

/*-----------------------------------------------------------------------*/
/* initialize and register module                                        */

int init_module(void) {
    int res;
    use_count[0] = use_count[1] = use_count[2] = 0;
    res = register_chrdev(THIS_MAJOR, "ParPortEmulModul", &ParPortEmulFops);
    if (res < 0)
        printk("<0>cannot register parallel port emulator");
    else
        printk("<0>parallel port emulator loaded\n");
    return(res);
}

void cleanup_module(void) {
    unregister_chrdev(THIS_MAJOR, "ParPortEmulModul");
    printk("<0>parallel port emulator successfully unloaded\n");
}

/*--------------------------------------------------------------------------*/
/* open()                                                                   */

int ParPortEmulOpen(struct inode *inode, struct file *filp) {

    int minor;

    minor = getMINOR(filp);

    if ((minor < 0) || (minor > 2))
        return(-1);
    
    if (use_count[minor] != 0)           /* check if not already in use     */
        return(-EBUSY);                  /* if yes return with error        */
    else
        use_count[minor]++;

    if (try_module_get(THIS_MODULE) == 0) /* check if module is loaded      */
        return(-1);

    return(0);
}

/*--------------------------------------------------------------------------*/
/* close()                                                                  */

int ParPortEmulRelease(struct inode *inode, struct file *filp) {
    int minor;
    module_put(THIS_MODULE);           /* release module                    */
    minor = getMINOR(filp);
    if (use_count[minor] > 0) {
        use_count[minor]--;
    }
    return(0);
}

/*--------------------------------------------------------------------------*/
/* read()                                                                   */

ssize_t ParPortEmulRead(struct file *filp, char *buf, 
                                            size_t count, loff_t *offset) {
    int  minor;
    long rv;
    size_t lcount;
    char test[2];
    minor = getMINOR(filp);
    test[0] = (char)dataPort[minor];
    test[1] = (char)cntlPort[minor];
    lcount = 2;
    rv = copy_to_user(buf, test, lcount);
    return(lcount);
}

/*--------------------------------------------------------------------------*/
/* write()                                                                  */

ssize_t ParPortEmulWrite(struct file *filp, const char *buf, 
                                            size_t count, loff_t *offset) {
    int  minor;
    long rv;
    char test[1];
    minor = getMINOR(filp);
    rv = copy_from_user(test, buf, count);
    statPort[minor] = (char)test[0]^0x80;            /* invert MSB */
    return(count);
}

/*--------------------------------------------------------------------------*/
/* emulate outb() resp. outb_p() @ lp0, lp1 and lp2                         */

void outbEmul(char data, int addr) {
    switch (addr) {
        case 0x3BC:    dataPort[0] = data;
                    break;
        case 0x3BE:    cntlPort[0] = (data ^ 0x0B) & 0x0F; 
                    break;
        case 0x378:    dataPort[1] = data;
                    break;
        case 0x37A:    cntlPort[1] = (data ^ 0x0B) & 0x0F; 
                    break;
        case 0x278:    dataPort[2] = data;
                    break;
        case 0x27A:    cntlPort[2] = (data ^ 0x0B) & 0x0F; 
                    break;
        default:    break;
    }
}
    
/*--------------------------------------------------------------------------*/
/* emulate inb() resp. inb_p() @ lp0, lp1 and lp2                           */

char inbEmul(int addr) {
    char data = 0;
    switch (addr) {
        case 0x3BD:    data = statPort[0];
                    break;
        case 0x379:    data = statPort[1];
                    break;
        case 0x279:    data = statPort[2];
                    break;
        default:    break;
    }
    return(data);        
}

/*--------------------------------------------------------------------------*/
