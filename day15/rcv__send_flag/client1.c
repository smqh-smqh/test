#include <func.h>

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
    char buf[1000];
    while(1){
    ret=send(socketFd,buf,sizeof(buf),MSG_DONTWAIT);
    printf("ret1=%d\n",ret);
    if(-1==ret){break;}
    }
    close(socketFd);
    return 0;
}

