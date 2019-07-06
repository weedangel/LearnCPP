/*************************************************************************
	> FileName  : ReferenceTest.cpp
	> Author    : zhouzhijun
	> Mail      : snjzzjun@163.com
	> CreateTime: 2019年07月06日 星期六 10时53分09秒
*************************************************************************/

#include <iostream>

using namespace std;

int num = 99;

class A
{
public:
    int a;
    int c;
    int &b;
    
public:
    A(); 
};

/* 引用的初始化也必须放在参数列表中，否则编译会报错 */
A::A():a(10), c(20), b(num)
{
    //b = num;
}

int main(int argc, char *argv[])
{
    A c_a;
    int i = 0;
    int *ptr_t = NULL;
    
    cout << c_a.a << "," << c_a.b << endl;
    
    /* 如果代码中不加int c的定义，大小依然是16，原因是8字节(64位机器)对齐 */
    cout << sizeof(c_a) << endl;
    
    ptr_t = (int*)&c_a;
    for (i=0; i < sizeof(c_a)/4; i++)
    {
        cout << hex << showbase << ptr_t[i] << endl;
    }
   
    cout << &num << endl;
    cout << dec << sizeof(c_a.a) << endl;
    cout << sizeof(ptr_t) << endl;
    
    int int_a = 123;
    int &ref_a = int_a;
    const int &ref_a_c1 = int_a;
    int const &ref_a_c2 = int_a;
    /* 这种声明方式是错误的（因为引用本身就是从一而终的，加上 const 是多此一举），编译器直接会报错，这个与指针不同 */
    //int &const ref_a_c3 = int_a; 
    cout << ref_a << "," << ref_a_c1 << "," << ref_a_c2 << endl;
    
    /* 没有二级引用，这个与指针也不一样 */
    int int_b = 321;
    int &ref_b = int_b;
    /* 一个引用可以等于另一个引用，效果和所等的引用一样 */
    int &ref_ref_b = ref_b;
    /* 不能想二级指针样声明引用，如果做了编译器会直接报错 */
    //int &&ref_ref_b1 = ref_b;
    cout << ref_b << "," << ref_ref_b << endl;
    cout << int_b << endl;
    
    return 0;
}
