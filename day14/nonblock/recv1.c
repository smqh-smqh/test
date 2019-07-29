#include <func.h>

int main(int argc,char* argv[])
{
    ARGS_CHECK(argc,3);
    int socketFd=socket(AF_INET,SOCK_STREAM,0);
    ERROR_CHECK(socketFd,-1,"socket");
    struct sockaddr_in serArr;
    bzero(&serArr,sizeof(serArr));
    serArr.sin_family=AF_INET;
    serArr.sin_addr.s_addr=inet_addr(argv[1]);
    serArr.sin_port=htons(atoi(argv[2]));
    socklen_t len=sizeof(struct sockaddr);
    //int reuse=1;
    int ret;
    //ret=setsockopt(socketFd,SOL_SOCKET,SO_REUSEADDR,&reuse,sizeof(int));
    //ERROR_CHECK(ret,-1,"setsockopt");
    ret=bind(socketFd,(struct sockaddr*)&serArr,len);
    ERROR_CHECK(ret,-1,"bind");
    listen(socketFd,10);

    int newFd=accept(socketFd,NULL,NULL);
    printf("newFd=%d\n",newFd);
    char buf[10];
    read(0,buf,sizeof(buf));
    return 0;
}

