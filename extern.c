#include <linux/init.h>
#include <linux/module.h>

MODULE_LICENSE("GPL v2");

int exdexp_mult(int x,int y)
{
  printk("extern functoin\n");
  return x+y;
}
int exdexp_divid(int x,int y)
{
  printk("extern function dvivd" );
  return x-y;
}

EXPORT_SYMBOL(exdexp_mult);
EXPORT_SYMBOL(exdexp_divid);
