#include <func.h>

typedef struct{
    int tickts;
    pthread_mutex_t mutex;
    pthread_cond_t con;
}Data_t;

void* threadFunc1(void *p){
    Data_t *pArr=(Data_t*)p;
    while(1){
        pthread_mutex_lock(&(pArr->mutex));
        if(pArr->tickts>0){
            printf("windows1 before sale tickits=%d\n",pArr->tickts);
            pArr->tickts--;
            if(!pArr->tickts){
                pthread_cond_signal(&pArr->con);
            }
            printf("windows1 after sale tickits=%d\n",pArr->tickts);
            pthread_mutex_unlock(&(pArr->mutex));
            sleep(1);
        }else{
            pthread_mutex_unlock(&(pArr->mutex));
            break; 
        }
    }
    return NULL;
}
void* threadFunc2(void *p){
    Data_t *pArr=(Data_t*)p;
    while(1){
        pthread_mutex_lock(&(pArr->mutex));
        if(pArr->tickts>0){
            printf("windows2 before sale tickits=%d\n",pArr->tickts);
            pArr->tickts--;
            if(!pArr->tickts){
                pthread_cond_signal(&pArr->con);
            }
            printf("windows2 after sale tickits=%d\n",pArr->tickts);
            pthread_mutex_unlock(&(pArr->mutex));
            sleep(1);
        }else{
            pthread_mutex_unlock(&(pArr->mutex));
            break; 
        }

    }
    return NULL;
}
void* threadFunc3(void *p){
    Data_t *pArr=(Data_t*)p;
    pthread_mutex_lock(&(pArr->mutex));
    if(pArr->tickts>0){
        pthread_cond_wait(&pArr->con,&pArr->mutex);
    }
    pArr->tickts=20;
    pthread_mutex_unlock(&(pArr->mutex));
    pthread_exit(NULL);
}
int main(int argc,char* argv[])
{
    pthread_t p1,p2,p3;
    Data_t *p;
    int ret;
    p->tickts=20;
    int i=0;
    pthread_mutex_init(&(p->mutex),NULL);
    pthread_cond_init(&p->con,NULL);
    ret=pthread_create(&p1,NULL,threadFunc1,p);
    THREAD_ERROR_CHECK(ret,"pthread_create");
    ret=pthread_create(&p2,NULL,threadFunc2,p);
    THREAD_ERROR_CHECK(ret,"pthread_create");
    ret=pthread_create(&p3,NULL,threadFunc3,p);
    THREAD_ERROR_CHECK(ret,"pthread_create");
    ret=pthread_join(p1,NULL);
    THREAD_ERROR_CHECK(ret,"pthread_join");
    ret=pthread_join(p2,NULL);
    THREAD_ERROR_CHECK(ret,"pthread_join");
    printf("sale over\n");
    return 0;
}

