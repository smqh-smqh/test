#include <func.h>
#include <mysql/mysql.h>
int query(char table[20],char name[25])
{
    MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;
    char* server="localhost";
    char* user="root";
    char* password="root";
    char* database="axing";
    char query[100]={0};
    if(!strcmp(table,"student")){
    strcpy(query,"select sid from ");
    sprintf(query,"%s%s%s%s%s",query,table," where sname ='",name,"'");
    }
    if(!strcmp(table,"teacher")){
    strcpy(query,"select tid from ");
    sprintf(query,"%s%s%s%s%s",query,table," where tname ='",name,"'");
    }
    puts(query);

    int ret,i;
    char id;
    conn=mysql_init(NULL);
    if(!mysql_real_connect(conn,server,user,password,database,0,NULL,0))
    {
        printf("Error connecting to database:%s\n",mysql_error(conn));
        return -1;
    }else{
        printf("connected\n");
    }

    ret=mysql_query(conn,query);
    if(ret){
        printf("Error making query:%s\n",mysql_error(conn));
    }else{
        printf("query sucess\n");
        res=mysql_use_result(conn);
        if(res){
            while((row=mysql_fetch_row(res))!=NULL)
            {
                for(i=0;i<mysql_num_fields(res);i++)
                {
                    printf("%s",row[i]);
                    id=*row[i];
                }
                printf("\n");
            }
        }else{
            printf("no data\n");
        }
        mysql_free_result(res);
    }
    mysql_close(conn);
    return id;
}

int add(char tid,char sid)
{
    MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;
    char* server="localhost";
    char* user="root";
    char* password="root";
    char* database="axing";
    char query[100]={0};
    strcpy(query,"insert into teacher_student values(");
    sprintf(query,"%s%c%s%c%s",query,tid,",",sid,")");
    puts(query);

    int ret;
    conn=mysql_init(NULL);
    if(!mysql_real_connect(conn,server,user,password,database,0,NULL,0))
    {
        printf("Error connecting to database:%s\n",mysql_error(conn));
        return -1;
    }else{
        printf("connected\n");
    }

    ret=mysql_query(conn,query);
    if(ret){
        printf("Error making query:%s\n",mysql_error(conn));
        mysql_close(conn);
        return -1;
    }else{
        printf("insert sucess\n");
    }
    mysql_close(conn);
    return 0;
}


int main(int argc,char* argv[])
{   ARGS_CHECK(argc,3);
    char buf1[20]={0};
    char buf2[20]={0};
    strcpy(buf1,"student");
    strcpy(buf2,argv[2]);
    char sid=query(buf1,buf2);
    strcpy(buf1,"teacher");
    strcpy(buf2,argv[1]);
    char tid=query(buf1,buf2);
    int ret=add(tid,sid);
    if(0==ret)
    printf("选课成功\n");
    return 0;
}

