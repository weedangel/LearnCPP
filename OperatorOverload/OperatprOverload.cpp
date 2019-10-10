/*************************************************************************
	> FileName  : OperatprOverload.cpp
	> Author    : zhouzhijun
	> Mail      : snjzzjun@163.com
	> CreateTime: 2019年10月10日 星期四 13时14分20秒
*************************************************************************/

#include <iostream>
#include <string>

using namespace std;

/***************************************************************************************
能够重载的运算符：+  -  *  /  %  ^  &  |  ~  !  =  <  >  +=  -=  *=  /=  %=  
   ^=  &=  |=  <<  >>  <<=  >>=  ==  !=  <=  >=  &&  ||  ++  --  ,  ->*  ->  ()
   []  new  new[]  delete  delete[] 
   其中[]是下标运算符，()是函数调用运算符
注意：箭头运算符->、下标运算符[ ]、函数调用运算符( )、赋值运算符=只能以成员函数的形式重载
   
不能被重载的运算符：长度运算符sizeof、条件运算符: ?、成员选择符.和域解析运算符::
****************************************************************************************/

/****************************************************************************************
1、重载不能改变运算符的优先级和结合性
2、重载不会改变运算符的用法，原有有几个操作数、操作数在左边还是在右边，这些都不会改变
3、运算符重载函数不能有默认的参数，否则就改变了运算符操作数的个数，这显然是错误的
4、运算符重载函数既可以作为类的成员函数，也可以作为全局函数
   作为类的成员函数：二元运算符的参数只有一个，一元运算符不需要参数，有一个隐藏的参数this
   作为全局函数：二元操作符就需要两个参数，一元操作符需要一个参数，而且其中必须有一个参数是对象，
                 好让编译器区分这是程序员自定义的运算符，防止程序员修改用于内置类型的运算符的性质
5、重载运算符时应该优先考虑成员函数，这样更符合运算符重载的初衷；
   另外有一部分运算符重载必须是全局函数，这样能保证参数的对称性 
*****************************************************************************************/

class Complex
{
private:
    double m_real;
    double m_imag;
    
public:
    Complex();
    /* 转换构造函数 */
    //Complex(double real);
    Complex(double real, double imag = 0);

    ~Complex();
    
    void dispaly() const;
    
    /* 运算符重载可以是成员函数，也可以是全局的函数，若是全局的运算符重载函数要使用私有成员变量则需要声明为友元函数 */
    Complex operator+(const Complex &complexDate) const;
    friend Complex operator-(const Complex &complexDateA, const Complex &complexDateB);
    //friend Complex operator-(const Complex &complexDate, double realData);
    friend ostream &operator<<(ostream &out, Complex &complexData);
    friend istream &operator>>(istream &in, Complex &complexData);
};

Complex::Complex():m_real(0.0), m_imag(0.0){}
//Complex::Complex(double real):m_real(real), m_imag(0.0){}
Complex::Complex(double real, double imag):m_real(real), m_imag(imag){}

Complex::~Complex(){
    //cout << "Complex destruct call" << endl;
}

void Complex::dispaly() const {
    cout << m_real << " + " << m_imag << "i" << endl;
}

/* 运算符重载函数作为成员函数 */
Complex Complex::operator+(const Complex &complexDate) const {
    Complex complexDateB;
    
    complexDateB.m_real = this->m_real + complexDate.m_real;
    complexDateB.m_imag = this->m_imag + complexDate.m_imag;
    
    return complexDateB;
}

/*********************************************************************************
修改内置类型的运算符时编译器会报错，这个函数编译是不能通过的
int operator*(int a, int b)
{
    return a/b;
}
*********************************************************************************/

/* 运算符重载函数是全局函数 */
Complex operator-(const Complex &complexDateA, const Complex &complexDateB){  
    return Complex(complexDateA.m_real - complexDateB.m_real, complexDateA.m_imag - complexDateB.m_imag);
}

/* 运算符重载重载函数之间也可以有重载关系 */
//Complex operator-(const Complex &complexDate, double realData){  
//    return Complex(complexDate.m_real - realData + 1, complexDate.m_imag);
//}
/* 当有转换构造函数时，编译器优先将数据类型转换，没有转换构造函数时编译器优先寻找运算符重载函数，最后才会尝试调用具有默认参数的构造函数来完成类型转换 */

/* 重载输入输出函数 */
istream &operator>>(istream &in, Complex &complexData) {
    in >> complexData.m_real >> complexData.m_imag;
    
    return in;
}

ostream &operator<<(ostream &out, Complex &complexData) {
    out << complexData.m_real << " + " << complexData.m_imag << "i";
    
    return out;
}

int main(int argc, char *argv[])
{
    Complex complexDate1(4.3, 5.8);
    Complex complexDate2(2.4, 3.7);
    Complex complexDateAdd, complexDateSub;
    
    //complexDateAdd = complexDate1.operator+(complexDate2)
    complexDateAdd = complexDate1 + complexDate2;
    complexDateAdd.dispaly();
    
    //complexDateSub = operator-(complexDate1, complexDate2);
    complexDateSub = complexDate1 - complexDate2;
    complexDateSub.dispaly();
    
    /* 这个函数的调用方式是编译器优先调用转换构造函数，若不存在转换构造函数才会使用具有重载关系的运算符重载函数 */
    complexDateSub = complexDate1 - 0.2;
    complexDateSub.dispaly();
#if 0    
    Complex complexDate3;
    cin >> complexDate3;
    cout << complexDate3 << endl;
#endif    
    return 0;
}
