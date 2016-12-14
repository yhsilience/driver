// include kernel head files

#include <linux/init.h>
#include <linux/module.h>

MODULE_LICENSE("Dual BSD/GPL");
MODULE_AUTHOR("yanghen");
MODULE_DESCRIPTION("My Second Hello world kernel moduel");
MODULE_VERSION("0.0.1");
MODULE_ALIAS("HelloWorld");

extern int exdexp_mult(int x,int y);
extern int exdexp_divid(int x, int y);

static int __init hello_init(void)
{
								printk(KERN_ALERT "My first kernel module\n");
								exdexp_mult(1,1);
								exdexp_divid(2,2);
								return 0;

}

static void __exit hello_exit(void)
{
								printk(KERN_ALERT "exit kernel module\n");

}


module_init(hello_init);
module_exit(hello_exit);
