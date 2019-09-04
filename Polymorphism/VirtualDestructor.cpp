/*************************************************************************
	> FileName  : VirtualDestructor.cpp
	> Author    : zhouzhijun
	> Mail      : snjzzjun@163.com
	> CreateTime: 2019年09月04日 星期三 21时06分49秒
*************************************************************************/

#include <iostream>
#include <string>

using namespace std;

/*
   将基类的析构函数声明为虚函数后，派生类的析构函数也会自动成为虚函数。
   这个时候编译器会忽略指针的类型，而根据指针的指向来选择函数；
   就是说，指针指向哪个类的对象就调用哪个类的函数。 
   
   大部分情况下都应该将基类的析构函数声明为虚函数。
*/
class Base
{
public:
	Base();
	Base(string temp_str);
	
	virtual ~Base();
	
protected:
	string str;
};

Base::Base(void)
{
	cout << "Base constructor0 call" << endl;
	this->str = "test";	
}

Base::Base(string temp_str)
{
	cout << "Base constructor1 call" << endl;
	this->str = temp_str;	
}

Base::~Base()
{
	cout << "Base destructor call" << endl;
}

class Derived: public Base
{
public:
	Derived();
	~Derived();

private:
	string name;
};

Derived::Derived()
{
	cout << "Derived constructor1 call" << endl;
	this->name = "my test";
}

Derived::~Derived()
{
	cout << "Derived destructor call" << endl;
	
}

int main(int argc, char *argv[])
{
	Base *tempBasePtr =  new Derived();
	delete tempBasePtr;
	
	cout << "--------------------------------------------" << endl;
	
	Derived *tempDerivedPtr = new Derived();
	delete tempDerivedPtr;
    
    return 0;
}
