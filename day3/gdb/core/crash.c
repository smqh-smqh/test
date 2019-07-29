#include<stdio.h>
#include<stdlib.h>
#define NUM 2+3
void print(int k)
{
	char *p=NULL;
	*p='H';
	printf("I am print k=%d\n",k);
}
int main(int argc,char* argv[])
{
	int *p;
	int arr[3]={1,2,3};
	int i=3;
	int j=4;
	arr[2]=4;
	p=arr;
	print(j);
	for(i=0;i<5;i++)
	{
		printf("hello world\n");
	}		
	return 0;
}
