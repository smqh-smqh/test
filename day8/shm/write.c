#include <func.h>

int main(int argc,char* argv[])
{
     int shmid;
     shmid=shmget(1000,1024,IPC_CREAT|0666);
     ERROR_CHECK(shmid,-1,"shmget");
     char *p=(char*)shmat(shmid,NULL,0);
     ERROR_CHECK(p,(char*)-1,"shmat");
     memset(p,0,1024);
     strcpy(p,"How are you");
     int ret=shmdt(p);
     ERROR_CHECK(ret,-1,"shmdt");
    return 0;
}

