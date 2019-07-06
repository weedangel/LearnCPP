/*************************************************************************
	> FileName  : ReferenceTempData.cpp
	> Author    : zhouzhijun
	> Mail      : snjzzjun@163.com
	> CreateTime: 2019年07月06日 星期六 13时55分49秒
*************************************************************************/

#include <iostream>

using namespace std;

bool isOdd(int &n)
{
    if (n/2 == 0)
    {
        return false;
    }
    else
    {
        return true;
    }
}

bool isEven(const int &n)
{
    if (n/2 != 0)
    {
        return false;
    }
    else
    {
        return true;
    }
}

int main(int argc, char *argv[])
{
    int int_a = 12, int_b = 43;
    cout << int_a + int_b << endl;
    
    /* 这个编译器会直接报错，指针不可以指向临时数据，临时数据可能存在寄存器中，寄存器是不可以寻址的 */
    //int *p = &(int_a + int_b);
    //cout << p << endl;
    
    /* 这个编译器会直接报错，引用不可以指向临时数据，引用的本质还是指针，原因同上 */
    //int &r = int_a + int_b;
    //cout << r << endl;
    
    cout << isOdd(int_a) << endl;
    /* 函数形参是引用时，传参时只能传递变量，不能传递常量或是表达式 */
    //cout << isOdd(int_a+int_b) << endl;
    //<< isOdd(27) << endl;
    
    cout << isEven(int_a) << endl;
    /* 函数形参是常引用时，传参时可以传递变量、常量或是表达式 */
    cout << isEven(int_a+int_b) << endl;
    cout << isEven(27) << endl;
    
    return 0;
}
