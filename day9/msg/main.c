#include <func.h>

typedef struct msgbuf{
    long mtype;
    char mtext[64];
};
int main(int argc,char* argv[])
{
    int msgid;
    msgid=msgget(1000,IPC_CREAT|0600);
    ERROR_CHECK(msgid,-1,"msgget");
    struct msgbuf msg;
    msg.mtype=1;
    strcpy(msg.mtext,"hello");
    int ret=msgsnd(msgid,&msg,strlen(msg.mtext),0);
    ERROR_CHECK(ret,-1,"msgsnd");
    bzero(&msg,sizeof(msg));
    ret=msgrcv(msgid,&msg,sizeof(msg.mtext),0,0);
    ERROR_CHECK(ret,-1,"msgrcv");
    printf("receive=%s",msg.mtext);
    ret=msgctl(msgid,IPC_RMID,NULL);
    ERROR_CHECK(ret,-1,"msgctl");
    return 0;
}

