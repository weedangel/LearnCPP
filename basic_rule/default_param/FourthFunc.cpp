/*************************************************************************
	> FileName  : DefaultParam.cpp
	> Author    : zhouzhijun
	> Mail      : snjzzjun@163.com
	> CreateTime: 2019年06月11日 星期二 20时48分51秒
*************************************************************************/

#include <iostream>
using namespace std;

/*************************************************************************
* 在声明的时候如果没有指定默认参数，就算定义时有默认参数，
* 在当前文件内调用函数就必须传递全部的参数   
*************************************************************************/
void func(int n, float b, char c);


int FourthFuncTest(void)
{
    int a  = 10;
    float b = 3.14;
    char c = 't';
    
    //func(a, b);  //这个编译会报错
    func(a, b, c);
    
    return 0;
}
