/*************************************************************************
	> FileName  : StringSTL.cpp
	> Author    : zhouzhijun
	> Mail      : snjzzjun@163.com
	> CreateTime: 2019年10月29日 星期二 15时58分34秒
*************************************************************************/

#include <iostream>
#include <string>

using namespace std;

int main(int argc, char *argv[])
{
    string strChar("abcdefghijabcdefghij");
    cout << strChar << endl;
    
    string strStr = "123456";
    cout << strStr << endl;
    
    cout << "strChar: " << sizeof(strChar) << ", strStr: " << sizeof(strStr) << endl;
    
    string strConst = strChar;
    //strConst[3] = 'a';
    strConst.at(3) = 'a';
    strConst.resize(10);
    
    cout << strChar << endl;
    cout << strConst << endl;
    
    cout << "string compare: " << strChar.compare(strConst) << endl;
    
    cout << "string len: " << strChar.length() << "," << strConst.length() << endl;
    cout << "string size: " << strChar.size() << "," << strConst.size() << endl;
    cout << "string capacity: " << strChar.capacity() << "," << strConst.capacity() << endl;
    cout << hex << "string max size: " << strChar.max_size() << "," << strConst.max_size() << dec << endl;
    
    //cout << strConst.at(strConst.length()) << endl;  //运行时报错，跑出out_of_range的异常
    cout << int(strConst[strConst.length()]) << endl;  //直接输出看不见输出结果，实际是'\0'
    
    string strAssign;
    strAssign.assign(strConst);
    cout << strAssign << endl;
    cout << "npos: " << strChar.npos << ", " << strConst.npos << ", " << strAssign.npos << endl;
    
    string::iterator itCharStart, itCharEnd, itConstStart, itConstEnd;
    
    itCharStart = strChar.begin();
    itCharEnd = strChar.end();
    itConstStart = strConst.begin();
    itConstEnd = strConst.end();
    //strConst.insert(3, 3, 'z');
    //strConst.insert(itConstEnd, itCharStart, itCharEnd);
    //strConst.insert(strConst.length(), strChar);
    //strConst.insert(itConstEnd, 5, 'z');
    strConst.insert(strConst.length(), strChar, 3, 7);
    cout << strConst << endl;
    
    cout << strChar.find("def") << endl;   //指向第一个出现def的d处索引
    cout << strChar.find_first_of("def") << endl;  //指向第一个出现def的d处索引
    cout << strChar.find_last_of("def") << endl;   //指向最后一个出现def的f处索引
    cout << strChar.find_first_not_of("def") << endl; //指向第一个非def处的第一个字符索引
    cout << strChar.find_last_not_of("def") << endl;  //指向最后一个非def处的最后一个字符索引
    
    cout << strConst << endl;
    cout << "strConst len: " << strConst.length() << endl;
    strConst.erase(3, 5); //擦除索引3后面的5个字符，并将剩下的后面字符自动拼接上来
    cout << strConst << endl;
    cout << "strConst len: " << strConst.length() << endl;
    strConst.clear();
    cout << strConst << endl;
    cout << "strConst len: " << strConst.length() << endl;
    
    
    return 0;
}

