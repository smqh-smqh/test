#ifndef _FACTORY_H_
#define _FACTORY_H_
#include "head.h"
#include "work_que.h"

typedef struct{
    Que_t que;
    pthread_cond_t cond;
    pthread_t *pid;
    int pthnum;
    short startFlag;
}Factory_t,*pFactory_t;

int factoryInit(pFactory_t,int,int);
int factoryStart(pFactory_t);
int tcp_init(int*,char*,char*);
#endif
