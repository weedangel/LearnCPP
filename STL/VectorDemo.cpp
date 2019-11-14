/*************************************************************************
	> FileName  : VectorDemo.cpp
	> Author    : zhouzhijun
	> Mail      : snjzzjun@163.com
	> CreateTime: 2019年11月14日 星期四 16时01分25秒
*************************************************************************/

#include <iostream>

using namespace std;

template <typename objType>
class IteratorDemo {
public:    
    typedef typename objType::value_type value_type;
    typedef typename objType::pointer pointer;
    typedef typename objType::reference reference;
private:
    unsigned int index;
    pointer dataPtr;
public:
    IteratorDemo(objType& objData): index(0) {dataPtr = objData.dataPtr;};
    IteratorDemo(const IteratorDemo& tempIter) {dataPtr = tempIter.dataPtr;};
    
    ~IteratorDemo() {cout << "delete IteratorDemo" << endl;};
    value_type operator*();
};

template <typename objType>
typename IteratorDemo<objType>::value_type IteratorDemo<objType>::operator*()
{
    return dataPtr[index];
}

template <typename ItemType>
class VectorDemo {
public:
    typedef ItemType value_type;
    typedef ItemType* pointer;
    typedef ItemType& reference;
    
    /* 在模板类内部声明时，使用当前类作为另外一个模板的类型参数时，可以不给当前模板类指明类型参数 */
    typedef IteratorDemo<VectorDemo> iterator;
private:
    unsigned int size;
    unsigned int capacity;
    unsigned int maxSize;
    ItemType* dataPtr;
public:
    VectorDemo(unsigned int vectorSize): size(vectorSize), capacity(10), maxSize(100) {
        dataPtr = new ItemType[vectorSize];
        for (unsigned int i = 0; i < vectorSize; i++) {
            dataPtr[i] = (i + 1) * 4;
        }
    };
    
    ~VectorDemo() {delete[] dataPtr; cout << "delete VectorDemo" << endl;};
    
    IteratorDemo<VectorDemo> begin();
    
    friend class  IteratorDemo<VectorDemo>;
};

/* 在类外面使用一个模板类做类型产生的时候需要给这个模板类指明类型参数，这个参数可以不具体（可以是另外一个类型参数变量），但必须指明 */
template <typename ItemType>
IteratorDemo< VectorDemo<ItemType> > VectorDemo<ItemType>::begin()
{
    IteratorDemo< VectorDemo<ItemType> > tempIter(*this);
    
    return tempIter;
}

int main(int argc, char *argv[])
{
    cout << "start test" << endl;
    
    VectorDemo<int> myVector(10);
    VectorDemo<int>::iterator myIter = myVector.begin();

    cout << "VectorDemo value: " << *myIter << endl;
    
    cout << "end test" << endl;
    return 0;
}
