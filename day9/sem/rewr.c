#include <func.h>

int main(int argc,char* argv[])
{
    int semArrId=semget(1000,3,IPC_CREAT|0600);
    ERROR_CHECK(semArrId,-1,"semget");    
    unsigned short arr[3]={1,1,1};
    int ret;
    int count=0;
    ret=semctl(semArrId,0,SETALL,arr);
    ERROR_CHECK(ret,-1,"semctl");
    struct sembuf sopp,sopv;
    if(!fork())
    {
        if(!fork()){
            while(1)
            {
                sopp.sem_num=1;
                sopp.sem_op=-1;
                sopp.sem_flg=SEM_UNDO;
                sopv.sem_num=2;
                sopv.sem_op=1;
                sopv.sem_flg=SEM_UNDO;
                semop(semArrId,&sopp,1);
                sopp.sem_num=2;
                semop(semArrId,&sopp,1);
                if(count==0){
                    sopp.sem_num=0;
                    semop(semArrId,&sopp,1);
                }
                count++;
                printf("I am reader num=%d\n",count);
                semop(semArrId,&sopv,1);
                sopv.sem_num=1;
                semop(semArrId,&sopv,1);
                printf("reading...\n");

                sopp.sem_num=2;
                semop(semArrId,&sopp,1);
                count--;
                if(count==0){
                    sopv.sem_num=0;
                    semop(semArrId,&sopv,1);
                }
                printf("after reading,left reader num=%d\n",count);
                sopv.sem_num=2;
                semop(semArrId,&sopv,1);
                sleep(1);
            }
        }
        else{
            while(1)
            {
                sopp.sem_num=1;
                sopp.sem_op=-1;
                sopp.sem_flg=SEM_UNDO;
                sopv.sem_num=2;
                sopv.sem_op=1;
                sopv.sem_flg=SEM_UNDO;
                semop(semArrId,&sopp,1);
                sopp.sem_num=2;
                semop(semArrId,&sopp,1);
                if(count==0){
                    sopp.sem_num=0;
                    semop(semArrId,&sopp,1);
                }
                count++;
                printf("I am reader num=%d\n",count);
                semop(semArrId,&sopv,1);
                sopv.sem_num=1;
                semop(semArrId,&sopv,1);
                printf("reading...\n");

               // sleep(3);
                sopp.sem_num=2;
                semop(semArrId,&sopp,1);
                count--;
                if(count==0){
                    sopv.sem_num=0;
                    semop(semArrId,&sopv,1);
                }
                printf("after reading,left reader num=%d\n",count);
                sopv.sem_num=2;
                semop(semArrId,&sopv,1);
                sleep(1);
            }
        }

    }else
    {
        while(1)
        {   
            sopp.sem_num=1;
            sopp.sem_op=-1;
            sopp.sem_flg=SEM_UNDO;
            sopv.sem_num=0;
            sopv.sem_op=1;
            sopv.sem_flg=SEM_UNDO;
            semop(semArrId,&sopp,1);
            sopp.sem_num=0;
            semop(semArrId,&sopp,1);
            printf("before writing..\n");
            printf("writing...\n");
            printf("after writing...\n");
            semop(semArrId,&sopv,1);
            sopv.sem_num=1;
            semop(semArrId,&sopv,1);
            sleep(2);

        }   
    }
    return 0;
}

