/*************************************************************************
	> FileName  : ReferenceTempData.cpp
	> Author    : zhouzhijun
	> Mail      : snjzzjun@163.com
	> CreateTime: 2019年07月06日 星期六 13时55分49秒
*************************************************************************/

#include <iostream>
#include <string>

using namespace std;

class People
{
private:
	string m_hobby;
	
protected:
    string m_name;
    int m_age;
	
public:
	void setname(string name);
    void setage(int age);
    void sethobby(string hobby);
    string gethobby(void);
};

void People::setname(string name)
{
	m_name = name;	
}

void People::setage(int age)
{
	m_age = age;
}

void People::sethobby(string hobby)
{
	m_hobby = hobby;
}

string People::gethobby(void)
{
	return m_hobby;
}

class Student: public People
{
protected:
    float m_score;
	
public:
    void setscore(float score);
};

void Student::setscore(float score)
{
	m_score = score;
}

class Pupil: public Student
{
private:
    int m_ranking;
	
public:
    void setranking(int ranking);
    void display(void);
};

void Pupil::setranking(int ranking)
{
	m_ranking = ranking;
}

void Pupil::display(void)
{
	cout<<m_name<<"的年龄是"<<m_age<<"，考试成绩为"<<m_score<<"分，班级排名第"<<m_ranking<<"，TA喜欢"<<gethobby()<<"。"<<endl;
}

int main(int argc, char *argv[])
{
	Pupil pup;
	
    pup.setname("小明");
    pup.setage(15);
    pup.setscore(92.5f);
    pup.setranking(4);
    pup.sethobby("乒乓球");
    pup.display();
	
    return 0;
}