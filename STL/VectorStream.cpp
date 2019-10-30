/*************************************************************************
	> FileName  : VectorStream.cpp
	> Author    : zhouzhijun
	> Mail      : snjzzjun@163.com
	> CreateTime: 2019年10月30日 星期三 14时58分03秒
*************************************************************************/

#include <iostream>
#include <string>
#include <algorithm>
#include <iterator>
#include <vector>

using namespace std;

int main(int argc, char *argv[])
{
    vector<string> words;
    words.reserve(10);
    
    cout << string (20, '*') << endl;
    cout << "Enter words separated by spaces. Enter Ctrl+D(linux)/Ctrl+Z(windows) on a separate line to end:" << endl;
    #if 0
    istream_iterator<string> startIt(cin);
    istream_iterator<string> endIt;
    
    copy(startIt, endIt, back_inserter(words));
    
    for (auto& word : words)
    {
        cout << "string: " << word << endl;
    }
    cout << "output end" << endl;
    #else
    copy(istream_iterator<string> {cin}, istream_iterator<string> {}, back_inserter(words));

    cout << "start sort string" << endl;
    bool range_flag = false;
    while(true)
    {
        for (auto first = words.begin() + 1; first != words.end(); ++first)
        {
            if (*(first-1) > *first)
            {
                swap(*(first-1), *first);
                range_flag = true;
            }
        }
        if (!range_flag)
        {
            break;
        }
        range_flag = false;
    }

    cout << string (20, '*') << endl;
    copy(begin(words), end(words), ostream_iterator<string> {cout, "\n"} );
    #endif
    
    cout << string (20, '*') << endl;
    
    vector<string> copy_words {make_move_iterator(words.begin()), make_move_iterator(words.end())};
    copy(begin(copy_words), end(copy_words), ostream_iterator<string> {cout, "\n"} );
    cout << string (20, '*') << endl;

    if (words.front().empty())
    {
        cout << "words is empty" << endl;
    }
    else
    {
        copy(begin(words), end(words), ostream_iterator<string> {cout, "\n"} );
    }
    
    cout << "process run end" << endl;
    cout << string (20, '*') << endl;
    
    return 0;
}

