#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/types.h>
#include <dirent.h>
#include <time.h>
#include <pwd.h>
#include <grp.h>
#include <fcntl.h>
#include <sys/select.h>
#include <sys/wait.h>
#include <sys/signal.h>
#include <sys/mman.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/msg.h>
#include <sys/sem.h>
#include <sys/time.h>
#include <signal.h>
#include <strings.h>
#include <sys/time.h>
#include <pthread.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <sys/epoll.h>
#include <fcntl.h>
#include <sys/sendfile.h>

#define ARGS_CHECK(argc,val){if (argc!=val) {printf("error args\n"); return -1;}}
#define ERROR_CHECK(ret,retVal,funcName){if(ret==retVal){perror(funcName);return -1;}}
#define THREAD_ERROR_CHECK(ret,funcName){if(ret!=0){printf("%s:%s",funcName,strerror(ret));return -1;}}

#define FILENAME "file"
typedef struct{
    pid_t pid;//子进程pid
    int pipeFd;//子进程的管道对端
    short busy;
}process_data_t;

typedef struct{
    int dataLen;
    char buf[1000];
}train_t;

int tcp_init(int*,char*,char*);
int recvFd(int,int*);
int sendFd(int,int);
int epollInAdd(int,int);
int tranfile(int);


