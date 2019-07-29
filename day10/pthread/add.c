#include <func.h>
void*  threadfunc(void *p){
    printf("I am child\n");
}
int main(int argc,char* argv[])
{
    pthread_t pthid;
    int val=0;
    int ret=pthread_create(&pthid,NULL,threadfunc,&val);
    usleep(1);
    printf("I am main\n");
   // ret=pthread_create(&pthid,NULL,threadfunc,NULL);
    return 0;
}

