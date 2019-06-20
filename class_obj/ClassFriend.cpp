/*************************************************************************
	> FileName  : ClassFriend.cpp
	> Author    : zhouzhijun
	> Mail      : snjzzjun@163.com
	> CreateTime: 2019年06月20日 星期四 10时15分34秒
*************************************************************************/

#include <iostream>
#include <string>

using namespace std;

class Address;

class Student
{
private:
    string m_name;
    int m_age;
    float m_score;
    
    /* 友元函数可以在类的任意位置进行声明，因为它不是类的成员，不受private和public的影响 */
    friend void ShowStudentInfo(Student *pStu);

public:
    Student(void);
    Student(string name, int age, float score);
    
    /* 友元函数访问私有变量是要指定对象的，否则没法访问，成员函数没有指定对象时因为有隐含的this指针 */
    //friend void ShowStudentInfo(Student *pStu);
    void show(Address *pAddr);
    
    void display(void);    
};

class Address
{
private:
    string m_province;
    string m_city;
    string m_district;
public:
    Address(string province, string city, string district);
    
    /* 可以将一个类的成员函数声明为友元函数 */
    //friend void Student::show(Address *pAddr);
    
    /* 将一个类声明为友元类，这个类的所有成员函数都是友元函数 */
    friend class Student;
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

void Student::show(Address *pAddr)
{
    cout << m_name << ": " << m_age << ", " << m_score << endl;
    cout << "Addr: " << pAddr->m_province << "," << pAddr->m_city << "," << pAddr->m_district << endl;
}

void Student::display(void)
{
    cout << m_name << ":" << m_age << "," << m_score << endl;
}

Address::Address(string province, string city, string district)
{
    m_province = province;
    m_city = city;
    m_district = district;
}

void ShowStudentInfo(Student *pStu)
{
    cout << pStu->m_name << ":" << pStu->m_age << "," << pStu->m_score << endl;
}

int main(int argc, char *argv[])
{
    Student zzj("zzj", 28, 98.8f);
    
    ShowStudentInfo(&zzj);
    
    Student astu("stu", 16, 95.5f);
    Address aaddr("shanxi", "xian", "yanta");
    astu.show(&aaddr);
    
    return 0;
}
