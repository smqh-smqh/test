#include <func.h>
void sigFunc(int signum,siginfo_t *p,void *p1){
}
int main(int argc,char* argv[])
{
    sigset_t proMask;
    sigemptyset(&proMask);
    sigaddset(&proMask,SIGINT);
    int ret=sigprocmask(SIG_BLOCK,&proMask,NULL);
    ERROR_CHECK(ret,-1,"sigprocmask");
    struct sigaction act;
    act.sa_flags=SA_SIGINFO;
    act.sa_sigaction=sigFunc;
    sigaction(SIGINT,&act,NULL);
    sleep(10);
    sigset_t pending;
    sigpending(&pending);
    if(sigismember(&pending,SIGINT))
    {
        printf("SIGINT is pending\n");
    }else
    {
        printf("SIGINT is not pending\n");
    }
    ret=sigprocmask(SIG_UNBLOCK,&proMask,NULL);
    return 0;
}

