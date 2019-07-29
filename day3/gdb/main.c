#include<stdio.h>
#include<stdlib.h>
#define NUM 2+3
void print(int k)
{
	printf("I am print k=%d\n",k);
	printf("I am print k=%d\n",k);
	printf("I am print k=%d\n",k);
}
int main(int argc,char* argv[])
{
	if(argc!=3)
	{
		printf("error args\n");
		return -1;
	}
	int *p;
	int arr[3]={1,2,3};
	int i=atoi(argv[0]);
	int j=atoi(argv[1]);
	arr[2]=4;
	p=arr;
	print(j);
	for(i=0;i<5;i++)
	{
		printf("hello world\n");
	}		
	return 0;
}
