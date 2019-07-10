/*************************************************************************
	> FileName  : ReferenceTempData.cpp
	> Author    : zhouzhijun
	> Mail      : snjzzjun@163.com
	> CreateTime: 2019年07月06日 星期六 13时55分49秒
*************************************************************************/

#include <iostream>
#include <string>

using namespace std;

class People {
protected:
    string m_name;
    int m_age;
	
public:
    void show(void);
};

void People::show(void)
{
    cout << m_name << "的年龄是" << m_age << endl;
}

/******************************************************************************************
 using 只能改变基类中 public 和 protected 成员的访问权限，不能改变 private 成员的访问权限，
 因为基类中 private 成员在派生类中是不可见的，根本不能使用，所以基类中的 private 成员在派
 生类中无论如何都不能访问。
******************************************************************************************/
class Student: public People {
private:
	/* 改变成员函数的方法的书写形式 */
    //using People::show;  //将public改为private

public:
    using People::m_name;  //将private改为public
    using People::m_age;  //将private改为public
    float m_score;
	
	void learning(void);
};

void Student::learning(void) {
    cout << "我是" << m_name << "，今年" << m_age << "岁，这次考了" << m_score << "分" << endl;
}

int main(){
    Student stu;
	
    stu.m_name = "小明";
    stu.m_age = 16;
    stu.m_score = 99.5f;
    stu.show();
    stu.learning();
	
    return 0;
}