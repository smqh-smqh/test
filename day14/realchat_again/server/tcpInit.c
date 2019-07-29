#include <func.h>

int tcpInit(int*sfd,char* ip,char* port)
{
    int socketFd;
    socketFd=socket(AF_INET,SOCK_STREAM,0);
    ERROR_CHECK(socketFd,-1,"socket");
    struct sockaddr_in serArr;
    bzero(&serArr,sizeof(serArr));
    serArr.sin_family=AF_INET;
    serArr.sin_port=htons(atoi(port));
    serArr.sin_addr.s_addr=inet_addr(ip);
    int ret;
    ret=bind(socketFd,(struct sockaddr*)&serArr,sizeof(serArr));
    ERROR_CHECK(ret,-1,"bint");
    listen(socketFd,10);
    *sfd=socketFd;
    return 0;
}

