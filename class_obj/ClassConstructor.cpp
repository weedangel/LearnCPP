/*************************************************************************
	> FileName  : ClassConstructor.cpp
	> Author    : zhouzhijun
	> Mail      : snjzzjun@163.com
	> CreateTime: 2019年06月18日 星期二 15时01分09秒
*************************************************************************/

//#include <cstdlib>
#include <iostream>
#include <string>
using namespace std;

class Student
{
private:
    string m_name;
    int m_age;
    float m_score;

public:
    Student(void);
    Student(string name, int age, float score);
    void display(void);    
};

Student::Student(void)
{
    m_name = "default";
    m_age = 20;
    m_score = 60.0; 
    cout << "default constructor call" << endl;
}

Student::Student(string name, int age, float score)
{
    m_name = name;
    m_age = age;
    m_score = score;
    cout << "param constructor call" << endl;
}

void Student::display(void)
{
    cout << m_name << ":" << m_age << "," << m_score << endl;
}

int main(int argc, char *argv[])
{
    Student stu;
    stu.display();
    
    /* 无参构造函数声明变量时不能使用括号,使用的话编译器会当作函数声明来处理 */
    //Student zza();
    //zza.display();
    
    Student *zza = NULL;
    
    /* 一下两种声明的方法都可以使用 */
    //zza = new Student;
    zza = new Student();
    zza->display();
    delete zza;
    
    Student zzj("zzj", 28, 98.2);
    zzj.display();
    
    return 0;
}
