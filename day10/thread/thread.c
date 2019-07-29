#include <func.h>
void* threadfunc(void *p){
    printf("I am child thread,gets %d\n",*(int*)p);
    pthread_exit((void*)2);
}
int main(int argc,char* argv[])
{
    pthread_t pthid;
    int val=1;
    long thret;
    int ret=pthread_create(&pthid,NULL,threadfunc,&val);
    THREAD_ERROR_CHECK(ret,"pthread_create");
    ret=pthread_join(pthid,(void**)&thret);
    THREAD_ERROR_CHECK(ret,"pthread_join");
    printf("I am main thread,return value=%ld\n",thret);
    return 0;
}

