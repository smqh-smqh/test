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
    
    int epfd;
    epfd=epoll_create(1);
    struct epoll_event event,evs[2];
    event.events=EPOLLIN;
    event.data.fd=STDIN_FILENO;
    ret=epoll_ctl(epfd,EPOLL_CTL_ADD,STDIN_FILENO,&event);
    ERROR_CHECK(ret,-1,"epoll_ctl");
    event.data.fd=socketFd;
    ret=epoll_ctl(epfd,EPOLL_CTL_ADD,socketFd,&event);
    ERROR_CHECK(ret,-1,"epoll_ctl");
    int readyCount,i;
    char buf[1024];
    while(1){
        readyCount=epoll_wait(epfd,evs,2,-1);
        for(i=0;i<readyCount;i++){
            if(evs[i].data.fd==STDIN_FILENO){
            bzero(&buf,sizeof(buf));
            ret=read(STDIN_FILENO,buf,sizeof(buf));
            if(ret==0){printf("byebye\n");goto end;}
            send(socketFd,buf,strlen(buf)-1,0);
            }
            if(evs[i].data.fd==socketFd){
            bzero(&buf,sizeof(buf));
            ret=recv(socketFd,buf,sizeof(buf),0);
            if(ret==0){printf("byebye\n");goto end;}
            printf("%s\n",buf);
            }
        }
    }
end:
    close(socketFd);
    return 0;
}

