#define _GNU_SOURCE
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

    off_t fileSize=0,downLoadSize=0;
    off_t lastLoadSize=0,slice;
    recvCycle(socketFd,&datalen,4);
    recvCycle(socketFd,&fileSize,datalen);
    printf("fileSize=%ld\n",fileSize);
    //slice=fileSize/2000;

    int fds[2];
    pipe(fds);
    struct timeval start,end;
    gettimeofday(&start,NULL);
    // while(1)
    // {
    //     ret=recvCycle(socketFd,&datalen,4);
    //     if(ret==-1){break;}
    //     if(datalen>0){
    //         ret=recvCycle(socketFd,buf,datalen);
    //         if(-1==ret){break;}
    //         write(fd,buf,datalen);
    //         downlowdSize+=datalen;
    //         if(downlowdSize-lastLoadSize>=slice)
    //         {
    //             printf("%5.2f%s\r",(float)downlowdSize/fileSize*100,"%");
    //             fflush(stdout);
    //             lastLoadSize=downlowdSize;
    //         }
    //     }else
    //     {
    //        printf("recycle datalen=0\n");
    //         printf("100.00%%\n");
    //         break;
    //     }
    // }
    // ftruncate(fd,fileSize);
    // char* pMap=(char*)mmap(NULL,fileSize,PROT_READ|PROT_WRITE,MAP_SHARED,fd,0);
    // ERROR_CHECK(pMap,(char*)-1,"mmap");
    // recvCycle(socketFd,pMap,fileSize);
    // munmap(pMap,fileSize);
    slice=fileSize/1000;
    while(downLoadSize<fileSize){
        ret=splice(socketFd,NULL,fds[1],NULL,65536,SPLICE_F_MOVE|SPLICE_F_MORE);
        //if(ret==0){break;}
        ERROR_CHECK(ret,-1,"splice");
        ret=splice(fds[0],NULL,fd,NULL,ret,SPLICE_F_MOVE|SPLICE_F_MORE);
        ERROR_CHECK(ret,-1,"splice");
        downLoadSize+=ret;
        if(downLoadSize-lastLoadSize>=slice)
        {
            printf("%5.2f%s\r",(float)downLoadSize/fileSize,"%");
            fflush(stdout);
            lastLoadSize=downLoadSize;
        }
    }

    gettimeofday(&end,NULL);
    printf("100.00%%\n");
    printf("usetime=%ld\n",(end.tv_sec-start.tv_sec)*1000000+end.tv_usec-start.tv_usec);
    close(fd);
    close(socketFd);
}

