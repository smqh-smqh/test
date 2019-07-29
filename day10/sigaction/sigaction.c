#include <func.h>

void sigFunc(int signum,siginfo_t *p,void *p1)
{
    printf("before sleep %d is coming\n",signum);
    sleep(2);
    sigset_t pending;
    sigpending(&pending);
    if(sigismember(&pending,SIGQUIT))
    {
        printf("SIGQUIT is pendding\n");
    }else
    {
        printf("SIGQUIT is not pending\n");
    }
    printf("after sleep %d is coming\n",signum);
}
int main(int argc,char* argv[])
{
    struct sigaction act;
    bzero(&act,sizeof(act));
    act.sa_flags=SA_SIGINFO;
    act.sa_sigaction=sigFunc;
    sigaction(SIGINT,&act,NULL);
    sigemptyset(&act.sa_mask);
    sigaddset(&act.sa_mask,SIGQUIT);
    signal(SIGQUIT,SIG_IGN);
    int ret=sigaction(SIGINT,&act,NULL);
    ERROR_CHECK(ret,-1,"sigaction");
    ret=sigaction(SIGQUIT,&act,NULL);
    ERROR_CHECK(ret,-1,"sigaction");
    while(1);
    return 0;
}

