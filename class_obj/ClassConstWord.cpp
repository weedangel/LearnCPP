/*************************************************************************
	> FileName  : ClassConstWord.cpp
	> Author    : zhouzhijun
	> Mail      : snjzzjun@163.com
	> CreateTime: 2019年06月18日 星期二 18时58分30秒
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

public:
    /* const 变量是能够通过对象直接访问的，不能修改(编译会报错)，初始化要在参数列表中完成 */
    const int sex;
    static int total;

    Student(void);
    Student(string tName, int tAge, float tScore, int sex);
    void ShowStudentInfo(void);
    void ShowStudentTotal(void);
    void SetStudentAge(int tAge);

    static int GetStudnetTotal(void);
    
    /* 常成员函数能够访问所有的成员变量, 但只能调用const成员函数，调用非const成员函数编译会报错 */
    string GetStudentName(void) const;
    int GetStudentAge(void) const;
    
    ~Student(void);
};

int Student::total = 0;

Student::Student(void): sex(0)
{
    name = "zzj";
    age = 28;
    score = 98.2;
    
    total += 1;
}

Student::Student(string tName, int tAge, float tScore, int tSex): sex(tSex)
{
    name = tName;
    age = tAge;
    score = tScore;
    
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

void Student::SetStudentAge(int tAge)
{
    age = tAge;
}

int Student::GetStudnetTotal(void)
{
    return total; //访问静态成员不需要加类名就可以访问,当然通过类来访问也是可以的
}

/* 函数后面的const必须要有，而且在类声明时也必须存在，否则声明和定义将发生冲突 */
string Student::GetStudentName(void) const
{
    /* 要在const成员函数中调用非const成员函数必须将this指针类型强转, 强转后还可以调用set接口 */
    //ShowStudentInfo()
    //Student *pTemp = (Student *)this;
    //pTemp->ShowStudentInfo();
    
    //int age = 33;
    //pTemp->SetStudentAge(age);
    
    return name;
}

int Student::GetStudentAge(void) const
{
    /* 可以调用const成员函数 */
    GetStudentName();
    return age;
}

Student::~Student(void)
{
    total -= 1;
}

int main(int argc, char *argv[])
{
    Student zzj;

    cout << zzj.GetStudentName() << ":" << zzj.GetStudentAge() << endl;
    cout << zzj.GetStudnetTotal() << ";" << zzj.sex << endl;
    
    cout << "test const obj" << endl;
    const Student mary;
    cout << mary.GetStudentName() << ":" << mary.GetStudentAge() << endl;
    cout << mary.sex << endl;
    
    /* const对象只能访问const修饰的成员（函数或变量），不能访问非const成员（函数或变量）*/
    cout << mary.name;
    //mary.ShowStudentInfo();
    
    return 0;
}
