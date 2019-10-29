/*************************************************************************
	> FileName  : TemplateFriend.cpp
	> Author    : zhouzhijun
	> Mail      : snjzzjun@163.com
	> CreateTime: 2019年10月17日 星期四 16时31分02秒
*************************************************************************/

#include <iostream>
#include <string>

using namespace std;

template<typename T>
void CoutOneData(T& data)
{
    cout << "data value: " << data << endl;
}

#if 0
class A {
private:
    int age;
    int height;
public:
    A(): age(20), height(165) {};
    A(int tmpAge, int tmpHeight): age(tmpAge), height(tmpHeight) {};
    
    template<typename T>
    friend void CoutOneData(T& data);
};
#endif

template<typename T1, typename T2>
class A {
private:
    T1 age;
    T2 height;
public:
    A(): age(20), height(165.2) {};
    A(T1 tmpAge, T2 tmpHeight): age(tmpAge), height(tmpHeight) {};
    
    template<typename T>
    friend void CoutOneData(T& data);    
};
#if 1
template<> void CoutOneData< A<int, double> >(A<int, double>& data)
{
    cout << "student age: " << data.age << endl;
    cout << "student height: " << data.height << endl;
}

template<> void CoutOneData< A<int, string> >(A<int, string>& data)
{
    cout << "student age: " << data.age << endl;
    cout << "student height: " << data.height << endl;
}
#else
/* 这样显示具体化编译是无法通过的 */
template<typename T2> void CoutOneData< A<int, T2> >(A<int, T2>& data)
{
    cout << "student age: " << data.age << endl;
    cout << "student height: " << data.height << endl;
}    
#endif
/**********************************************************************************************/

template < typename T1, typename T2 >
void CoutDoubleData(const T1& data1, const T2& data2)
{
    cout << "data1: " << data1 << endl;
    cout << "data2: " << data2 << endl;
}

#if 1
template<typename T> void CoutDoubleData(const int& data1, const T& data2)
{
    cout << "data 1: " << data1 + 123 << endl;
    cout << "data 2: " << data2 << endl;
}
#endif
/* 自己的理解：模板函数部分具体化，实际就是在声明了一个模板函数，只是这个模板函数较之前的模板函数参数限制的更加严格，
   编译器在选举调用哪个函数的时候优先匹配能够精确匹配的这个函数 */
   
template <typename T1, typename T2>
class TestBase {
private:
    T1 lenData;
    T2 widthData;
public:
    TestBase(): lenData(1.0), widthData(1.0) {};
    TestBase(T1 len, T2 width): lenData(len), widthData(width) {};
    
    void GetArea();    
};

template <typename T1, typename T2>
void TestBase<T1, T2>::GetArea()
{
    //cout << "area: " << lenData * widthData << endl;
    cout << "lenData: " << lenData << endl;
    cout << "widthData: " << widthData << endl;
}

#if 0
/* 不知道为什么这个编译不过去 */
template <typename T2> void TestBase<int, T2>::GetArea()
{
    //cout << "area: " << lenData * stod(widthData) << endl;
    cout << "lenData int: " << lenData << endl;
    cout << "widthData string: " << widthData << endl;
}
#endif

int main(int argc, char *argv[])
{
    A<int, double> testA;
    
    CoutOneData(testA);
    
    A<int, double> testB(21, 324.5);
    CoutOneData(testB);
    
    A<int, string> testC(23, "125.6cm");
    CoutOneData(testC);
    
    int aTest = 900;
    CoutOneData(aTest);
    
    string aString = "TestCode";
    
    CoutDoubleData(aTest, aString);
    
    TestBase<double, double> barA(3.5, 4.2);
    barA.GetArea();
    
    TestBase<int, double> barB(5, 5.5);
    barB.GetArea();
     
    return 0;
}
