#include <func.h>

int main(int argc,char* argv[])
{
    ARGS_CHECK(argc,2);
    int fdw=open(argv[1],O_WRONLY);
    printf("I am writer fdw=%d\n",fdw);
    write(fdw,"cool",4);
    return 0;
}

