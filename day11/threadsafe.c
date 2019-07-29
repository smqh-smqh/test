#include <func.h>

void* threadFunc(void* p1){
    time_t now;
    time(&now);
    char *p=ctime(&now);
    printf("time is %s\n",p);
    sleep(3);
    printf("time is %s\n",p);
}
int main(int argc,char* argv[])
{
    pthread_t pthid;
    pthread_create(&pthid,NULL,threadFunc,NULL);
    sleep(1);
    time_t now;
    time(&now);
    char *p=ctime(&now);
    printf("time is %s\n",p);
    pthread_join(pthid,NULL);
    return 0;
}

