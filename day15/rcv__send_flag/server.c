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
    int reuse=1;
    int ret;
    ret=setsockopt(socketFd,SOL_SOCKET,SO_REUSEADDR,&reuse,sizeof(int));
    ERROR_CHECK(ret,-1,"setsockopt");
    ret=bind(socketFd,(struct sockaddr*)&serArr,len);
    ERROR_CHECK(ret,-1,"bind");
    listen(socketFd,10);

    int epfd;
    epfd=epoll_create(1);
    struct epoll_event event,evs[3];
    event.events=EPOLLIN;//监听读事件
    event.data.fd=STDIN_FILENO;
    ret=epoll_ctl(epfd,EPOLL_CTL_ADD,STDIN_FILENO,&event);
    ERROR_CHECK(ret,-1,"epoll_ctl");
    event.data.fd=socketFd;
    ret=epoll_ctl(epfd,EPOLL_CTL_ADD,socketFd,&event);
    ERROR_CHECK(ret,-1,"epoll_ctl");
    int readyFdCount,i;
    int newFd;
    char buf[128];
    while(1)
    {
        readyFdCount=epoll_wait(epfd,evs,3,-1);
        for(i=0;i<readyFdCount;i++){

            if(evs[i].data.fd==socketFd){
                newFd=accept(socketFd,NULL,NULL);
                event.data.fd=newFd;
                ret=epoll_ctl(epfd,EPOLL_CTL_ADD,newFd,&event);
                ERROR_CHECK(ret,-1,"epoll_ctl");
            }
            if(evs[i].data.fd==STDIN_FILENO){
                bzero(&buf,sizeof(buf));
                ret=read(STDIN_FILENO,buf,sizeof(buf));
                if(ret==0){printf("byebye\n");goto end;}
                send(newFd,buf,strlen(buf)-1,0);
            }

            if(evs[i].data.fd==newFd){
                bzero(&buf,sizeof(buf));
                ret = recv(newFd,buf,sizeof(buf)-1,0);
                if(ret==0){
                    printf("byebye\n");
                    ret=epoll_ctl(epfd,EPOLL_CTL_DEL,newFd,&event);
                    ERROR_CHECK(ret,-1,"epoll_ctl");
                    close(newFd);
                    break;
                }
                printf("%s\n",buf);
            }
        }
    }
end:
    close(socketFd);
    return 0;
}

