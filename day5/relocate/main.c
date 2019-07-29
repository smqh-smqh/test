#include <func.h>
int main(int argc,char* argv[])
{
    ARGS_CHECK(argc,3);
    int fd1,fd2;
    fd1=open(argv[1],O_RDWR);
    ERROR_CHECK(fd1,-1,"open");
    fd2=open(argv[2],O_RDWR);
    printf("\n");
    dup2(STDOUT_FILENO,100);
    dup2(STDERR_FILENO,101);
    fd1=dup2(fd1,STDOUT_FILENO);
    fd2=dup2(fd2,STDERR_FILENO);
    ERROR_CHECK(fd2,2,"open");
    printf("you can't see me\n");
    dup2(100,STDOUT_FILENO);
    dup2(101,STDERR_FILENO);
    //printf("you can see me\n");
    close(fd1);
    close(fd2);
}
