/*************************************************************************
	> FileName  : ClassTemplate.cpp
	> Author    : zhouzhijun
	> Mail      : snjzzjun@163.com
	> CreateTime: 2019年10月11日 星期五 14时57分05秒
*************************************************************************/

#include <iostream>
#include <string>
using namespace std;

template <typename T1, typename T2>
class Point {
private:
    T1 xPoint;
    T2 yPoint;
public:
    Point(T1 x, T2 y):xPoint(x), yPoint(y) {};
    void SetXPoint(T1 x);
    void SetYPoint(T2 y);
    T1 GetXPoint() const;
    T2 GetYPoint() const;
};

/* 声明时模板头也必须存在，是一个整体不能省略 */
/* 声明的时候类类型后面必须带有<T1, T2>，否则编译不能通过 */
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

int main(int argc, char *argv[])
{
    Point<int, int> pointTest(10, 20);
    cout<<"x="<<pointTest.GetXPoint()<<", y="<<pointTest.GetYPoint()<<endl;
    
    /* ；两边的类型参数必须一致，否则编译器会报错 */
    Point<string, string> *pointPtr = new Point<string, string>("东经180度", "北纬210度");
    cout<<"x="<<pointPtr->GetXPoint()<<", y="<<pointPtr->GetYPoint()<<endl;
    
    /* 赋值号两边的数据类型不一致，编译不通过 */
    //Point<float, float> *p = new Point<float, int>(10.6, 109);
    /* 赋值号右边没有指明数据类型，编译不通过 */
    //Point<float, float> *p = new Point(10.6, 109);

    return 0;
}
