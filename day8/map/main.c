#include <func.h>

int main(int argc,char* argv[])
{
    int fd;
    fd=open(argv[1],O_RDWR);
    ftruncate(fd,10);
    ERROR_CHECK(fd,-1,"open");
    char *p=(char*)mmap(NULL,10,PROT_READ|PROT_WRITE,MAP_SHARED,fd,0);
    ERROR_CHECK(p,(char*)-1,"mmap");
    if(!fork())
    {
        printf("I am child p=%s",p);

    }else
    {
        strcpy(p,"hello");
        wait(NULL);

    }
    munmap(p,10);
    return 0;

}
