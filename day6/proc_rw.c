#include <linux/module.h>
#include <linux/init.h>
#include <linux/proc_fs.h>
#include <asm/uaccess.h>

static struct proc_dir_entry *mydir;
static struct proc_dir_entry *pfile;

static char info[256];
static int myproc_read(char *page,char **start,off_t off,int count,int *eof,
                       void *data)
{
        int len = strlen(info);
        if(off >= len)
                return 0;
        if(count > len-off)
        {
                count = len - off;
        }
        memcpy(page+off,info+off,count);
        return off + count;
}

static int myproc_write (struct file *file,const char __user *buffer,
                            unsigned long count,void *data)
{
        unsigned long count2 = count;
        if(count2 >= sizeof(info))
        {
                count2 = sizeof(info) -1;
        }
        if(copy_from_user(info,buffer,count2))
        {
                return -EFAULT;
        }
        info[count2] = '\0';
        return count;
}

static int __init myproc_init(void)
{
        mydir = proc_mkdir("mydir",NULL);
        if(!mydir)
        {
                printk(KERN_ERR " Can't creare /proc/mydir\n");
                return -1;
        }
        pfile = create_proc_entry("pool",0666,mydir);
        if(!pfile)
        {
                printk(KERN_ERR "Can't create /proc/mydir/pool\n");
                remove_proc_entry("mydir",NULL);
                return -1;

        }
}

static void __exit myproc_exit(void)
{
        remove_proc_entry("pool",mydir);
        remove_proc_entry("mydir",NULL);
}

module_init(myproc_init);
module_exit(myproc_exit);
MODULE_LICENSE("GPL");
