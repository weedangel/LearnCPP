/*************************************************************************
	> FileName  : VectorSTL.cpp
	> Author    : zhouzhijun
	> Mail      : snjzzjun@163.com
	> CreateTime: 2019年10月29日 星期二 19时19分18秒
*************************************************************************/

#include <iostream>
#include <vector>

using namespace std;

int main(int argc, char *argv[])
{
#if 0    
    #if 0
    /* C++ 98支持这种写法，不支持下面一种写法 */
    int testBuf[] = {12, 34, 56, 78, 90, 98, 76, 54, 32, 10};
    vector<int> testVector(testBuf, testBuf + sizeof(testBuf) / sizeof(int));
    #endif
    /* C++11 支持这种初始化方法，C++98编译会报错 */
    vector<int> testVector {12, 34, 56, 78, 90, 98, 76, 54, 32, 10};
    vector<int>::iterator vecIt;
    
    for(vecIt = testVector.begin(); vecIt != testVector.end(); vecIt++)
    {
        cout << "value: " << *vecIt << endl;
    }
    cout << "vector size: " << testVector.size() << endl;
    //cout << "vector length: " << testVector.length() << endl;  //vector不支持改成员函数
    cout << "vector capacity: " << testVector.capacity() << endl;
    cout << "vector max_size: " << testVector.max_size() << endl;
    
    testVector.reserve(20);  //修改的是capacity，没有修改size
    for(vecIt = testVector.begin(); vecIt != testVector.end(); vecIt++)
    {
        cout << "value: " << *vecIt << endl;
    }
    cout << "vector size: " << testVector.size() << endl;
    cout << "vector capacity: " << testVector.capacity() << endl;
    cout << "vector max_size: " << testVector.max_size() << endl;
    
    testVector.resize(8);  //修改了size，没有修改capacity
    for(vecIt = testVector.begin(); vecIt != testVector.end(); vecIt++)
    {
        cout << "value: " << *vecIt << endl;
    }
    cout << "vector size: " << testVector.size() << endl;
    cout << "vector capacity: " << testVector.capacity() << endl;
    cout << "vector max_size: " << testVector.max_size() << endl;
#else
    vector<int> testVector(20, 89); //指定vector的大小为20，并默认进行初始化，如果没有给出第二个参数初始化为0，给定第二个参数后会全部初始化为指定的值
    vector<int>::iterator vecIt;

    for(vecIt = testVector.begin(); vecIt != testVector.end(); vecIt++)
    {
        cout << "value: " << *vecIt << endl;
    }
    cout << "vector size: " << testVector.size() << endl;
    cout << "vector capacity: " << testVector.capacity() << endl;
    cout << "vector max_size: " << testVector.max_size() << endl;
#endif    
    return 0;
}
