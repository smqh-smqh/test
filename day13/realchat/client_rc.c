#include <func.h>

int main(int argc,char* argv[])
{
    ARGS_CHECK(argc,3);
    int socketFd;
    socketFd=socket(AF_INET,SOCK_STREAM,0);
    ERROR_CHECK(socketFd,-1,"socket");
    struct sockaddr_in serArr;
    bzero(&serArr,sizeof(serArr));
    serArr.sin_family=AF_INET;
    serArr.sin_port=htons(atoi(argv[2]));
    serArr.sin_addr.s_addr=inet_addr(argv[1]);
    int ret;
    ret=connect(socketFd,(struct sockaddr*)&serArr,sizeof(serArr));
    ERROR_CHECK(ret,-1,"connect");
    char buf[1024]={0};
    while(1){
    bzero(buf,sizeof(buf));
    read(STDIN_FILENO,buf,sizeof(buf));
    send(socketFd,buf,sizeof(buf),0);
    bzero(buf,sizeof(buf));
    recv(socketFd,buf,sizeof(buf),0);
    printf("client gets %s",buf);
    }
    close(socketFd);
    return 0;
    }

