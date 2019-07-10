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

void People::show(void) {
	cout << "嗨，大家好，我叫" << m_name << "，今年" << m_age << "岁" << endl;
}

class Student: public People {
private:
	float m_score;
	 
public:
	Student(string name, int age, float score);
	
	void show(void); //遮蔽基类的show()
};

Student::Student(string name, int age, float score) {
	m_name = name;
    m_age = age;
    m_score = score;	
}

void Student::show(void) {
	cout << m_name << "的年龄是" << m_age << "，成绩是" << m_score << endl;
}

int main(int argc, char *argv[])
{
	Student stu("小明", 16, 90.5);
	
    //使用的是派生类新增的成员函数，而不是从基类继承的
    stu.show();
	
    //使用的是从基类继承来的成员函数
    stu.People::show();
	
    return 0;
}