/*************************************************************************
	> FileName  : NameSpace.cpp
	> Author    : zhouzhijun
	> Mail      : snjzzjun@163.com
	> CreateTime: 2019年06月11日 星期二 19时18分22秒
*************************************************************************/

#include <iostream>
using namespace std;

namespace Zjzhou 
{
    class Student 
    {
    public:
        char *name;
        int age;
        float score;

        void displayStudent(void)
        {
            cout << "name: " << name << "age: " << age << "score: " << score << endl;
        }
    };
}

int main(int argc, char *argv[])
{
    Zjzhou::Student stu;

    stu.name = "zzj";
    stu.age = 20;
    stu.score = 92.1;

    stu.displayStudent();

    return 0;
}
