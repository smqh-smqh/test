#include <func.h>

void cleanup(void* p){
    free(p);
    printf("free success\n");
}
void* threadfunc(void *p){
    //sleep(5);
    printf("I am child thread\n");
    printf("I am child thread\n");
    p=malloc(20);
    pthread_cleanup_push(cleanup,p);
    printf("before read \n");
    read(STDIN_FILENO,p,sizeof(p));
    printf("after read \n");
    printf("gets %s",p);
    pthread_cleanup_pop(1);
    return NULL;
}
int main(int argc,char* argv[])
{
    pthread_t pthid;
    long thret;
    int ret=pthread_create(&pthid,NULL,threadfunc,NULL);
    THREAD_ERROR_CHECK(ret,"pthread_create");
    //sleep(5);
    ret=pthread_cancel(pthid);
    THREAD_ERROR_CHECK(ret,"pthread_cancel");
    ret=pthread_join(pthid,(void**)&thret);
    THREAD_ERROR_CHECK(ret,"pthread_join");
    printf("I am main thread,return value=%ld\n",thret);
    return 0;
}

