#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <linux/device.h>
#include <asm/uaccess.h>
#include <asm/irq.h>
#include <asm/io.h>

int major;

static struct class *chardev_class;

static int char_dev_open(struct inode *inode,struct file *file)
{
        printk("first char dev\n");
        return 0;
}
static ssize_t char_dev_write(struct file *file,const char __user *buf,size_t count,loff_t *ppos)
{
        printk("first char dev is write\n");
        return 0;
}

static struct file_operations char_dev_fops={
        .owner = THIS_MODULE,
        .open  = char_dev_open,
        .write = char_dev_write,
};

static int __init char_dev_init(void)
{
        major = register_chrdev(0,"char_dev",&char_dev_fops);
        chardev_class = class_create(THIS_MODULE,"char_dev");
        device_create(chardev_class, NULL, MKDEV(major,0), NULL, "gpio_yh");
        return 0;
}

static int __init char_dev_exit(void)
{
        unregister_chrdev(major,"char_dev");
        class_destroy(chardev_class);
        return 0;
}
module_init(char_dev_init);
module_exit(char_dev_exit);
MODULE_LICENSE("GPL");
MODULE_AUTHOR("yh <yanghen517@gmail.com>");
