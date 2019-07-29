#include <func.h>
#define N 20000000
typedef struct{
    int val;
    pthread_mutex_t mutex;
}Data_t,*pData_t;

int main(int argc,char* argv[])
{
    int shmid;
    shmid=shmget(1000,1<<20,IPC_CREAT|0600);
    ERROR_CHECK(shmid,-1,"shmid");
    pData_t p;
    p=(pData_t)shmat(shmid,NULL,0);
    ERROR_CHECK(p,(pData_t)-1,"shmat");
    p->val=0;
    pthread_mutexattr_t mattr;
    pthread_mutexattr_init(&mattr);
    int ret= pthread_mutexattr_setpshared(&mattr,PTHREAD_PROCESS_SHARED);
    THREAD_ERROR_CHECK(ret,"pthread_mutexattr_setpshared");
    ret= pthread_mutex_init(&p->mutex,&mattr);
    THREAD_ERROR_CHECK(ret,"pthread_mutex_init");
    struct timeval start,end;
    gettimeofday(&start,NULL);
    if(!fork())
    {
        for(int i=0;i<N;i++){
        pthread_mutex_lock(&p->mutex);
        p->val+=1;
        pthread_mutex_unlock(&p->mutex);
        }
    }else
    {
        for(int j=0;j<N;j++){
        pthread_mutex_lock(&p->mutex);
        p->val+=1;
        pthread_mutex_unlock(&p->mutex);
        }
    
    wait(NULL);
    gettimeofday(&end,NULL);
    printf("sum=%d,time=%ld\n",p->val,(end.tv_sec-start.tv_sec)*1000000+end.tv_usec-start.tv_usec);
    }
    ret=shmctl(shmid,IPC_RMID,0);
    ERROR_CHECK(ret,-1,"shmctl");
    return 0;
}

