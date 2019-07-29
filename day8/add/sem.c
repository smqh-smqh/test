#include <func.h>
#define N 10000000
int main(int argc,char* argv[])
{
    int semid;
    semid=semget(1000,1,IPC_CREAT|0600);
    ERROR_CHECK(semid,-1,"semget");
    int shmid;
    shmid=shmget(1000,1024,IPC_CREAT|0600);
    ERROR_CHECK(shmid,-1,"shmid");
    int *p=(int *)shmat(shmid,NULL,0);
    ERROR_CHECK(p,(int*)-1,"shmat");
    int ret=semctl(semid,0,SETVAL,1);
    ERROR_CHECK(ret,-1,"semctl");
    struct sembuf semp,semv;
    semp.sem_num=0;
    semp.sem_op=-1;
    semp.sem_flg=SEM_UNDO;
    semv.sem_num=0;
    semv.sem_op=1;
    semv.sem_flg=SEM_UNDO;
    *p=0;
    if(!fork())
    {
        for(int i=0;i<N;i++){
            semop(semid,&semp,1);
            p[0]=p[0]+1;
            semop(semid,&semv,1);
        }
    }else
    {
        for(int j=0;j<N;j++){
            semop(semid,&semp,1);
            p[0]=p[0]+1;
            semop(semid,&semv,1);
        }
    
    wait(NULL);
    printf("sum=%d\n",p[0]);
    }
    ret=shmctl(shmid,IPC_RMID,0);
    ERROR_CHECK(ret,-1,"shmctl");
    return 0;
}

