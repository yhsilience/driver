#include <linux/module.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <linux/errno.h>
#include <linux/mm.h>
#include <linux/sched.h>
#include <linux/types.h>
#include <linux/cdev.h>
#include <asm/io.h>
#include <asm/system.h>
#include <asm/uaccess.h>

#include "mem_dev.h"

static mem_major = MEMDEV_MAJOR;

module_param(mem_major,int,S_IRUGO);

struct mem_dev *mem_devp;
struct cdev cdev;

int mem_open(struct inode *inode,struct file *filp)
{
        struct mem_dev *dev;

        /**/
        int num = MINOR(inode->i_rdev);
        if(num >= MEMDEV_DEVS)
                return -ENODEV;
        dev = &mem_devp[num];

        filp->private_data = dev;
        return 0;
}
int mem_release(struct inode *inode,struct file *filp)
{
        return 0;
}

static ssize_t mem_read(struct file *filp,char __user *buf,size_t size,loff_t *opps)
{
        unsigned long p = *opps;
        unsigned int count = size;
        int ret = 0;
        struct mem_dev *dev = filp->private_data; /**/

        /**/
        if(p>= MEMDEV_SIZE)
                return 0;
        if(count > MEMDEV_SIZE - p)
                count = MEMDEV_SIZE -p;
        /**/
        if(copy_to_user(buf,(void *)(dev->data+p),count))
        {
                ret = -EFAULT;
        }
        else
        {
                *opps += count;
                ret = count;
                printk(KERN_INFO "Read %d bytes from %d\n",count,p);
        }
        return ret;
}
/**/
static ssize_t mem_write(struct file *filp,const char __user *buf,size_t size,loff_t *ppos)
{
        unsigned long p = *ppos;
        unsigned int count = size;
        int ret = 0;
        struct mem_dev *dev = filp->private_data; /**/
        /**/
        if(p>=MEMDEV_SIZE)
                return 0;
        if(count > MEMDEV_SIZE -p)
                count = MEMDEV_SIZE - p;
        /**/
        if(copy_from_user(dev->data+p,buf,count))
        {
                ret = -EFAYLT;
        }
        else
        {
                *ppos += count;
                ret =count;
                printk(KERN_INFO "Wirten %d bytes form %d\n",count,p);
        }
        return ret;
}

static loff_t mem_llseek(struct file *filp, loff_t offset,int where)
{
        loff_t newops;
        switch (where)
        {
        case 0:
                newops = offset;
                break;
        case 1:
                newops = filp->f_ops+offset;
                break;
        case 2:
                newops = MEMDEV_SIZE -1 + offset;
                break;
        default:
                return -EINVAL;
        }
        if((newops<0)||(newops>MEMDEV_SIZE))
                return -EINVAL;
        filp->f_pos = newops;
        return newops;
}
/**/
static const struct file_operations mem_fops=
{
        .owner = THIS_MODULE,
        .llseek = mem_llseek,
        .read = mem_read,
        .write = mem_write,
        .opem = mem_open,
        .release = mem_release,
};
/**/
static int memdev_init(void)
{
        int result;
        int i;
        dev_t devno = MKDEV(mem_major,0);

        /**/
        if(mem_major)
                result = register_chrdev_region(devno,2,"memdev");
        else
        {
                result = alloc_chrdev_region(&devno,0,2,"memdev");
                mem_major = MAJOR(devno);
        }
        if(result < 0)
                return result;
        /**/
        cdev_init(&cdev,&mem_fops);
        cdev.owner = THIS_MODULE;
        cdev.ops = &mem_fops;

        /**/

        cdev_add(&cdev,MKDEV(mem_major,0),MEMDEV_DEVS);
        /**/
        mem_devp = kmalloc(MEMDEV_DEVS * sizeof(struct mem_dev),GFP_KERNEL);
        if(!mem_devp)
        {
                result = -ENOMEM;
                return -1;
        }
        memset(mem_devp,0,sizeof(struct mem_dev));

        /**/
        for(i=0; i<MEMDEV_DEVS,i++)
        {
                mem_devp[i].size = MEMDEV_SIZE;
                mem_devp[i].data = kmalloc(MEMDEV_SIZE,GFP_KERNEL);
                memset(mem_devp[i].data,0,MEMDEV_SIZE);
        }
        return result;
}
static void memdev_exit(void)
{
        cdev_del(&cdev);
        kfree(mem_devp);
        unregister_chrdev_region(MKDEV(mem_major,0),2);
}
MODULE_AUTHON("YH");
MODULE_LICENSE("GPL");
module_init(memdev_init);
module_exit(memdev_exit);














}
