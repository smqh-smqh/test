#include <iostream>
using std::cout;
using std::endl;

#define SIZE 10
class Queue
{
public:
    Queue()
    {
        cout<<"Queue()"<<endl;
        front=0;
        rear=0;
        for(int i=0;i<SIZE;i++)
        {
            arr[i]=0;
        }
    }

    bool full()
    {
        if((rear+1)%SIZE==front)
        {
            return 1;
        }
        return 0;
    }

    bool empty()
    {
        if(front==rear){return 1;}
        return 0;
    }
    
    void push(int val)
    {
        if(!full()){
        arr[rear]=val;
        rear++;
        rear%=SIZE;
        cout<<val<<" push queue"<<endl;
        }
    }
    
    void pop()
    {
        if(!empty())
        {
        cout<<arr[front]<<" pop queue"<<endl;
        front++;
        front%=SIZE;
        }
    }

    int getFront()
    {
        if(!empty())
        {
            return arr[front];
        }
        else
        {
             cout<<"queue empty"<<endl;
        }
    
    }

    int getBack()
    {
        if(!empty())
        {
            return arr[rear-1];
        }
        else
        {
            cout<<"queue empty"<<endl;
        }
    }


private:
    int front;
    int rear;
    int arr[SIZE];
};



int main()
{
    Queue q;
    q.push(10);
    q.push(12);
    q.push(14);
    int f=q.getFront();
    int b=q.getBack();
    cout<<"queue front is "<<f<<endl;
    cout<<"queue back is "<<b<<endl;
    q.pop();
    f=q.getFront();
    b=q.getBack();
    cout<<"queue front is "<<f<<endl;
    cout<<"queue back is "<<b<<endl;
    
    return 0;
}

