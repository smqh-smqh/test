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
    fd_set rdset;
    while(1){
        FD_ZERO(&rdset);
        FD_SET(STDIN_FILENO,&rdset);
        FD_SET(socketFd,&rdset);
        select(socketFd+1,&rdset,NULL,NULL,NULL);
        if(FD_ISSET(STDIN_FILENO,&rdset)){
            bzero(buf,sizeof(buf));
            ret=read(STDIN_FILENO,buf,sizeof(buf));
            if(0==ret){printf("byebye\n");break;}
            send(socketFd,buf,sizeof(buf),0);
        }
        if(FD_ISSET(socketFd,&rdset)){
            bzero(buf,sizeof(buf));
            ret=recv(socketFd,buf,sizeof(buf),0);
            if(0==ret){printf("byebye\n");break;}
            printf("client gets %s",buf);
        }
    }
    close(socketFd);
    return 0;
}

