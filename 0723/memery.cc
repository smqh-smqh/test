#include <stdio.h>
 #include <stdlib.h>
#include <string.h>
#include <iostream>

int a=0;
char* p1;
int main()
{
    char p2[]="hello";
    const char * p3="hello";
    p1=(char*)malloc(6);
    strcpy(p1,"hello");
    std::cout << p1 << std::endl;
    p1[0]='H';
    p2[0]='H';
    p3[0]='H';
    std::cout << p1 << std::endl;
    std::cout << p2 << std::endl;
    std::cout << p3 << std::endl;
    return 0;
}

