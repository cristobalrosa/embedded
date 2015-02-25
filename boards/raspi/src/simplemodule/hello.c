#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Cristobal Rosa <cristobalrosa@gmail.com>");
MODULE_DESCRIPTION("A simple module to test my cross-compile environment");


static int __init hello_init(void)
{
    printk(KERN_ALERT "Hello from the raspi world\n");
    return 0;
}
static  void __exit hello_exit(void)
{
    printk(KERN_ALERT "Bye bye, have fun!\n");

}

module_init(hello_init);
module_exit(hello_exit);

