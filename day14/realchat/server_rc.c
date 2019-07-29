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
    ret=bind(socketFd,(struct sockaddr*)&serArr,sizeof(serArr));
    ERROR_CHECK(ret,-1,"bint");
    listen(socketFd,10);
    struct sockaddr_in client;
    bzero(&client,sizeof(client));
    int newFd;
    socklen_t len=sizeof(struct sockaddr);
    newFd=accept(socketFd,(struct sockaddr*)&client,&len);
    printf("client ip=%s,client port=%d\n",inet_ntoa(client.sin_addr),ntohs(client.sin_port));
    char buf[1024]={0};
    fd_set rdset;
    while(1){
        FD_ZERO(&rdset);
        FD_SET(STDIN_FILENO,&rdset);
        FD_SET(newFd,&rdset);
        ret=select(newFd+1,&rdset,NULL,NULL,NULL);
        if(FD_ISSET(STDIN_FILENO,&rdset)){
            bzero(buf,sizeof(buf));
            ret=read(STDIN_FILENO,buf,sizeof(buf));
            if(0==ret){printf("byebye\n");break;}
            send(newFd,buf,sizeof(buf),0);
        }
        if(FD_ISSET(newFd,&rdset)){
            bzero(buf,sizeof(buf));
            ret=recv(newFd,buf,sizeof(buf),0);
            if(0==ret){printf("byebye\n");break;}
            printf("server gets %s",buf);
        }
    }
    close(newFd);
    close(socketFd);
    return 0;
}

