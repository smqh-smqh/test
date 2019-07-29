#include <func.h>
#define N 10000000
int main(int argc,char* argv[])
{
    int shmid;
    shmid=shmget(1000,1024,IPC_CREAT|0600);
    ERROR_CHECK(shmid,-1,"shmid");
    int *p=(int *)shmat(shmid,NULL,0);
    ERROR_CHECK(p,(int*)-1,"shmat");
    *p=0;
    if(!fork())
    {
        for(int i=0;i<N;i++){
            p[0]=p[0]+1;
        }
    }else
    {
        for(int j=0;j<N;j++){
            p[0]=p[0]+1;
        }
    
    wait(NULL);
    printf("sum=%d\n",p[0]);
    }
    int ret=shmctl(shmid,IPC_RMID,0);
    ERROR_CHECK(ret,-1,"shmctl");
    return 0;
}

