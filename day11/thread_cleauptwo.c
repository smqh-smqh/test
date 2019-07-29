#include <func.h>

void cleanup(void* p){
    //free(p);
    printf("cleanup1 free success\n");
}
void cleanup2(void* p){
    //free(p);
    printf("clanup2 free success\n");
}
void* threadfunc(void *p){
    //p=malloc(20);
    pthread_cleanup_push(cleanup,p);
    pthread_cleanup_push(cleanup2,p);
    printf("I am child thread\n");
    pthread_cleanup_pop(1);
    pthread_cleanup_pop(1);
    return NULL;
}
int main(int argc,char* argv[])
{
    pthread_t pthid;
    long thret;
    int ret=pthread_create(&pthid,NULL,threadfunc,NULL);
    THREAD_ERROR_CHECK(ret,"pthread_create");
    ret=pthread_cancel(pthid);
    THREAD_ERROR_CHECK(ret,"pthread_cancel");
    ret=pthread_join(pthid,(void**)&thret);
    THREAD_ERROR_CHECK(ret,"pthread_join");
    printf("I am main thread,return value=%ld\n",thret);
    return 0;
}

