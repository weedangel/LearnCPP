/*************************************************************************
	> FileName  : OperatprOverloadSpecial.cpp
	> Author    : zhouzhijun
	> Mail      : snjzzjun@163.com
	> CreateTime: 2019年10月10日 星期四 18时21分46秒
*************************************************************************/

#include <iostream>
#include <iomanip>

using namespace std;

class StopWatch {
private:
    int timeSecond;
    int timeMinute;
    int timeHour;
    
public:
    StopWatch();
    void WatchRun();
    void display();

    StopWatch operator=(const StopWatch &tempWatch);
    StopWatch operator++();
    StopWatch operator++(int back);
    friend ostream &operator<<(ostream &out, StopWatch &watch);
};

StopWatch::StopWatch():timeSecond(0), timeMinute(0),timeHour(0) {}

void StopWatch::WatchRun() {
    timeSecond += 1;
    if (timeSecond == 60) {
        timeSecond = 0;
        timeMinute += 1;
        if (timeMinute == 60) {
            timeMinute = 0;
            timeHour += 1;
            if (timeHour == 24) {
                timeHour = 0;
            }
        }
    }
}

void StopWatch::display() {
    cout << timeHour << ":" << timeMinute << ":" << timeSecond << endl;
}

/* 参数推荐使用const修饰，否则如果等号右边的值是临时常量就会出现编译不通过 */
StopWatch StopWatch::operator=(const StopWatch &tempWatch) {
    this->timeHour = tempWatch.timeHour;
    this->timeMinute = tempWatch.timeMinute;
    this->timeSecond = tempWatch.timeSecond;
    
    return tempWatch;
}

StopWatch StopWatch::operator++() {
    WatchRun();
    
    return *this;
}

StopWatch StopWatch::operator++(int back) {
    StopWatch tempWatch = *this;
    WatchRun();
    
    return tempWatch;
}

ostream &operator<<(ostream &out, StopWatch &watch) {
    out << setfill('0') << setw(2) << watch.timeHour << ":" << setw(2) << watch.timeMinute << ":" << setw(2) << watch.timeSecond;
    
    return out;
}

class Array {
private:
    int arraySize;
    int *arrayPtr;

public:
    Array();
    Array(int size);
    
    ~Array();
 
/* 必须使用引用，否则不能通过下标运算进行赋值 */ 
    int &operator[](int i);
};

Array::Array():arraySize(0), arrayPtr(NULL) {}
Array::Array(int size):arraySize(size) {
    arrayPtr = new int[size];
}

Array::~Array() {
    delete[] arrayPtr;
}

int &Array::operator[](int i) {
    return arrayPtr[i];
}

int main(int argc, char *argv[])
{
    StopWatch runWatch;
    StopWatch resWatch;

    runWatch.WatchRun();
    cout << runWatch << endl;
    cout << "***********************************" << endl;
#if 0
    runWatch++;
    resWatch = runWatch;   //这样写=重载时可以不需要加const修饰也能编译通过
#else
    resWatch = runWatch++; //直接返回的值默认带const属性，所以=重载时需要加const修饰
#endif
    cout << runWatch << endl;
    cout << resWatch << endl;
    cout << "***********************************" << endl;

#if 0    
    ++runWatch;
    resWatch = runWatch;
#else
    resWatch = ++runWatch;  //直接返回的值默认带const属性
#endif
    cout << runWatch << endl;
    cout << resWatch << endl;  
    
    Array arrayTest(5);
    
    for (int i = 0; i < 5; i++) {
        //arrayTest.arrayPtr[i] = i + 1;
        arrayTest[i] = i + 1;
    }
    
    cout << arrayTest[4] << endl;
  
    return 0;
}
