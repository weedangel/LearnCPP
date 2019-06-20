/*************************************************************************
	> FileName  : DefaultParam.cpp
	> Author    : zhouzhijun
	> Mail      : snjzzjun@163.com
	> CreateTime: 2019年06月11日 星期二 20时48分51秒
*************************************************************************/

#include <iostream>
using namespace std;

/*************************************************************************
* 在声明的时候指定默认参数，定义时不设置默认参数，能够正常运行   
*************************************************************************/
void func(int n, float b=1.2, char c='@');
int ThirdFuncTest(void);
int FourthFuncTest(void);

int main(int argc, char *argv[])
{
    int a  = 10;
    
    func(a);
    ThirdFuncTest();
    FourthFuncTest();
    
    return 0;
}
