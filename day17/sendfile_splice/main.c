#include "process_pool.h"

int childHandle(int pipeFd){
    int newFd;
    char finishflag;
    while(1){
         recvFd(pipeFd,&newFd); 
         tranfile(newFd);
         close(newFd); 
         write(pipeFd,&finishflag,1);
    }

}

int main(int argc,char* argv[])
{
    ARGS_CHECK(argc,4);
    int socketFd;
    int  ret= tcp_init(&socketFd,argv[1],argv[2]);
    if(-1==ret){return -1;}
    int pnum = atoi(argv[3]);
    int i,pid;
    int fds[2];
    process_data_t *p=(process_data_t *)calloc(pnum,sizeof(process_data_t));
    for(i=0;i<pnum;i++)
    {
    ret=socketpair(AF_LOCAL,SOCK_STREAM,0,fds);
    ERROR_CHECK(ret,-1,"socketpair");
        if(!(pid=fork())){
            close(fds[0]);
            childHandle(fds[1]);
        }
        close(fds[1]);
        p[i].pid=pid;//子进程pid
        p[i].pipeFd=fds[0];
        p[i].busy=0;
    }
    int epfd=epoll_create(1);
    struct epoll_event *evs;
    evs=(struct epoll_event *)calloc(pnum+1,sizeof(struct epoll_event));
    epollInAdd(epfd,socketFd);
    for(i=0;i<pnum;i++){
        epollInAdd(epfd,p[i].pipeFd);
    }
    int readyFdCount,newFd,j;
    char noBusyFlag;
    while(1){
        readyFdCount=epoll_wait(epfd,evs,pnum+1,-1);
        for(i=0;i<readyFdCount;i++)
        {
            if(evs[i].data.fd==socketFd)
            {
                newFd=accept(socketFd,NULL,NULL);
                for(j=0;j<pnum;j++)
                {
                    if(0==p[j].busy)
                    {
                        sendFd(p[j].pipeFd,newFd);
                        p[j].busy=1;
                        printf("%d pid is busy\n",p[j].pid);
                        break;
                    }
                }
                close(newFd);
            }
            for(j=0;j<pnum;j++)
            {
                if(evs[i].data.fd==p[j].pipeFd)
                {
                    read(p[j].pipeFd,&noBusyFlag,1);
                    p[j].busy=0;
                    printf("%d pid is not busy\n",p[j].pid);
                    break;
                }
            }
        }
    }
    return 0;
}

