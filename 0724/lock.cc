#include <unistd.h>
#include <pthread.h>
#include <iostream>
using std::cout;
using std::endl;

pthread_mutex_t mutex;
class MutexLock
{
public:
    static MutexLock * getInstance()
    {
        if(pInstance==nullptr)
        {
            pInstance=new MutexLock();
        }
        return pInstance;
    }

    static void destroy()
    {
        if(pInstance)
        {
            delete pInstance;
        }
    }
    void lock()
    {
        cout<<"lock()"<<endl;
        pthread_mutex_lock(&mutex);
    }
    void unlock()
    {
        cout<<"unlock()"<<endl;
        pthread_mutex_unlock(&mutex);
    }
private:
    MutexLock()
    {
        pthread_mutex_init(&mutex,NULL);
    }
    ~MutexLock(){pthread_mutex_destroy(&mutex);}
    static MutexLock *pInstance;
};

MutexLock * MutexLock::pInstance=nullptr;

class Condition
{
public:
    static Condition * getInstance()
    {
        if(nullptr==pConInstance)
        {
            pConInstance=new Condition();
        }
        return pConInstance;
    }

    void wait()
    {
        cout<<"wait()"<<endl;
        pthread_cond_wait(&con,&mutex);
    }
    void notify()
    {
        cout<<"notify()"<<endl;
        pthread_cond_signal(&con);
    }
    void notifyall();
private:
    Condition(){pthread_cond_init(&con,NULL);}
    ~Condition(){pthread_cond_destroy(&con);};
    static Condition * pConInstance;
    pthread_cond_t con;
    
};

Condition * Condition::pConInstance=nullptr;

typedef struct mc{
    int i;
    MutexLock * mutex;
    Condition * con;
}mc_t,*pmc_t;

void * threadFunc(void *p)
{
    mc_t * thInfo=(mc_t *)p;
    while(1){
        thInfo->mutex->lock();
        if(0==thInfo->i)
        {
            thInfo->con->wait();
        }
        cout<<"i="<<thInfo->i<<endl;
        if(1==thInfo->i){thInfo->i--;}
        cout<<"i="<<thInfo->i<<endl;
        thInfo->mutex->unlock();
    }
}


int main()
{
    pmc_t p;
    p->i=1;
    p->mutex=MutexLock::getInstance();
    p->con=Condition::getInstance();
    pthread_t pth1,pth2;
    pthread_create(&pth1,NULL,threadFunc,p);
    pthread_create(&pth2,NULL,threadFunc,p);
    for(int i=0;i<5;i++)
    {
        p->i=1;
        sleep(1);
        p->con->notify();
    }
    pthread_join(pth1,NULL);
    pthread_join(pth2,NULL);
    
    return 0;
}

