#include <func.h>

int main(int argc,char* argv[])
{
    if(!fork())
    {
        printf("I am child %d\n",getpid());
    }else
    {
        int status;
        pid_t pid;
        pid=wait(&status);
        printf("I am parent child id =%d\n",pid);
        if(WIFEXITED(status))
        {
            printf("exit code=%d\n",WEXITSTATUS(status));
        }else
        {
            printf("child crash\n");
        }
    }
    return 0;
}

