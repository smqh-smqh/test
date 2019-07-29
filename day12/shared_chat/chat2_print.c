#include <func.h>

int main(int argc,char* argv[])
{
    ARGS_CHECK(argc,3);
    int fdw=open(argv[1],O_WRONLY);
    int fdr=open(argv[2],O_RDONLY);
    printf("I am chat2 fdw=%d fdr=%d\n",fdw,fdr);
    char buf[128]={0};
    fd_set rdset;
    int ret;
    while(1)
    {
        FD_ZERO(&rdset);                                     
        FD_SET(STDIN_FILENO,&rdset);
        FD_SET(fdr,&rdset);
        ret=select(fdr+1,&rdset,NULL,NULL,NULL);
        if(FD_ISSET(STDIN_FILENO,&rdset))
        {
            memset(buf,0,sizeof(buf));
            ret=read(STDIN_FILENO,buf,sizeof(buf));
            write(fdw,buf,strlen(buf)-1);
            if(0==ret)
            {
                printf("byebye\n");
                break;
            }
        }   

        if(FD_ISSET(fdr,&rdset))
        {
            memset(buf,0,sizeof(buf));
            ret=read(fdr,buf,sizeof(buf));
            printf("%*s%s\n",50,"",buf);
            if(0==ret){                                      
                printf("byebye\n");
                break;

            }  

        }   

    } 
    return 0;
}

