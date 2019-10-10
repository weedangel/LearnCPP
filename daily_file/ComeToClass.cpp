/*************************************************************************
	> FileName  : ComeToClass.cpp
	> Author    : zhouzhijun
	> Mail      : snjzzjun@163.com
	> CreateTime: 2019年08月22日 星期四 10时03分18秒
*************************************************************************/

#include <iostream>
using namespace std;

unsigned int comeToClass[] = 
{
    20190526, 20190627, 20190803, 20190902,
    20191004, 2019
};

int main(int argc, char *argv[])
{
    int i = 0;
    
    cout << "Mrs. Dai, I love you!" << endl;
    cout << "Come to class time: " << endl;
    for (i = 0; i < sizeof(comeToClass)/ sizeof(comeToClass[0]); i++)
    {
        
        if (((i + 1) % 4) == 0)
        {
            cout << comeToClass[i] << endl;
        }
        else
        {
            cout << comeToClass[i] << ", ";
        }
    }
    
    if (i % 4)
    {
        cout << endl;
    }
    cout <<"All class time" << endl;
    
    return 0;
}