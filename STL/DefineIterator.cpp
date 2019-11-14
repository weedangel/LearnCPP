/*************************************************************************
	> FileName  : DefineIterator.cpp
	> Author    : zhouzhijun
	> Mail      : snjzzjun@163.com
	> CreateTime: 2019年11月13日 星期三 14时58分59秒
*************************************************************************/

#include <iostream>
#include <string>

using namespace std;

class Base {
public:
    typedef Base  value_type;
    typedef Base* pointer;
    typedef Base& reference;
    
private:
    int stuAge;
    float stuHeight;
    string stuName;
    
public:
    Base(int age = 16, float height = 165.0, string name = "unknow"): stuAge(age), stuHeight(height) {stuName = name;};
    void SetAge(int age) {stuAge = age;};
    void SetAge(float height) {stuHeight = height;};
    
    friend ostream & operator<< (ostream & out, Base & stuData);
    Base& operator=(const Base& data);
};

ostream & operator<< (ostream & out, Base & stuData) {
    out << stuData.stuName << " is " << stuData.stuAge << " and " <<  stuData.stuHeight << "cm.";
    
    return out;
}

template <typename Iter> void SwapTest(Iter& dataA, Iter& dataB) {
    typename Iter::value_type tempData;
    
    tempData = dataA;
    dataA = dataB;
    dataB = tempData;
    
    return;
}

Base& Base::operator= (const Base& data) {
    this->stuAge = data.stuAge;
    this->stuHeight = data.stuHeight;
    this->stuName = data.stuName;
    
    return *this;
}

int main(int argc, char *argv[])
{
    Base testStu;
    cout << "testStu: " <<testStu << endl;
    
    Base liMing(17, 186.2, "Li Ming");
    cout << "liMing: " << liMing << endl;

    Base zhangSan(16, 165.4, "zhangSan");
    cout << "zhangSan: " <<zhangSan << endl;
    cout << string(30, '*') << endl;
    
    SwapTest(liMing, zhangSan);
    cout << "liMing: " <<liMing << endl;
    cout << "zhangSan: " <<zhangSan << endl;
    cout << string(30, '*') << endl;
    
    return 0;
}
