#include <string.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

using std::string;
using std::cout;
using std::endl;
using std::ifstream;
using std::vector;
using std::ofstream;

struct Item
{
    Item(const string &w,const int &n)
    :word(w)
    ,num(n)
    {}

    string word;
    int num;
};

vector<Item> dic;
void print()
{
    
    ofstream ofs("dic.txt");
    for(auto & item : dic) 
    {
        ofs<<item.word<<"    "<<item.num<<endl;
    }
    ofs.close();
}

void addDic(string & str)
{
    //cout<<"addDic str "<<str<<endl;
    int flag=0;
    if(!dic.size())
    {
        dic.push_back(Item(str,1));
    }
    else
    {
        for(auto & item : dic)
        {
            if(item.word==str)
            {
                item.num++;
                flag=1;
                break;
            }
            flag=0;
        }
        if(flag==0)
        {
            dic.push_back(Item(str,1));
        }
    }
    //print();
} 

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
    if(str.size()){
        //cout<<"str.size()="<<str.size()<<endl;
        addDic(str);
        //cout << "vec's size = " << dic.size() << endl;
        //cout << "vec's capacity = " << dic.capacity() << endl;
        //cout<<"addDic(str) finish"<<endl;
    }
}

int main()
{
    ifstream ifs;
    ifs.open("/home/xiaoxiao/The_Holy_Bible.txt");
    if(!ifs){
        cout<< "ifsteam open file error!"<<endl;
        return 0;
    }
    string wd;
    while(ifs>>wd)
    {
        process(wd);
    }
    print();
    return 0;
}

