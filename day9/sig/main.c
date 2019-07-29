#include <func.h>
void sigFunc(int signum)
{
    printf("This is signal %d,before sleep..\n",signum);
    sleep(3);
    printf("This is signal %d,after sleep..\n",signum);
}
int main(int argc,char* argv[])
{
    if(signal(SIGINT,sigFunc)==SIG_ERR){
        perror("signal");
        return -1;
    }
    while(1);
    return 0;
}

