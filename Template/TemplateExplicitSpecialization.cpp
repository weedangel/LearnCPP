/*************************************************************************
	> FileName  : TemplateExplicitSpecialization.cpp
	> Author    : zhouzhijun
	> Mail      : snjzzjun@163.com
	> CreateTime: 2019年10月11日 星期五 15时45分16秒
*************************************************************************/

#include <iostream>
#include <string>

using namespace std;

/* 函数调用优先级：显示具体化优先于常规模板，而非模板函数优先于显示具体化和常规模板 */
#if 0
typedef struct Student
{
    string name;
    int age;
    float score;
}STU;

template<typename T> 
T& Max(T& data1, T& data2)
{
    return data1 > data2 ? data1 : data2;
}

/* 函数模板显示具体化，template<>就不存在类型参数了（尖括号内部应该是空）， */
//template<> STU& Max<STU>(STU& data1, STU& data2) //这种写法也是对的，一样可以编译通过
template<> STU& Max(STU& data1, STU& data2)
{
    return data1.age > data2.age ? data1 : data2;
}

ostream& operator<<(ostream& out, STU& stu)
{
    out << stu.name << "(" << stu.age << ")";
    
    return out;
}

int main(int argc, char *argv[])
{
    int num1 = 6, num2 = 9;
    cout << "max value: " << Max(num1, num2) << endl;
    
    STU stu1 = { "王明", 16, 95.5};
    STU stu2 = { "徐亮", 17, 90.0};
    cout << "max age: " << Max(stu1, stu2) << endl;
    
    return 0;
}
#else
template <typename T1, typename T2>
class Point
{
private:
    T1 xPoint;
    T2 yPoint;
public:
    Point(T1 x, T2 y):xPoint(x), yPoint(y) {};
    void SetXPoint(T1 x);
    void SetYPoint(T2 y);
    T1 GetXPoint() const;
    T2 GetYPoint() const;
    void display();
}; 

template <typename T1, typename T2>
void Point<T1, T2>::SetXPoint(T1 x)
{
    xPoint = x;
}

template <typename T1, typename T2>
void Point<T1, T2>::SetYPoint(T2 y)
{
    yPoint = y;
}

template <typename T1, typename T2>
T1 Point<T1, T2>::GetXPoint() const
{
    return xPoint;
}

template <typename T1, typename T2>
T2 Point<T1, T2>::GetYPoint() const
{
    return yPoint;
}

template <typename T1, typename T2>
void Point<T1, T2>::display()
{
    cout << xPoint << "," << yPoint << endl;
}

/*
ostream& operator<<(ostream& out, Point<string, string>& pointTemp)
{
    out << pointTemp.GetXPoint() << "|" << pointTemp.GetYPoint();
    
    return out;
}
*/

#if 1
/* 显示具体化模板类 */
template<> class Point<string, string> 
{
private:
    string xPoint;
    string yPoint;
public:
    Point(string x, string y):xPoint(x), yPoint(y) {};
    void SetXPoint(string x);
    void SetYPoint(string y);
    string GetXPoint() const;
    string GetYPoint() const;
    void display();    
};

/* 这里不能带模板头template<> */
void Point<string, string>::display()
{
    cout << xPoint << "|" << yPoint << endl;
}

/* 一个类显示具体化后，它的成员函数都应该被显示的具体化，否则编译时会在链接时报错 */
string Point<string, string>::GetXPoint() const
{
    return xPoint;
}
#else //可以只对一个具体的成员函数进行显示具体化
/* 这里不能带模板头template<> */
template<> void Point<string, string>::display()
{
    cout << xPoint << "|" << yPoint << endl;
}
#endif

/* 部分显示具体化模板类 */
/* 类名后面要列出所有的类型参数，是为了让编译器确认到底是第几个类型参数被具体化了 */
template<typename T2> class Point<string, T2> 
{
private:
    string xPoint;
    T2 yPoint;
public:
    Point(string x, T2 y):xPoint(x), yPoint(y) {};
    void SetXPoint(string x);
    void SetYPoint(T2 y);
    string GetXPoint() const;
    T2 GetYPoint() const;
    void display();    
};

template<typename T2>
void Point<string, T2>::display()
{
    cout << xPoint << "|" << yPoint << endl;
}

int main(int argc, char *argv[])
{
    Point<int, int> pointInt(23, 45);
    pointInt.display();
    
    Point<string, string> pointString("东经125度", "北纬34度");
    pointString.display();
    cout << pointString.GetXPoint() << endl;
    
    Point<string, int> pointAll("东经125度", 20);
    pointAll.display();
    
    return 0;
}
#endif
/******************************************************************************************
总结：
1、显示初始化感觉就是具体的生成了一个类
2、也可以显示具体化某一个成员函数，重写函数的实现
*******************************************************************************************/

