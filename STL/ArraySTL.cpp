/*************************************************************************
	> FileName  : ArraySTL.cpp
	> Author    : zhouzhijun
	> Mail      : snjzzjun@163.com
	> CreateTime: 2019年11月12日 星期二 14时36分48秒
*************************************************************************/

#include <iostream>
#include <string>
#include <algorithm>
#include <iterator>
#include <array>

using namespace std;

int main(int argc, char *argv[])
{
    //array<int, 10> arrayTest {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    array<int, 10> arrayTest {1, 2, 3, 4, 5};  //未完全初始化时后面默认填充0
    
    cout << "Array size: " << arrayTest.size() << endl;
    //cout << "Array capacity: " << arrayTest.capacity() << endl;  //array没有实现capacity方法
    cout << "Array max_size: " << arrayTest.max_size() << endl;
    cout << string(25, '*') << endl;

    for (auto arrayIter : arrayTest) {
        cout << arrayIter << endl;
    }
    cout << string(25, '*') << endl;
    
    for (int i = 0; i < arrayTest.size(); i++) {
        cout << arrayTest.at(i) << endl;
    }
    cout << string(25, '*') << endl; 
    
    for (int i = 0; i < arrayTest.size(); i++) {
        cout << arrayTest[i] << endl;
    }
    cout << string(25, '*') << endl;
    
    arrayTest.fill(99);
    array<int, 10>::iterator arrayIterFor;
    for (arrayIterFor = arrayTest.begin(); arrayIterFor != arrayTest.end(); arrayIterFor++) {
        cout << *arrayIterFor << endl;
    }
    cout << string(25, '*') << endl;
    
    int height = 0;
    int min_height = 40;
    int height_step = 2;
    
    //arrayTest.clear();  //未实现该方法
    generate(begin(arrayTest), end(arrayTest), [height, &min_height, &height_step] () mutable -> int {return height += height == 0 ? min_height : height_step;});
    for (auto arrayIter : arrayTest) {
        cout << arrayIter << endl;
    }
    cout << string(25, '*') << endl;
    cout << "height: " << height << endl;
    cout << string(25, '*') << endl;
    
    array<double,4> these {1.0, 2.0, 3.0, 4.0};
    array<double,4> those {1.0, 2.0, 3.0, 4.0};
    array<double,4> them {1.0, 3.0, 3.0, 2.0};
    if (these == those) cout << "these and those are equal." << endl;
    if (those != them) cout << "those and them are not equal."<< endl;
    if (those < them) cout << "those are less than them."<< endl;
    if (them > those) cout << "them are greater than those." << endl;
    cout << string(25, '*') << endl;
    
    cout << "Test end" << endl;
    return 0;
}
