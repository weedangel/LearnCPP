/*************************************************************************
	> FileName  : ReferenceTempData.cpp
	> Author    : zhouzhijun
	> Mail      : snjzzjun@163.com
	> CreateTime: 2019年07月06日 星期六 13时55分49秒
*************************************************************************/

#include <iostream>

using namespace std;

int main(int argc, char *argv[])
{
    int int_a = 12;
	int &ref_a = int_a;
	
	/* 引用不能自动转换类型，下面这种写法编译器会直接报错 */
	//float &ref_a_f = int_a;
	
	/* 加const修饰后，编译器会使用数据类型转换规则创建临时变量，并将临时变量赋给新建的引用 */
	const float &ref_a_f = int_a;
	
	cout << int_a << "," << ref_a << endl;
	cout << ref_a_f << endl;
	
	char ch_a = '1';
	char &ref_ch_a = ch_a;
	
	/* 引用不能自动转换类型，下面这种写法编译器会直接报错，char转int也不可以 */
	//int &ref_int_a = ch_a;
	
	cout << ch_a << "," << ref_ch_a << endl;
	
    return 0;
}