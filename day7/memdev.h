#ifndef _MEMDEV_H_
#define _MEMDEV_H_

#ifndef MEMDEV_MAJOR
#define MEMDEV_MAJOR 251 /*主设备号*/
#endif

#ifndef MEMDEV_SIZE
#define MEMDEV_SIZE 4096　
#endif

#ifndef MEMDEV_DEVS
#define MEMDEV_DEVS 2　/*设备数*/
#endif

/*mem设备描述结构体*/
struct mem_dev
{
        char *data;
        unsigned long size;
};

#endif
