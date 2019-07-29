#include <func.h>
int tcp_init(int* sfd,char* ip,char* port)
{
    int socketFd=socket(AF_INET,SOCK_STREAM,0);                                                                                     
    ERROR_CHECK(socketFd,-1,"socket");
    struct sockaddr_in serArr;
    bzero(&serArr,sizeof(serArr));
    serArr.sin_family=AF_INET;
    serArr.sin_addr.s_addr=inet_addr(ip);
    serArr.sin_port=htons(atoi(port));
    socklen_t len=sizeof(struct sockaddr);
    int reuse=1;
    int ret;
    ret=setsockopt(socketFd,SOL_SOCKET,SO_REUSEADDR,&reuse,sizeof(int));
    ERROR_CHECK(ret,-1,"setsockopt");
    ret=bind(socketFd,(struct sockaddr*)&serArr,len);
    ERROR_CHECK(ret,-1,"bind");
    listen(socketFd,10);
    *sfd=socketFd;
    return 0;
}

