#include "factory.h"

int exitFds[2];
void sigExitFunc(int signum)
{
    printf("%d is coming..\n",signum);
    write(exitFds[1],&signum,1);
}

int epoll_add(int epfd,int fd)
{
    struct epoll_event event;
    event.events=EPOLLIN;
    event.data.fd=fd;
    int ret;
    ret=epoll_ctl(epfd,EPOLL_CTL_ADD,fd,&event);
    ERROR_CHECK(ret,-1,"epoll_ctl");
    return 0;
}

int main(int argc,char* argv[])
{
    if(argc!=5)
    {
        printf("./thread_pool_server IP PORT THREAD_NUM CAPACITY\n");
        return -1;
    }
    pipe(exitFds);
    while(fork()){
        signal(SIGUSR1,sigExitFunc);
        int status;
        wait(&status);
        if(WIFEXITED(status))
        {
            printf("exit success\n");
            exit(0);
        }
    }
    close(exitFds[1]);
    
    Factory_t thread_info;
    int threadNum=atoi(argv[3]);
    int capacity=atoi(argv[4]);
    factoryInit(&thread_info,threadNum,capacity);
    factoryStart(&thread_info);
    int socketFd,newFd;
    tcp_init(&socketFd,argv[1],argv[2]);
    pQue_t pq=&thread_info.que;
    pNode_t pNew;
    int epfd=epoll_create(1);
    struct epoll_event evs[2];
    epoll_add(epfd,socketFd);
    epoll_add(epfd,exitFds[0]);
    int readyFdCount,i,j;
    while(1){
        readyFdCount=epoll_wait(epfd,evs,2,-1);
        for(i=0;i<readyFdCount;i++){
            if(evs[i].data.fd==socketFd){
                newFd=accept(socketFd,NULL,NULL);
                pNew=(pNode_t)calloc(1,sizeof(Node_t));
                pNew->newFd=newFd; 
                pthread_mutex_lock(&pq->mutex);
                queInsert(pq,pNew);
                pthread_mutex_unlock(&pq->mutex);
                pthread_cond_signal(&thread_info.cond);
            }
                if(evs[i].data.fd==exitFds[0])
                {
                    for(j=0;j<threadNum;j++)
                    {
                        pthread_cancel(thread_info.pid[j]);
                    }
                   for(j=0;j<threadNum;j++)
                   {
                        pthread_join(thread_info.pid[j],NULL);
                   }
                exit(0);
                }
        }
    }
    return 0;
}

