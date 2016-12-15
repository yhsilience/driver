# 内核空间
* kmalloc/kfree
* vmalloc/vfree
* __get_free_pages/free_pages

# 函数原型

* IS_ERR(const void *ptr); 返回错误编号

* kmalloc(size_t size, gfp_t flags);
  * GFP_KERNEL 可能会导致睡眠。
  * GFP_ATOMIC 不会导致睡眠。
  * GFP_DMA 申请的内存通常情况下位于（0-16Ｍ）空间。
  * __GPF_HIGHMEM 申请高端内存(８９６M以上的物地址为高端内存)。
* __get_free_pages(gfp_t gfp_mask,unsigned int order);
  * order : 请求或释放的页数的２的幂
    
# 注意
　在开发板上实验时，出现段错误，未找到原因
