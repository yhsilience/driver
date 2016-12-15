#include <linux/init.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <linux/slab.h>
#include <linux/vmalloc.h>

MODULE_LICENSE("GPL v2");

unsigned char* kernelmalloc = NULL;
unsigned char* kernelpage = NULL;
int __init kernelspace_init(void)
{
        int ret = -ENOMEM;
        kernelmalloc  = (unsigned char*)kmalloc(100,GFP_KERNEL);
        if(IS_ERR(kernelmalloc))
        {
                printk("kmalloc is failed\n");
                ret = PTR_ERR(kernelmalloc);
                goto error;
        }
        printk("kmalloc sapce = 0x%lx\n",kernelmalloc);

        kernelpage = __get_free_pages(GFP_KERNEL,1);
        if(IS_ERR(kernelmalloc))
        {
                printk("get_free_pages is failed\n");
                ret = PTR_ERR(kernelpage);
                goto error;
        }
        printk("get_free_pages sapce = 0x%lx\n",kernelpage);
        return 0;
error:
        return ret;
}
int __init kernelspace_exit(void)
{
        kfree(kernelmalloc);
        free_pages(kernelpage,2);
        return 0;
}
module_init(kernelspace_init);
module_exit(kernelspace_exit);
