#include <func.h>

int main(int argc,char* argv[])
{
    int shmid;
    shmid=shmget(1000,1024,IPC_CREAT|0666);
    ERROR_CHECK(shmid,-1,"shmget");
    char *p=(char*)shmat(shmid,NULL,0);
    ERROR_CHECK(p,(char*)-1,"shmat");
    memset(p,0,1024);
    int fdr=open(argv[1],O_RDONLY);
    int fdw=open(argv[2],O_RDONLY);
    printf("I am chat1 fdr=%d fdw=%d\n",fdr,fdw);
    int ret;
    char buf[128]={0};
    fd_set rdset;
    while(1)
    {
        FD_ZERO(&rdset);
        FD_SET(fdw,&rdset);
        FD_SET(fdr,&rdset);
        ret=select(fdr+1,&rdset,NULL,NULL,NULL);
        if(FD_ISSET(fdw,&rdset))
        {
           // memset(buf,0,sizeof(buf));
           //ret=read(STDIN_FILENO,buf,sizeof(buf));
           // write(fdw,buf,strlen(buf)-1);
            printf("%s",p); 
        }

        if(FD_ISSET(fdr,&rdset))
        {
            memset(buf,0,sizeof(buf));
            ret= read(fdr,buf,sizeof(buf));
            printf("%*s%s\n",50,"",buf);
            if(0==ret){
                printf("byebye\n");
                break;
            }
        }
    }
    ret=shmdt(p);
    ERROR_CHECK(ret,-1,"shmdt");
    return 0;
}

