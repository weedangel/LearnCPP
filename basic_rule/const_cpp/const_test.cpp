/*************************************************************************
	> FileName  : const_test.cpp
	> Author    : zhouzhijun
	> Mail      : snjzzjun@163.com
	> CreateTime: 2019年06月18日 星期二 09时36分11秒
*************************************************************************/

#include <iostream>

using namespace std;

/* C和C++中全局 const 变量的作用域相同，都是当前文件，不同的是它们的可见范围：
C语言中 const 全局变量的可见范围是整个程序，在其他文件中使用 extern 声明后就可以使用；
而C++中 const 全局变量的可见范围仅限于当前文件，在其他文件中不可见，所以它可以定义在头文件中，多次引入后也不会出错。 */

/* 对全局的const变量去地址指针修改值也是不允许的，会报段错误(全局的const变量存储在只读段) */
//const int a = 20;
int a = 20;

int main(int argc, char *argv[])
{
    /* 局部的const变量是可以违规指针操作修改值的，但修改后变量访问的值还是初始化的值，
    编译器在编译阶段完成const变量的值替换， 指针访问能够看见值发生了变化，变量存储在堆栈段 */
    const int g_test = 10;
    
    cout << "g_test0: " << g_test << endl;
    
    int *g_p = (int *)&g_test;
    cout << "g_p: " << g_p << endl;
    *g_p = 99;
    
    cout << "g_test1: " << *g_p << endl;
    cout << "g_test2: " << g_test << endl;
    
    cout << "a0: " << a << endl;
    
    int *a_p = (int *)&a;
    cout << "a_p: " << a_p << endl;
    *a_p = 99;
    
    cout << "a1: " << *a_p << endl;
    cout << "a2: " << a << endl;
    
    return 0;
}
