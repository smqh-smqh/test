#include <func.h>

int ls(char* file)
{
    int ret;
    char buff[128]={0};
    char buf1[64]={0};
    struct stat buf;
    ret=stat(file,&buf);
    ERROR_CHECK(ret,-1,"stat");
    sprintf(buff,"%s",ctime(&buf.st_mtime));
    buff[strlen(buff)-5]=0;
    char buf2[10]={0};
    char a[]={'x','w','r'};
    int j=0;
    if(buf.st_mode/16/16/16==8){buf2[0]='-';}
    if(buf.st_mode/16/16/16==4){buf2[0]='d';}
    for(int i=9;i>0;i--){
        j=j%3;
        if(buf.st_mode&1==1){buf2[i]=a[j];}
        else {buf2[i]='-';}
        buf.st_mode>>=1;
        j++;

    }

    sprintf(buf1,"%s",buf2);
    printf("%s %ld %s %s %ld %s %s\n",buf1,buf.st_nlink,getpwuid(buf.st_uid)->pw_name,getgrgid(buf.st_gid)->gr_name,buf.st_size,buff,file);
    return 0;
}

int findDir(char *path)
{
    int ret;
    struct stat buf;
    ret=stat(path,&buf);
    ERROR_CHECK(ret,-1,"stat");
    if((buf.st_mode&S_IFMT)==S_IFREG){
        ls(path);
    }else{
        DIR* dir;
        dir = opendir(path);
        ERROR_CHECK(dir,NULL,"opendir");
        struct dirent *p;
        char buf[1024]={0};
        while(p=readdir(dir))
        {
            if(!strcmp(p->d_name,".")||!strcmp(p->d_name,".."))
            {
                continue;
            }
            sprintf(buf,"%s%s%s",path,"/",p->d_name);
            ls(buf);
        }
    }
    return 0;
}
int main(int argc,char *argv[])
{
    if(argc>1)
        findDir(argv[1]);
    else findDir(".");
    return 0;
}
