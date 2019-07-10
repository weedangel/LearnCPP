/*************************************************************************
	> FileName  : ReferenceTempData.cpp
	> Author    : zhouzhijun
	> Mail      : snjzzjun@163.com
	> CreateTime: 2019年07月06日 星期六 13时55分49秒
*************************************************************************/

#include <iostream>

using namespace std;

class Base {
public:
    void func(void);
    void func(int);
};
void Base::func(void) {
	cout<<"Base::func()"<<endl;
}

void Base::func(int a) {
	cout<<"Base::func(int)"<<endl;
}

/* 不管函数的参数如何，只要名字一样就会造成遮蔽。字查找规则导致只有在同一作用域中才能构成重载 */
class Derived: public Base {
public:
    void func(string);
    void func(bool);
};
void Derived::func(string str) {
	cout << "Derived::func(string str)" << endl;
}

void Derived::func(bool is) {
	cout << "Derived::func(bool)" << endl;
}

int main(int argc, char *argv[])
{
	Derived d;
	
    d.func("c.biancheng.net");
    d.func(true);
	
	/* 派生类与基类不能构成重载，编译报错 */
    //d.func();  //compile error
    //d.func(10);  //compile error
	
    d.Base::func();
    d.Base::func(100);
	
    return 0;
}