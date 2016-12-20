#include <stdio.h>

int main()
{
        FILE *fp0 = NULL;
        char buf[4096];
        /**/
        strcpy(buf,"mem is char dev\n");
        printf("buf:%s\n",buf);

        fp0 = fopen("dev/memdev1","r+");
        if(fp0 == NULL)
        {
                printf("Open memdev1 is error\n");
                return -1;
        }

        fwrite(buf,sizeof(buf),1,fp0);

        fseek(fp0,0,SEEK_SET);

        strcpy(buf,"Buf is NULL\n");

        fread(buf,sizeof(buf),1,fp0);

        printf("buf:%s\n",buf);
        return 0;
}
