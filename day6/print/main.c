#include <func.h>

int main(int argc,char* argv[])
{
    printf("current pid=%d,parent pid=%d,user id=%d,user group=%d,effect user id=%d,effect uer group=%d\n",getpid(),getppid(),getuid(),getgid(),geteuid(),getegid());
    return 0;
}

