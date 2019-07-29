#include <string.h>
#include <iostream>
using std::cout;
using std::endl;

class Student
{
public:
    Student(int id,const char * name)
    :_id(id)
    ,_name(new char[strlen(name)+1]())
    {
        cout<<"Student(int ,char *)"<<endl;
        strcpy(_name,name);
    }

    ~Student()
    {
        cout<<"~Student()"<<endl;
        if(_name)
        {
            delete []_name;
            _name=nullptr;
        }
    }

    void print() const
    {
        cout<<"_id="<<_id<<endl
            <<"_name="<<_name<<endl;
    
    }

private:
    void * operator new(size_t);
    void operator delete(void*);
    int _id;
    char * _name;
};

int main()
{
    Student s1(101,"Jack");
    s1.print();

   // Student * p=new Student(102,"Helen");//error
   // p->print();
   // delete(p);
    return 0;
}

