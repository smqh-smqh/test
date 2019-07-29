#include <func.h>

int main(int argc,char* argv[])
{
     int shmid;
     shmid=shmget(1000,1024,IPC_CREAT|0666);
     ERROR_CHECK(shmid,-1,"shmget");
     char *p=(char*)shmat(shmid,NULL,0);
     ERROR_CHECK(p,(char*)-1,"shmat");
     printf("gets=%s",p);
     int ret=shmctl(shmid,IPC_RMID,0);
     ERROR_CHECK(ret,-1,"shmctl");
    return 0;
}

