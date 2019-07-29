#include <iostream>
using std::cout;
using std::endl;

class Stack{
public:
    bool empty()
    {
        if(0==size){return 1;}
        else return 0;
    }

    bool full()
    {
        if(10==size){return 1;}
        else return 0;
    }

    void push(int val)
    {
        if(!full())
        {
            arr[size]=val;
            size++;
            cout<<val<<"push stack"<<endl;
        }
        else
        {cout<<"stack full"<<endl;}
    }

    void pop()
    {
        if(!empty())
        {
            size--;
            cout<<arr[size]<<"pop stack"<<endl;
        }
    }

    int top()
    {
        if(!empty())
        {
            return arr[size-1];
        }
    
    }
    
    Stack()
    {
        cout<<"Stack()"<<endl;
        size=0;
        for(int i=0;i<10;i++)
        {
            arr[i]=0;
        }
    }

private:
    int size;
    int arr[10];
};


int main()
{
    Stack s;
    s.push(10);
    s.push(12);
    s.push(14);
    int top=s.top();
    cout<<"top is "<<top<<endl;
    s.pop();
    top=s.top();
    cout<<"top is "<<top<<endl;

    return 0;
}

