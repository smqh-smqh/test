#include <func.h>

typedef struct student{
    int num;
    char name[20];
    float score;
}Student_t,*pStudent_t;

int main(int argc,char* argv[])
{
    ARGS_CHECK(argc,2);
    int i=0,len=0;
    char buf[256]={0};
    char buf1[256]={0};
    struct student s[3];
    for(i=0;i<3;i++){
        printf("enter the number %d student information:\n",i);
        scanf("%d%s%f",&s[i].num,&s[i].name,&s[i].score);
    }
    int fd=open(argv[1],O_RDWR|O_TRUNC);
    ERROR_CHECK(fd,-1,"open");
    for(i=0;i<3;i++){
        sprintf(buf+len,"%03d%10s%10.2f",s[i].num,s[i].name,s[i].score);
        write(fd,buf+len,strlen(buf+len));
        len=strlen(buf)*(i+1);
        write(fd,"\n",1);
    }
    lseek(fd,0,SEEK_SET);
   // len/=3;
   // for(i=0;i<3;i++){
      read(fd,buf1,len+1);
      printf("%s",buf1);
   // }
    return 0;
}

