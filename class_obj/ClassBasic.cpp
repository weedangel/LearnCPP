/*************************************************************************
	> FileName  : ClassBasic.cpp
	> Author    : zhouzhijun
	> Mail      : snjzzjun@163.com
	> CreateTime: 2019年06月12日 星期三 14时46分54秒
*************************************************************************/

/*************************************************************************
C++命名规则:
    1、变量和参数用小写字母开头的单词组合而成，而且后面的单词用大写字母开头
    2、类名用大写字母开头的单词组合而成
    3、常量用类型前缀+全大写字母组成，用下划线分割单词
    4、静态变量加前缀 s_（表示static，后面更变量名）
    5、全局变量加前缀 g_（表示global，后面更变量名），全局变量尽量不要用
    6、宏和枚举全用大写字母组成，用下划线分割单词
*************************************************************************/

#include <iostream>
#include <string>

using namespace std;

class Student
{
public:
    string name;
    char age;
    char sex;
    short height;
    short weight;
    char grades;
    char classes;
    float score;
    
    void displayInfo(void)
    {
        cout << "name: " << name << endl;
        
        /* cout 不能直接输出char数据的值，他会当做字符来输出，所以需要强转一下 */
        cout << "age: " << (int)age << endl;
        //cout << "age: " << age << endl;
    }
};

/*************************************************************************************
* 两种创建对象的方式：
*    1、在栈上创建，形式和定义普通变量类似
*    2、在堆上创建，必须要用一个指针指向它，读者要记得 delete 掉不再使用的对象
*    
* 注：使用 new 在堆上创建出来的对象是匿名的，没法直接使用，必须要用一个指针指向它，
*     再借助指针来访问它的成员变量或成员函数  
************************************************************************************/

int main(int argc, char *argv[])
{
    /* 实例化类模板，创建两个实例变量，实例化时可以加class关键字，也可以不加 */
    class Student LiLei;
    Student Bob;
    
    LiLei.name = "LiLei";
    LiLei.age = 18;
    LiLei.displayInfo();
    
    Bob.name = "Bob";
    Bob.age = 19;
    Bob.displayInfo();
    
    Student *pStu = NULL;
    pStu = new Student;
    pStu->name = "Jack";
    pStu->age = 17;
    pStu->displayInfo();
    
    /* 使用new从堆上创建对象时必须使用一个指针来接受，创建匿名对象编译器是能够接受的，但并没有实际意义（不能使用，还会造成内存泄露）*/
    //new Student; //这样写编译能够通过，也没有警告
    
    return 0;
}
