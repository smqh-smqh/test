#include <iostream>
using std::cin;
using std::cout;
using std::endl;

int main()
{

        char ch[20];
        cout << "enter a sentence:" << endl;
        cin >> ch;
        cout << "The string read with cin is:" << ch << endl;
        cin.getline(ch, 20, '/');//读19个字符或遇′/′结束
        cout << "The second part is:" << ch << endl;
        cin.getline(ch,20);                              //读19个字符或遇′/n′结束
        cout << "The third part is:" << ch << endl;
    return 0;
}

