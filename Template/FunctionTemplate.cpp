/*************************************************************************
	> FileName  : FunctionTemplate.cpp
	> Author    : zhouzhijun
	> Mail      : snjzzjun@163.com
	> CreateTime: 2019年10月11日 星期五 13时46分17秒
*************************************************************************/

#include <iostream>

using namespace std;

/* 函数模板也可以提前声明，不过声明的时候模板头与函数的声明必须是一个整体 */
template <typename T> void SwapData(T &data1, T &data2);

/* 模板函数定义，定义的时候也不能少了模板头，就算有提前声明也不可以，模板头与
   函数声明必须是一个整体，中间可以有空格或是换行，但不能有分号 */
template <typename T> void SwapData(T &data1, T &data2)
{
    T tempData = data1;
    
    data1 = data2;
    data2 = tempData;
}

template <typename T> void SwapDataFunc(T data1, T data2)
{
    T tempData = data1;
    
    data1 = data2;
    data2 = tempData;
}

/* 函数模板也支持重载 */
template <typename T> void SwapData(T *buf1, T *buf2, int dataLen)
{
    T tempData = 0;
    
    for (int i = 0; i < dataLen; i++)
    {
        tempData = buf1[i];
        buf1[i] = buf2[i];
        buf2[i] = tempData;
    }
}

int main(int argc, char *argv[])
{
    /* 函数模板在进行类型推断时允许的类型转换相当严格，比普通函数的类型转换严谨的多，
       只支持const和数组与指针的转换，其余的转换规则都不适用 */
    int a = 23, b = 45;   
    SwapData(a, b);
    cout << a << "," << b << endl;
    
    float c = 23.4, d = 45.2;
    SwapData(c, d);
    cout << c << "," << d << endl;
    
    /* 函数模板也支持显示的指明类型参数 */
    char e = 'e', f = 'f';
    SwapData<char>(e, f);
    cout << e << "," << f << endl;
     
    int x = 123;
    float y = 234.5;
    /*这样调用编译会报错 */
    //SwapDataFunc(x, y);  
    
    /* 模板函数调用时显示的指明了类型参数，此时自动转换规则就可以使用了，
    编译器会像对待普通函数一样进行参数类型转换 */
    SwapDataFunc<float>(x, y);
    
    /* 这个调用也会出错，编译器不能直接将Int类型转换成float &类型 */
    //SwapData<float>(x, y);
    
    cout << x << "," << y << endl;
    
    int array1[5] = {1, 2, 3, 4, 5};
    int array2[5] = {6, 7, 8, 9, 10};
    SwapData(array1, array2, sizeof(array1)/ sizeof(array1[0]));
    for (int i = 0; i < 5; i++)
    {
        cout << array1[i] << ",";
    }
    cout << endl;
    
    int mm = 900;
    int *intPtr = &mm;
    /* C++编译器不允许直接将int*类型直接转换成float*，除非是用类型强转 */
    //float *floatPtr = intPtr;
    cout << mm << endl;
    
    return 0;
}
