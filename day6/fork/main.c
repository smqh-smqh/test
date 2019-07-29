#include <func.h>

int main(int argc,char* argv[])
{
    pid_t pid;
    pid=fork();
    if(pid==0){
        printf("I am child mypid=%d,myppid=%d\n",getpid(),getppid());
        while(1);
    }else{
        printf("I am parent mypid=%d,mychild=%d\n",getpid(),pid);
        while(1);
    }
    return 0;
}

