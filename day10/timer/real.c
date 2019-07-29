#include <func.h>
void sigFunc(int signum){
    time_t now;
    time(&now);
    printf("%s\n",ctime(&now));
}
int main(int argc,char* argv[])
{
    signal(SIGALRM,sigFunc);
    struct itimerval t;
    bzero(&t,sizeof(t));
    t.it_value.tv_sec=1;
    t.it_interval.tv_sec=1;
    sleep(5);
    int ret=setitimer(ITIMER_REAL,&t,NULL);
    ERROR_CHECK(ret,-1,"setitimer");
    while(1);
    return 0;
}

