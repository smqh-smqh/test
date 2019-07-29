#include <func.h>

typedef struct{
    int val;
    pthread_mutex_t mutex;
}Data_t;
#define N 200000000

void* func(void *p){
    Data_t* pArg=(Data_t*)p;
    for(int i=0;i<N;i++){
    pthread_mutex_lock(&pArg->mutex);
        pArg->val+=1;
    pthread_mutex_unlock(&pArg->mutex);
    }
}
int main(int argc,char* argv[])
{
    Data_t data;
    pthread_t pthid;
    struct timeval start,end;
    data.val=0;
    int ret= pthread_mutex_init(&data.mutex,NULL);
    THREAD_ERROR_CHECK(ret,"pthread_mutex_init");
    gettimeofday(&start,NULL);
    ret=pthread_create(&pthid,NULL,func,&data);
    THREAD_ERROR_CHECK(ret,"pthread_create_");
    for(int i=0;i<N;i++){
    pthread_mutex_lock(&data.mutex);
        data.val+=1;
    pthread_mutex_unlock(&data.mutex);
    }
    pthread_join(pthid,NULL);
    gettimeofday(&end,NULL);
    printf("sum=%d,time=%ld\n",data.val,(end.tv_sec-start.tv_sec)*1000000+end.tv_usec-start.tv_usec);
    return 0;
}

