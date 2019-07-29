#include <mysql/mysql.h>
#include <func.h>

int main(int argc,char* argv[])
{
    ARGS_CHECK(argc,3);
    MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;
    char* server="localhost";
    char* user="root";
    char* password="root";
    char* database="axing";
    char query[100]={0};
    strcpy(query,"update ");
    sprintf(query,"%s%s%s%s%s%s",query,argv[1]," set sname"," ='",argv[2],"' where sid=1");
    puts(query);

    int ret,i;
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
        printf("update sucess\n");
       // res=mysql_use_result(conn);
       // if(res){
       //     while((row=mysql_fetch_row(res))!=NULL)
       //     {
       //         for(i=0;i<mysql_num_fields(res);i++)
       //         {
       //             printf("%-8s ",row[i]);
       //         }
       //         printf("\n");
       //     }
       // }else{
       //     printf("no data\n");
       // }
       // mysql_free_result(res);
    }
    mysql_close(conn);
    return 0;
}

