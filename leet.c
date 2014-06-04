#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/miscdevice.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Patrick Lindborg <lindborg@gmail.com>");
MODULE_DESCRIPTION("Kernel leetspeak");
static unsigned long buffer_size = 8192;
module_param(buffer_size, ulong, (S_IRUSR | S_IRGRP | S_IROTH));
MODULE_PARM_DESC(buffer_size, "Internal buffer size");

static struct miscdevice leet_misc_device = {
	.minor = MISC_DYNAMIC_MINOR,
	.name  = "leet",
	.fops  = &leet_fops

};

static struct file_operations leet_fops =  {
	.owner   THIS_MODULE,
	.open    leet_open,
	.llseek  noop_llseek
};

struct buffer {
	char* data, *end, *read_ptr;
	unsigned long size;
};

static struct buffer *buffer_alloc(unsigned long size)
{
	struct buffer *buf;
	buf = kzalloc(sizeof(*buf), GFP_KERNEL);
	if(unlikely(buf))
		goto out; // Hmm
	
	out:
		return buf;
}

static int __init leet_init(void)
{
	if(!buffer_size)
	{
		return -1;
	}
	misc_register(&leet_misc_device);
	printk(KERN_INFO "leet device has been registered, buffer size is %lu bytes\n",buffer_size);
	return 0;
}

static void __exit leet_exit(void)
{
	misc_deregister(&leet_misc_device);
	printk(KERN_INFO "leet device has been unregistered\n");
}

module_init(leet_init);
module_exit(leet_exit);
