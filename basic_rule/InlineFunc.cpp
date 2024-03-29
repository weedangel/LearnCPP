/*************************************************************************
	> FileName  : InlineFunc.cpp
	> Author    : zhouzhijun
	> Mail      : snjzzjun@163.com
	> CreateTime: 2019年06月11日 星期二 20时21分22秒
*************************************************************************/

#include <iostream>
using namespace std;

/**************************************************************************************
* 内联函数的特点：
*   1、内联函数不应该有声明，应该将函数定义放在本应该出现函数声明的地方(inline用于实现)
*   2、inline关键字应添加在函数定义的位置，添加在声明的位置无效
*   3、内联函数在编译阶段完成替换，直接用函数的功能代码替换函数的调用，会做类型检查
*   4、内联函数应尽量的小，否则多次调用拷贝后会增大编译后elf文件的大小（空间换时间）
*   5、内联函数可以定义在头文件中（不用加static修饰），并且可以多次重复包含（与普通函数不同）
*   6、内联函数在编译完成之后就不存在了，不会存在函数的入口来进行调用（定义和调用必须在同文件）
* 作用：
*   1、消除函数调用时的开销（空间换时间）
*   2、取代带参数的宏（更倾向这个作用）
***************************************************************************************/
inline int addFunc(const int a, const int b)
{
    return a + b;
}

int main(int argc, char *argv[])
{
    int a = 10;
    int b = 20;
    
    cout << "a+b=" << addFunc(a, b) << endl;
    
    return 0;
}
