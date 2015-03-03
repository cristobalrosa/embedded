// Simple character device. This code could help as an skeleton for future drivers.
#include <linux/module.h>
#include <linux/init.h>
#include <linux/fs.h> // Character device support

#define DEVICE_NAME "simchar"

int major = 200;//static major number
int ret; // variable to handle return values

static int simchar_open(struct inode *pinode, struct file *pfile)
{
    printk(KERN_ALERT "Simchar open..\n");
    return 0;
}

static size_t  simchar_read(struct file *pfile, char __user *buffer,  size_t length, loff_t *offset)
{
    printk(KERN_ALERT "Simchar read..\n");
    return 0;

}
static size_t  simchar_write(struct file *pfile, const char __user *buffer, size_t length, loff_t *offset)
{
    printk(KERN_ALERT "Simchar write..\n");
    return length;

}
static int simchar_close(struct inode *pinode, struct file *pfile)
{
    printk(KERN_ALERT "Simchar close..\n");
    return 0;
}


static struct file_operations simchar_fops = {
    .owner   = THIS_MODULE,
    .open    = simchar_open,
    .read    = simchar_read,
    .write   = simchar_write,
    .release = simchar_close
};

static int __init simchar_init(void)
{

    // register the driver
    // register_chrdev (major, device name, file operations
    // This is the older way to register a device. Starting from kernel 2.6, there
    // is a better approach that we will discuss it later.
    ret = register_chrdev(major, DEVICE_NAME, &simchar_fops);

    if( ret < 0 )
    {
        printk(KERN_ALERT "Cannot register the device");
        return ret;
    }
    printk(KERN_ALERT "Simchar registered...");
    return 0;
}

static void __exit simchar_exit(void)
{
    unregister_chrdev(major, DEVICE_NAME);
    printk(KERN_ALERT "Simchar exit...");
}


module_init(simchar_init);
module_exit(simchar_exit);
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Cristobal Rosa <cristobalrosa@gmail.com>");
MODULE_DESCRIPTION("Simple character device");

