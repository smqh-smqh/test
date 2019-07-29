#include "work_que.h"

void queInit(pQue_t pq,int capacity)
{
    memset(pq,0,sizeof(Que_t));
    pq->queCapacity=capacity;
    pthread_mutex_init(&pq->mutex,NULL);
}
void queInsert(pQue_t pq,pNode_t pNew)
{
    if(NULL==pq->queHead)
    {
        pq->queHead=pq->queTail=pNew;
    }else{
        pq->queTail->next=pNew;
        pq->queTail=pNew;
    }
    pq->queSize++;
}
int queGet(pQue_t pq,pNode_t* pGet )
{
    *pGet=pq->queHead;
    if(NULL== *pGet)
    {
        return -1;
    }
    pq->queHead=pq->queHead->next;
    if(NULL==pq->queHead)
    {
        pq->queTail=NULL;
    }
    pq->queSize--;
    return 0;
}

