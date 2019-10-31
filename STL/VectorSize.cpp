/*************************************************************************
	> FileName  : VectorSize.cpp
	> Author    : zhouzhijun
	> Mail      : snjzzjun@163.com
	> CreateTime: 2019年10月31日 星期四 21时40分29秒
*************************************************************************/

#include <iostream>
#include <vector>
#include <iterator>

using namespace std;

int main(int argc, char *argv[])
{
	vector<int> values {1, 2, 3};
	
	copy(begin(values), end(values), ostream_iterator<int> {cout, " "});
	cout << endl << "vector size: " << values.size() << endl;
	cout << "vector capacity: " << values.capacity() << endl;
	
	values.resize(7, 99); //把容量扩充到7，扩充后扩充的部分用99来填充
	copy(begin(values), end(values), ostream_iterator<int> {cout, " "});
	cout << endl << "vector size: " << values.size() << endl;
	cout << "vector capacity: " << values.capacity() << endl;
	
	values.resize(5);  //大小变为5，容量还是7
	values[0] = 5656;
	values[1] += values[0];
	copy(begin(values), end(values), ostream_iterator<int> {cout, " "});
	cout << endl << "vector size: " << values.size() << endl;
	cout << "vector capacity: " << values.capacity() << endl;
	
	cout << "values front: " << values.front() << endl;
	cout << "values back: " << values.back() << endl;
    
	auto intPtr = values.data();  //返回C语言类型的数组，string类型还没验证
	unsigned int* uintPtr = (unsigned int*)intPtr;
	for (int i = 0; i < values.size(); i++)
	{
		cout << uintPtr[i] << endl;
	}
	cout << string (20, '*') << endl;
	
	/*
	//不能这样操作，这样操作得不到想要的访问数组的效果
	uintPtr = (unsigned int*)&values;
	for (int i = 0; i < values.size(); i++)
	{
		cout << uintPtr[i] << endl;
	}
	*/
	
	values.push_back(234);
	values.emplace_back(567);
	copy(begin(values), end(values), ostream_iterator<int> {cout, " "});
	cout << endl << "vector size: " << values.size() << endl;
	cout << "vector capacity: " << values.capacity() << endl;
	
	values.emplace(begin(values), 890);
	values.emplace(values.end(), 111);
	values.emplace(begin(values) + 3, 888);
	copy(begin(values), end(values), ostream_iterator<int> {cout, " "});
	cout << endl << "vector size: " << values.size() << endl;
	cout << "vector capacity: " << values.capacity() << endl;
	
	values.insert(begin(values), 555);
	values.insert(values.end(), 666);
	values.insert(begin(values) + 3, 777);
	copy(begin(values), end(values), ostream_iterator<int> {cout, " "});
	cout << endl << "vector size: " << values.size() << endl;
	cout << "vector capacity: " << values.capacity() << endl;
	
    return 0;
}
