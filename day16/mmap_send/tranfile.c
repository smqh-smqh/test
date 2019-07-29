#include "process_pool.h"
void sigFunc(int signum)
{
    printf("%d is coming\n",signum);
}

int tranfile(int newFd)
{
    signal(SIGPIPE,sigFunc);
    train_t train;
    int ret;
    //文件名字
    train.dataLen=strlen(FILENAME);
    strcpy(train.buf,FILENAME);
    send(newFd,&train,4+train.dataLen,0);

    //文件大小
    struct stat buf;
    int fd =open(FILENAME,O_RDWR);
    ERROR_CHECK(fd,-1,"open");
    fstat(fd,&buf);
    train.dataLen=sizeof(buf.st_size);
    memcpy(train.buf,&buf.st_size,train.dataLen);
    send(newFd,&train,4+train.dataLen,0);

    //文件内容
    //while((train.dataLen=read(fd,train.buf,sizeof(train.buf))))
   // {
   //     ret=send(newFd,&train,4+train.dataLen,0);
   //     if(-1==ret){return -1;}
   // }
    char *pMap=(char*)mmap(NULL,buf.st_size,PROT_READ|PROT_WRITE,MAP_SHARED,fd,0);
    ERROR_CHECK(pMap,(char*)-1,"mmap");
    off_t sendFileSize=0;
    while(buf.st_size-sendFileSize>=1000)
    {
        train.dataLen=sizeof(train.buf);
        memcpy(train.buf,pMap+sendFileSize,train.dataLen);
        ret=send(newFd,&train,4+train.dataLen,0);
        if(-1==ret){return -1;}
        sendFileSize+=1000;
    }
    train.dataLen=buf.st_size-sendFileSize;
    memcpy(train.buf,pMap+sendFileSize,train.dataLen);
    ret=send(newFd,&train,4+train.dataLen,0);
    if(-1==ret){return -1;}
    
    train.dataLen=0;
    send(newFd,&train,4,0);
    printf("send success\n");
    return 0;
}

