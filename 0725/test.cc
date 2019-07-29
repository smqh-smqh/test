#include <string.h>
#include <iostream>
using std::cin;
using std::cout;
using std::endl;
using std::string;


void process(string & str)
{
    int i=0;
         while(str[i])
    {
        if((str[i]>='A'&&str[i]<='Z')||(str[i]>='a'&&str[i]<='z'))
        {
            if(str[i]>='A'&&str[i]<='Z')
            {
                str[i]+=32;        
            }
        }
        else
        {
            str[i]='\b';
        }
        i++;
    }
         //if(str){cout<<"null"<<endl;}
}
int main()
{
    string word;
    while(cin>>word){
        process(word);
        if(!word.empty())
        cout<<word<<endl;
    }
    return 0;
}

