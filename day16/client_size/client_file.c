#include <func.h>

int recvCycle(int,void*,int);

int main(int argc,char* argv[])
{
    ARGS_CHECK(argc,3);
    int socketFd;
    socketFd=socket(AF_INET,SOCK_STREAM,0);
    ERROR_CHECK(socketFd,-1,"socket");
    struct sockaddr_in serAddr;
    bzero(&serAddr,sizeof(serAddr));
    serAddr.sin_family=AF_INET;
    serAddr.sin_addr.s_addr=inet_addr(argv[1]);
    serAddr.sin_port=htons(atoi(argv[2]));
    int ret;
    socklen_t len=sizeof(struct sockaddr);
    ret=connect(socketFd,(struct sockaddr*)&serAddr,len);
    ERROR_CHECK(ret,-1,"connect");

    int fd;
    int datalen;
    char buf[1000]={0};
    recvCycle(socketFd,&datalen,4);
    recvCycle(socketFd,buf,datalen);
    fd=open(buf,O_CREAT|O_RDWR,0666);
    ERROR_CHECK(fd,-1,"open");

    off_t fileSize,downlowdSize=0;
    off_t lastLoadSize=0,slice;
    recvCycle(socketFd,&datalen,4);
    recvCycle(socketFd,&fileSize,datalen);
    slice=fileSize/2000;

    struct timeval start,end;
    gettimeofday(&start,NULL);
    while(1)
    {
        ret=recvCycle(socketFd,&datalen,4);
        if(ret==-1){break;}
        if(datalen>0){
            ret=recvCycle(socketFd,buf,datalen);
            if(-1==ret){break;}
            write(fd,buf,datalen);
            downlowdSize+=datalen;
            if(downlowdSize-lastLoadSize>=slice)
            {
                printf("%5.2f%s\r",(float)downlowdSize/fileSize*100,"%");
                fflush(stdout);
                lastLoadSize=downlowdSize;
            }
        }else
        {
            printf("100.00%%\n");
            break;
        }
    }
    gettimeofday(&end,NULL);
    printf("usetime=%ld\n",(end.tv_sec-start.tv_sec)*1000000+end.tv_usec-start.tv_usec);
    close(fd);
    close(socketFd);
}

