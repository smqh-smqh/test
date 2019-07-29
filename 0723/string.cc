#include <string.h>
#include <stdlib.h>
#include <iostream>
#include <string>
using std::cout;
using std::endl;

class String
{
public:
    String()
    {
        _pstr=NULL;
        cout<<"String()"<<endl;
    }

    String(const char *pstr)
    :_pstr(new char[strlen(pstr)+1]())
    {
        strcpy(_pstr,pstr);
        cout<<"String(const char *pstr)"<<endl;
    }

    String(const String & rhs)
    :_pstr(new char[strlen(rhs._pstr)+1]())
    {
        strcpy(_pstr,rhs._pstr);
        cout<<"String(const String & rhs)"<<endl;
    }

    String & operator=(const String & rhs)
    {
        if(this!=&rhs){
        delete [] _pstr;
        _pstr=new char[strlen(rhs._pstr)+1]();
        strcpy(_pstr,rhs._pstr);
        cout<<"String & operator=(const String & rhs)"<<endl;
        }
        return *this;
    }

    ~String()
    {
        if(_pstr)
        delete [] _pstr;
        cout<<"~String()"<<endl;
    }

    void print()
    {
        cout<<"_pstr:"<<_pstr<<endl;
    }

private:
    char * _pstr;
};

int main(void)
{
    //String str1;
    //str1.print();
    
    cout<<"str2"<<endl;
    String str2 = "Hello,world";
    cout<<"str3"<<endl;
    String str3("wangdao");

    str2.print();       
    str3.print();   
    
    cout<<"str4"<<endl;
    String str4 = str3;
    str4.print();
    
    str2.print();   
    str4 = str2;
    str4.print();

    return 0;
}
