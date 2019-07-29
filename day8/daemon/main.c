#include <func.h>

int main(int argc,char* argv[])
{
    int fd;
    fd=open("file",O_CREAT|O_RDWR);
    ERROR_CHECK(fd,-1,"open");
    if(fork())
    {
        exit(0);
    }
    setsid();
    for(int i=0;i<3;i++)
    {
        close(i);
    }
    chdir("/");
    umask(0);
    while(1){
        int ret= write(fd,"wohenshuai\n",11);
        ERROR_CHECK(ret,-1,"write");
        sleep(60);
    }
    return 0;
}

