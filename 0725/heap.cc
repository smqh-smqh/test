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

    void destroy()
    {
        cout<<"destroy()"<<endl;
        if(this)
        {delete this;}
    }

    void print()
    {
        cout<<"_id="<<_id<<endl
            <<"_name="<<_name<<endl;
    }

private:
    ~Student(){}
    int _id;
    char* _name;
};

int main()
{
   // Student s1(101,"Jack");//error
    //s1.print();
    
    Student * p=new Student(102,"Helen");
    p->print();
    p->destroy();
    return 0;
}

