#include <linux/init.h>
#include <linux/slab.h>
#include <linux/list.h>
#include <linux/module.h>
#include <linux/kernel.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("yh");

/*结构体*/

struct student
{
        char name[20];
        int num;
        struct list_head list;
};

struct student *pstudent;
struct student *tmp_student;
struct list_head student_list;
struct list_head *pos;


int mylist_init(void)
{
        int i= 0;
        INIT_LIST_HEAD(&student_list);
        pstudent = kmalloc(sizeof(struct student)*5,GFP_KERNEL);
        memset(pstudent,0,sizeof(struct student)*5);

        for(i=0; i<5; i++)
        {
                //printk("Student name = %d\n",pstudent[i].name);
                sprintf(pstudent[i].name,"student%d",i+1);
                pstudent[i].num = i;
                list_add(&(pstudent[i].list),&student_list);
        }

        /*遍历*/
        list_for_each(pos,&student_list)
        {
                tmp_student = list_entry(pos,struct student,list); //提取数据结构
                printk("student %d name:%s\n",tmp_student->name,tmp_student->name);
        }
        return 0;
}

int  mylist_exit(void)
{
  #if 0
        int i;
        for(i=0; i<5; i++)
        {
                list_del(&(pstudent[i].list));
        }
        kfree(pstudent);
  #endif
        /*会有段错误*/
        list_for_each(pos,&student_list)
        {
                list_del(&student_list);
                printk("success\n");
        }
}

module_init(mylist_init);
module_exit(mylist_exit);
