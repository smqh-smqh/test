#include <func.h>

int main(int argc,char* argv[])
{
    ARGS_CHECK(argc,3);
    int socketFd=socket(AF_INET,SOCK_DGRAM,0);
    ERROR_CHECK(socketFd,-1,"socket");
    struct sockaddr_in serArr;
    bzero(&serArr,sizeof(serArr));
    serArr.sin_family=AF_INET;
    serArr.sin_addr.s_addr=inet_addr(argv[1]);
    serArr.sin_port=htons(atoi(argv[2]));
    int ret=bind(socketFd,(struct sockaddr*)&serArr,sizeof(serArr));
    ERROR_CHECK(ret,-1,"bind");
    struct sockaddr_in client;
    bzero(&client,sizeof(client));
    socklen_t len = sizeof(struct sockaddr);
    char buf[128]={0};
    recvfrom(socketFd,buf,sizeof(buf),0,(struct sockaddr*)&client,&len);
    printf("server gets %s,client ip=%s,client port=%d\n",buf,inet_ntoa(client.sin_addr),ntohs(client.sin_port));
    sendto(socketFd,"wo hen bang",11,0,(struct sockaddr*)&client,sizeof(client));
    close(socketFd);
    return 0;
}

