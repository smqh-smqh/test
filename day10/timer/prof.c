#include <func.h>
void sigFunc(int signum){
    time_t now;
    time(&now);
    printf("%s\n",ctime(&now));
}
int main(int argc,char* argv[])
{
    signal(SIGPROF,sigFunc);
    struct itimerval t;
    bzero(&t,sizeof(t));
    t.it_value.tv_sec=1;
    t.it_interval.tv_sec=1;
    sigFunc(0);
    sleep(5);
    int ret=setitimer(ITIMER_PROF,&t,NULL);
    ERROR_CHECK(ret,-1,"setitimer");
    while(1);
    return 0;
}

