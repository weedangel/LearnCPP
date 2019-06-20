/*************************************************************************
	> FileName  : ClassStaticVar.cpp
	> Author    : zhouzhijun
	> Mail      : snjzzjun@163.com
	> CreateTime: 2019年06月18日 星期二 16时54分18秒
*************************************************************************/

#include <iostream>
#include <string>

using namespace std;

class Student
{
private:
    string name;
    int age;
    float score;
    //static int total;

public:
    /* 静态成员必须在类体外进行初始化，初始化时不能带static关键字 */
    static int total;

    Student(void);
    void ShowStudentInfo(void);
    void ShowStudentTotal(void);
    
    /* 静态成员函数没有 this 指针，只能访问静态成员（变量或是函数），类外定义时不能带static关键字 */
    static int GetStudnetTotal(void);
    
    ~Student(void);
};

/* 静态变量在初始化时分配内存(私有的静态变量同样使用这种方法进行初始化，不过外部访问时就会收到权限限制)，不初始化编译会报未定义的错误 */
int Student::total = 0;

Student::Student(void)
{
    name = "zzj";
    age = 28;
    score = 98.2;
    
    total += 1;
}

void Student::ShowStudentInfo(void)
{
    cout << name << ":" << age << "," << score << endl;
}

void Student::ShowStudentTotal(void)
{
    cout << total << endl;
}

int Student::GetStudnetTotal(void)
{
    return total; //访问静态成员不需要加类名就可以访问,当然通过类来访问也是可以的
}

Student::~Student(void)
{
    total -= 1;
}

int main(int argc, char *argv[])
{
    Student zzj;

    zzj.ShowStudentInfo();
    zzj.ShowStudentTotal();
    
    Student *other = new Student();
    
    /* 静态成员变量可以使用类名访问，一个通过对象访问,（私有的静态成员变量不能这样访问，编译会报错） */
    cout << Student::total << endl;
    cout << zzj.total << endl;
    cout << other->total << endl;
    
    delete other;
    
    /* 静态成员函数可以通过类或是对象来访问 */
    cout << Student::GetStudnetTotal() << endl;
    cout << zzj.GetStudnetTotal() << endl;
    
    return 0;
}
