include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Patrick Lindborg <lindborg@gmail.com>");
MODULE_DESCRIPTION("Kernel leetspeak");
static unsigned long buffer_size = 8192;
module_param(buffer_size, ulong, (S_IRUSE | S_IRGRP | S_IROTH));


static int __init leet_init(void)
{
	if(!buffer_size)
	{
		return -1;
	}
	printk(KERN_INFO "leet device has been registered, buffer size is %lu bytes\n",buffer_size);
	return 0;
}

static void __exit leet_exit(void)
{
	printk(KERN_INFO "leet device has been unregistered\n")
}

module_init(leet_init);
module_exit(leet_exit);
