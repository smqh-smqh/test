#include <func.h>

int main(int argc,char* argv[])
{
    int semArrId=semget(1000,2,IPC_CREAT|0600);
    ERROR_CHECK(semArrId,-1,"semget");    
    unsigned short arr[2]={10,0};
    int ret;
    ret=semctl(semArrId,0,SETALL,arr);
    ERROR_CHECK(ret,-1,"semctl");
    struct sembuf sopp,sopv;
    if(!fork())
    {
        while(1)
        {
            sopp.sem_num=1;
            sopp.sem_op=-1;
            sopp.sem_flg=SEM_UNDO;
            sopv.sem_num=0;
            sopv.sem_op=1;
            sopv.sem_flg=SEM_UNDO;
            printf("I am consumer space num=%d,product num=%d\n",semctl(semArrId,0,GETVAL),semctl(semArrId,1,GETVAL));
            semop(semArrId,&sopp,1);
            printf("I am consumer space num=%d,product num=%d\n",semctl(semArrId,0,GETVAL),semctl(semArrId,1,GETVAL));
            printf("consume success\n");
            semop(semArrId,&sopv,1);
            printf("I am consumer space num=%d,product num=%d\n",semctl(semArrId,0,GETVAL),semctl(semArrId,1,GETVAL));
            sleep(2);
        }
    }else
    {

        while(1)
        {   
            sopp.sem_num=0;
            sopp.sem_op=-1;
            sopp.sem_flg=SEM_UNDO;
            sopv.sem_num=1;
            sopv.sem_op=1;
            sopv.sem_flg=SEM_UNDO;
            printf("I am productor space num=%d,product num=%d\n",semctl(semArrId,0,GETVAL),semctl(semArrId,1,GETVAL));
            semop(semArrId,&sopp,1);
            printf("I am productor space num=%d,product num=%d\n",semctl(semArrId,0,GETVAL),semctl(semArrId,1,GETVAL));
            printf("product success\n");
            semop(semArrId,&sopv,1);
            printf("I am productor space num=%d,product num=%d\n",semctl(semArrId,0,GETVAL),semctl(semArrId,1,GETVAL));
            sleep(1);
        }   
    }
    return 0;
}

