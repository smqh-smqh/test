#include <func.h>
#define SHM_HUGE_2MB (1<<21)
int main(int argc,char* argv[])
{
     int shmid;
     int fd = open(argv[1],O_RDWR);
     shmid=shmget(1000,1<<21,IPC_CREAT|0666|SHM_HUGETLB|SHM_HUGE_2MB);
     ERROR_CHECK(shmid,-1,"shmget");
     char *p=(char*)shmat(shmid,NULL,0);
     ERROR_CHECK(p,(char*)-1,"shmat");
     memset(p,0,1024);
     strcpy(p,"How are you");
     write(fd,p,1<<21);
     int ret=shmdt(p);
     ERROR_CHECK(ret,-1,"shmdt");
    return 0;
}

