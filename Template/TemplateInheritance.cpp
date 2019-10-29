/*************************************************************************
	> FileName  : TemplateInheritance.cpp
	> Author    : zhouzhijun
	> Mail      : snjzzjun@163.com
	> CreateTime: 2019年10月17日 星期四 15时32分09秒
*************************************************************************/

#include <iostream>
#include <string>

using namespace std;

template <typename T1, typename T2> 
class Base
{
private:
    T1 data1;
    T2 data2;
public:
    Base(): data1(0), data2(0) { cout<<"call base1" << endl;};
    Base(T1 tData1, T2 tData2): data1(tData1), data2(tData2) {cout<<"call base2" << endl;};
    
    void SetData1(T1 data);
    void SetData2(T2 data);
    
    T1 GetData1(void);
    T2 GetData2(void);
};

template <typename T1, typename T2>
void Base<T1, T2>::SetData1(T1 data)
{
    data1 = data;
}

template <typename T1, typename T2>
void Base<T1, T2>::SetData2(T2 data)
{
    data2 = data;
}

template <typename T1, typename T2>
T1 Base<T1, T2>::GetData1(void)
{
    return data1;
}

template <typename T1, typename T2>
T2 Base<T1, T2>::GetData2(void)
{
    return data2;
}

#if 0
/* 如果派生类没有使用模板，那么派生类之类继承某一个固定的类模板，不能自动兼容所有的模板实现 */
class Derive: public Base<int, float> 
{
private:
    int dData;
public:
    void SetData(int dd);
    int GetData(void);
};
#endif

/* 基类可以根据派生类的模板选择继承那个一个基类模板实例 */
template <typename T1, typename T2>
class Derive: public Base<T2, T1> 
{
private:
    T1 dData;
public:
    void SetData(T1 dd);
    T1 GetData(void);
};

template <typename T1, typename T2>
void Derive<T1, T2>::SetData(T1 data)
{
    dData = data;
}

template <typename T1, typename T2>
T1 Derive<T1, T2>::GetData(void)
{
    return dData;
}

/* 注意：不管以哪种方式继承模板类，针对派生类它继承的基类一定是一个具体化的实例，不会再是一个模板而兼容所有的可能的基类 */
/* 类模板从模板类派生：可以使用类模板的类型参数来显示实例化基类，也可以指定固定的类型来显示实例化基类，但一定是显示实例化后才能被继承 */
/* 类模板从普通类派生：直接继承就可以了，和普通的继承没什么不一样 */
/* 普通类从模板类派生：基类必须指定类型参数显示实例化后才能被继承，否则编译会报错 */

int main(int argc, char *argv[])
{
    Base<int, int> base0;
    cout <<"data1: " << base0.GetData1() << ", data2: " << base0.GetData2() << endl;
    
    Base<int, int> base1(45, 67);
    cout <<"data1: " << base1.GetData1() << ", data2: " << base1.GetData2() << endl;
    
    Derive<int, double> testD;
    
    return 0;
}
