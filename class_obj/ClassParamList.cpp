/*************************************************************************
	> FileName  : ClassParamList.cpp
	> Author    : zhouzhijun
	> Mail      : snjzzjun@163.com
	> CreateTime: 2019年06月18日 星期二 16时07分43秒
*************************************************************************/

#include <iostream>
using namespace std;

class Demo
{
private:
    int m_a;
    int m_b;
    
    /* 声明带有const的变量时，必须进行初始化，否则编译报错，初始化const变量必须是在参数列表中完成，在构造函数中也不能对其赋值*/
    const int m_c;
    
public:
    Demo(void);
    Demo(int b);
    Demo(int a, int b);
    Demo(int a, int b, int c);
    void display(void);
    
    /* 析构函数没有参数，所以也不支持重载，一个类只有一个析构函数 */
    ~Demo(void);
};

Demo::Demo(void): m_c(0)
{
    m_a = 0;
    m_b = 0;    
}

/* 参数初始化顺序与初始化表列出的变量的顺序无关，它只与成员变量在类中声明的顺序有关
所以调用这个构造函数后m_a的值是不确定的，因为m_a先赋值，赋值是m_b还是一个不确定的垃圾值 */
Demo::Demo(int b): m_b(b), m_a(m_b), m_c(0)
{
    ;
}

/* 参数初始化列表完成的顺序在构造函数中显示赋值之前，该构造函数能够将m_b的值设置成50 */
Demo::Demo(int a, int b): m_a(a), m_c(50)
{
    m_b = m_c;
}   

Demo::Demo(int a, int b, int c): m_c(c)
{
    m_a = a;
    m_b = b;
}   

void Demo::display(void)
{
    cout << m_a << ", " << m_b << endl;
}

Demo::~Demo(void)
{
    cout << "free memory" << endl;
}


int main(int argc, char *argv[])
{
    Demo d;
    d.display();
    
    Demo b(30);
    b.display();
    
    Demo a(10, 20);
    a.display();

    return 0;
}
