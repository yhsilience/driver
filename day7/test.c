#include <stdio.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
int main(void)
{
        int fd;
        int var = 1;
        fd = fopen("dev/gpio_yh","r+");
        if(fd<0)
        {
                printf ("cant't open!fd=%d\n",fd);
                return -1;
        }
        printf ("open success!\n");
        write(fd,&var,4);
        return 0;
}
