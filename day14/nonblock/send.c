#include <func.h>
int setNonBlock(int fd){
    int status;
    status=fcntl(fd,F_GETFL);
    status=status|O_NONBLOCK;
    fcntl(fd,F_SETFL,status);
    return 0;
}
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

    setNonBlock(socketFd);

    char buf[1000];
    int total=0;
    while(1){
    ret=send(socketFd,buf,sizeof(buf),0);
    if(-1==ret){break;}
    total+=ret;
    printf("total=%d,ret=%d\n",total,ret);
    }
    close(socketFd);
    return 0;
}

