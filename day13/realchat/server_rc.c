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
    socklen_t len=sizeof(client);
    newFd=accept(socketFd,(struct sockaddr*)&client,&len);
    printf("client ip=%s,client port=%d\n",inet_ntoa(client.sin_addr),ntohs(client.sin_port));
    char buf[1024]={0};
    while(1){
    bzero(buf,sizeof(buf));
    recv(newFd,buf,sizeof(buf),0);
    printf("server gets %s",buf);
    bzero(buf,sizeof(buf));
    read(STDIN_FILENO,buf,sizeof(buf));
    send(newFd,buf,sizeof(buf),0);
    }
    close(newFd);
    close(socketFd);
    return 0;
}

