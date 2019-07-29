#include "process_pool.h"
void sigFunc(int signum)
{
    printf("%d is coming\n",signum);
}

int tranfile(int newFd)
{
    sleep(6);
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

   // char *pMap=(char*)mmap(NULL,buf.st_size,PROT_READ|PROT_WRITE,MAP_SHARED,fd,0);
   // ERROR_CHECK(pMap,(char*)-1,"mmap");
   // 
   // ret=send(newFd,pMap,buf.st_size,0);
   // if(-1==ret){return -1;}

   ret=sendfile(newFd,fd,NULL,buf.st_size);
    ERROR_CHECK(ret,-1,"sendfile");
    train.dataLen=0;
    send(newFd,&train,4,0);
    printf("send success\n");
    return 0;
}

