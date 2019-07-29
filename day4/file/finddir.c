#include<func.h>

int findDir(char *path,char *file)
{
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
		if(!strcmp(p->d_name,file))
		printf("%s\n",buf);
		if(4==p->d_type)
		{
		findDir(buf,file);
		}
	}
	closedir(dir);
	return 0;
}
int main(int argc,char *argv[])
{
	ARGS_CHECK(argc,3);
	findDir(argv[1],argv[2]);
	return 0;
}
