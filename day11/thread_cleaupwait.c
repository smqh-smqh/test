#include <func.h>
typedef struct{
    pthread_cond_t con;
    pthread_mutex_t mutex;
}Data_t,*pData_t;

void cleanup(void* p){
    pData_t pArg=(pData_t)p;
    pthread_mutex_unlock(&pArg->mutex);
    printf("cleanup success\n");
}

void* threadfunc(void *p){
    pData_t pArg=(pData_t)p;
    pthread_mutex_lock(&pArg->mutex);
    pthread_cleanup_push(cleanup,p);
    pthread_cond_wait(&pArg->con,&pArg->mutex);
    printf("wait return\n");
    pthread_cleanup_pop(1);
    printf("I am child thread wake up\n");
    return NULL;
}
#define N 2
int main(int argc,char* argv[])
{
    pthread_t pthid,pthid1;
    long thret;
    pData_t p;
    pthread_mutex_init(&p->mutex,NULL);
    pthread_cond_init(&p->con,NULL);
    int ret,i;
    ret=pthread_create(&pthid,NULL,threadfunc,p);
    THREAD_ERROR_CHECK(ret,"pthread_create");
    ret=pthread_create(&pthid1,NULL,threadfunc,p);
    THREAD_ERROR_CHECK(ret,"pthread_create");

    ret=pthread_cancel(pthid);
    THREAD_ERROR_CHECK(ret,"pthread_cancel");
    ret=pthread_cancel(pthid1);
    THREAD_ERROR_CHECK(ret,"pthread_cancel");

    ret=pthread_join(pthid,(void**)&thret);
    THREAD_ERROR_CHECK(ret,"pthread_join");
    ret=pthread_join(pthid1,(void**)&thret);
    THREAD_ERROR_CHECK(ret,"pthread_join");
    printf("I am main thread,return value=%ld\n",thret);
    return 0;
}

