#include "factory.h"

void cleanup(void *p)
{
    pQue_t pq=(pQue_t)p;
    pthread_mutex_unlock(&pq->mutex);
}
void* threadFunc(void* p){
    pFactory_t pf=(pFactory_t)p;
    pQue_t pq=&pf->que;
    pNode_t pCur;
    int getSuccess;
    
    while(1){
        pthread_mutex_lock(&pq->mutex);
        pthread_cleanup_push(cleanup,pq);
        if(!pq->queSize)
        {
            pthread_cond_wait(&pf->cond,&pq->mutex);
        }
        getSuccess=queGet(pq,&pCur);
        pthread_cleanup_pop(1);
        if(!getSuccess)
        {
            tranfile(pCur->newFd);
            free(pCur);
        }
        pCur=NULL;
    }

}

int factoryInit(pFactory_t p,int threadNum,int capacity)
{
    queInit(&p->que,capacity);
    pthread_cond_init(&p->cond,NULL);
    p->pid=(pthread_t *)calloc(threadNum,sizeof(pthread_t));
    p->pthnum=threadNum;
    p->startFlag=0;
    return 0;
}

int factoryStart(pFactory_t p){
    int i;
    if(!p->startFlag){
        for(i=0;i<p->pthnum;i++)
        {
            pthread_create(p->pid+i,NULL,threadFunc,p);
            printf("create success,num=%ld\n",*(p->pid+i));
        }
        p->startFlag=1;
    }
    return 0;
}

