#include "process_pool.h"

int epollInAdd(int epfd,int newfd)
{
    struct epoll_event event;
    event.events=EPOLLIN;
    event.data.fd=newfd;
    int ret;
    ret=epoll_ctl(epfd,EPOLL_CTL_ADD,newfd,&event);
    ERROR_CHECK(ret,-1,"epoll_ctl");
    return 0;
}

