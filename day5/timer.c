#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/module.h>
#include <linux/timer.h>
#include <asm/uaccess.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("yh");

struct timer_list timer;

void timer_function(int ptr)
{
        printk("timer expired and para is %d \n",ptr);
}

int  time_init()
{
        init_timer(&timer);
        timer.data = 5;
        timer.expires = jiffies + (5 * HZ);
        timer.function = timer_function;
        add_timer(&timer);
        return 0;
}
int  time_exit()
{
        del_timer(&timer);
        return 0;
}

module_init(time_init);
module_exit(time_exit);
