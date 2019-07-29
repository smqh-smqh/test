#include <func.h>

typedef struct{
    int tickts;
    pthread_mutex_t mutex;
}Data_t;

void* threadFunc1(void *p){
    Data_t *pArr=(Data_t*)p;
    int i=0;
    while(1){
        pthread_mutex_lock(&(pArr->mutex));
        if(pArr->tickts>0){
            //printf("windows1 before sale tickits=%d\n",pArr->tickts);
            pArr->tickts--;
            i++;
            //printf("windows1 after sale tickits=%d\n",pArr->tickts);
            pthread_mutex_unlock(&(pArr->mutex));
        }else{
            pthread_mutex_unlock(&(pArr->mutex));
            printf("widows1 %d",i);
            pthread_exit(NULL);
        }
    }
}
void* threadFunc2(void *p){
    Data_t *pArr=(Data_t*)p;
    int i=0;
    while(1){
        pthread_mutex_lock(&(pArr->mutex));
        if(pArr->tickts>0){
           // printf("windows2 before sale tickits=%d\n",pArr->tickts);
            pArr->tickts--;i++;
            //printf("windows2 after sale tickits=%d\n",pArr->tickts);
            pthread_mutex_unlock(&(pArr->mutex));
        }else{
            pthread_mutex_unlock(&(pArr->mutex));
            printf("widows2 %d",i);
            pthread_exit(NULL);
        }

    }
}
int main(int argc,char* argv[])
{
    pthread_t p1,p2;
    Data_t *p;
    int ret;
    p->tickts=2000000;
    pthread_mutex_init(&(p->mutex),NULL);
    ret=pthread_create(&p1,NULL,threadFunc1,p);
    THREAD_ERROR_CHECK(ret,"pthread_create");
    ret=pthread_create(&p2,NULL,threadFunc2,p);
    THREAD_ERROR_CHECK(ret,"pthread_create");
    ret=pthread_join(p1,NULL);
    THREAD_ERROR_CHECK(ret,"pthread_join");
    ret=pthread_join(p2,NULL);
    THREAD_ERROR_CHECK(ret,"pthread_join");
    printf("sale over\n");
    return 0;
}

