/*************************************************************************
	> FileName  : ReferenceTest.cpp
	> Author    : zhouzhijun
	> Mail      : snjzzjun@163.com
	> CreateTime: 2019年08月20日 星期六 8时40分18秒
*************************************************************************/

#include <iostream>

using namespace std;

//基类People
class People{
public:
    /* 构造函数不能声明成虚函数，否者会编译报错（继承时构造函数不能被继承，还有构造函数用于创建对象，调用构造函数的时候对象还不存在，虚函数表也不存在，此时也无法调用虚函数） */
    People(char *name, int age);
    /* 声明虚函数必须在基类中进行说明，在派生类中说明没有效果，多层继承时也需要在最顶层的基类进行声明，在中间层进行声明也没有效果 */
    virtual void display();  //声明为虚函数
    //void display();
protected:
    char *m_name;
    int m_age;
};

/* 在构造函数中调用成员函数，不管是不是虚函数都会调用自己的那个成员函数 */
People::People(char *name, int age): m_name(name), m_age(age){}
void People::display(){
    cout<<m_name<<"今年"<<m_age<<"岁了，是个无业游民。"<<endl;
}

//派生类Teacher
class Teacher: public People{
public:
    Teacher(char *name, int age, int salary);
    /* 基类声明了虚函数，在派生类中可以加virtual修饰，也可以不加都能达到虚函数的效果 */
    //virtual void display(); //声明为虚函数
    void display();  
protected:
    int m_salary;
};
Teacher::Teacher(char *name, int age, int salary): People(name, age), m_salary(salary){}
void Teacher::display(){
    cout<<m_name<<"今年"<<m_age<<"岁了，是一名教师，每月有"<<m_salary<<"元的收入。"<<endl;
}

class Education: public Teacher{
public:
    Education(char *name, int age, int salary, int year);
    void display();
private:
    int workYear;
};

Education::Education(char *name, int age, int salary, int year): Teacher(name, age, salary), workYear(year){}
void Education::display(){
    cout<<m_name<<"今年"<<m_age<<"岁了，是一名教育工作者，每月有"<<m_salary<<"元的收入。"<< "工作了" << workYear << "年" << endl;
}

int main(){
    People *p = new People("王志刚", 23);
    p -> display();

    p = new Teacher("赵宏佳", 45, 8200);
    p -> display();
    
    p = new Education("张三", 43, 4500, 23);
    p -> display();

    return 0;
}