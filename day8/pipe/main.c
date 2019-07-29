#include <func.h>

int main(int argc,char* argv[])
{
    int fds[2];
    pipe(fds);
    if(!fork()){
        close(fds[0]);
        write(fds[1],"hello",5);
        exit(0);
    }else{
        char buf[10];
        close(fds[1]);
        read(fds[0],buf,sizeof(buf));
        printf("I am parent,gets= %s",buf); 
    }
    return 0;
}

