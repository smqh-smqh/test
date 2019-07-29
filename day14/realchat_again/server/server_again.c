#include <func.h>
int tcpInit(int*,char*,char*);
int main(int argc,char* argv[])
{
    ARGS_CHECK(argc,3);
    int socketFd;
    int ret=tcpInit(&socketFd,argv[1],argv[2]);
    if(-1==ret) return -1;
    int newFd;
    char buf[1024]={0};
    fd_set rdset;
    fd_set needset;
    FD_ZERO(&needset);
    FD_SET(STDIN_FILENO,&needset);
    FD_SET(socketFd,&needset);
    while(1){
        memcpy(&rdset,&needset,sizeof(fd_set));
        ret=select(14,&rdset,NULL,NULL,NULL);
        if(ret>0)
        {

            if(FD_ISSET(socketFd,&rdset)){
                newFd=accept(socketFd,NULL,NULL);
                ERROR_CHECK(newFd,-1,"accept");
                FD_SET(newFd,&needset);
            }
            if(FD_ISSET(STDIN_FILENO,&rdset)){
                bzero(buf,sizeof(buf));
                ret=read(STDIN_FILENO,buf,sizeof(buf));
                if(0==ret){printf("byebye\n");break;}
                send(newFd,buf,sizeof(buf)-1,0);
            }
            if(FD_ISSET(newFd,&rdset)){
                bzero(buf,sizeof(buf));
                ret=recv(newFd,buf,sizeof(buf),0);
                if(0==ret){printf("byebye\n");
                    FD_CLR(newFd,&needset);
                    close(newFd);
                }else{
                    printf("%s",buf);
                }
            }
        }
    }
    close(socketFd);
    return 0;
}

