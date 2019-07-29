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
    while((train.dataLen=read(fd,train.buf,sizeof(train.buf))))
    {
        ret=send(newFd,&train,4+train.dataLen,0);
        if(-1==ret){return -1;}
    }
    send(newFd,&train,4,0);
    printf("send success\n");
    return 0;
}

