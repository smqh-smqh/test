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
    pthread_t pthid[N];
    long thret;
    pData_t p=(pData_t)malloc(sizeof(Data_t));
    pthread_mutex_init(&p->mutex,NULL);
    pthread_cond_init(&p->con,NULL);
    int ret,i;
    for(i=0;i<N;i++){
        ret=pthread_create(pthid+i,NULL,threadfunc,p);
        THREAD_ERROR_CHECK(ret,"pthread_create");
    }

    for(i=0;i<N;i++){
        ret=pthread_cancel(pthid[i]);
        THREAD_ERROR_CHECK(ret,"pthread_cancel");
    }

    for(i=0;i<N;i++){
        ret=pthread_join(pthid[i],(void**)&thret);
        THREAD_ERROR_CHECK(ret,"pthread_join");
    }
    printf("I am main thread,return value=%ld\n",thret);
    return 0;
}

