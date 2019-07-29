#include <iostream>
using std::cout;
using std::endl;

class Sigleton{
public:
    static Sigleton * getInstance()
    {
        if(nullptr==_pInstance)
        {
           _pInstance=new Sigleton();
        }
        return _pInstance;
    }

    static void destroy()
    {
        if(_pInstance)
        {
            delete _pInstance;
        }
    }

private:
    Sigleton(){cout<<"Sigleton()"<<endl;}
    ~Sigleton(){cout<<"~Sigleton()"<<endl;}

private:
    static Sigleton * _pInstance;
};

Sigleton*  Sigleton::_pInstance=nullptr;
int main()
{
    Sigleton * p1=Sigleton::getInstance();
    Sigleton * p2=Sigleton::getInstance();
    Sigleton * p3=Sigleton::getInstance();
    cout<<"p1="<<p1<<endl;
    cout<<"p2="<<p2<<endl;
    cout<<"p3="<<p3<<endl;
    Sigleton::destroy();
    return 0;
}

