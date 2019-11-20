/*************************************************************************
	> FileName  : StackExample.cpp
	> Author    : zhouzhijun
	> Mail      : snjzzjun@163.com
	> CreateTime: 2019年11月15日 星期五 13时38分59秒
*************************************************************************/

#include <iostream>
#include <stdexcept>
#include <string>
#include <algorithm>
#include <stack>
#include <cmath>

using namespace std;

inline int GetOperatorPrecedence(const char operatorChar)
{
    int OperatorPrecedence = 0;
    
    if (operatorChar == '+' || operatorChar == '-')
    {
        OperatorPrecedence = 1;
    }
    else if (operatorChar == '*' || operatorChar == '/')
    {
        OperatorPrecedence = 2;
    }
    else if (operatorChar == '^')
    {
        OperatorPrecedence = 3;
    }
    else
    {
        throw runtime_error(string("invalid operator in precedence() function: " + operatorChar));
    }
    
    return OperatorPrecedence;
}

template <typename OperandType>
OperandType ExcuteArithmeticOperation(stack<char>& operatorStack, stack<OperandType>& operandStack)
{
    OperandType calcResult = 0.0;
    OperandType calcOperandLeft = 0.0, calcOperandRight = 0.0;
    char calcOperator = 0;
    
    calcOperandRight = operandStack.top();
    operandStack.pop();
    calcOperandLeft = operandStack.top();
    operandStack.pop();
    calcOperator = operatorStack.top();
    
    //cout << calcOperandLeft << calcOperator << calcOperandRight << endl;
    switch (calcOperator)
    {
        case '+':
            calcResult = calcOperandLeft + calcOperandRight;
            break;
        case '-':
            calcResult = calcOperandLeft - calcOperandRight;
            break;
        case '*':
            calcResult = calcOperandLeft * calcOperandRight;
            break;
        case '/':
            calcResult = calcOperandLeft / calcOperandRight;
            break;
        case '^':
            calcResult = pow(calcOperandLeft, calcOperandRight);
            break;
        default:
            throw runtime_error(string("invalid operator: " + calcOperator));
    }
    operatorStack.pop();
    operandStack.push(calcResult);
    
    return calcResult;
}

int main(int argc, char *argv[])
{
    stack<double> operandStack;
    stack<char> operatorStack;
    string calcExpress;
    size_t indexString = 0, indexOffset = 0;
    
    cout << "An arithmetic expression can include the operators +, -, *, /, and ^ for exponentiation." << endl;
    try
    {
        while (true)
        {
            cout << "Please input arithmetic expression(end by Enter. Input \"exit\" to exit process):" << endl;
            getline(cin, calcExpress, '\n');
            if (calcExpress.empty())
            {
                cout << "Arithmetic expression is empty, please input it again..." << endl;
                continue;
            }
            calcExpress.erase(remove(begin(calcExpress), end(calcExpress), ' '), end(calcExpress));
            
            indexString = 0, indexOffset = 0;
            operandStack.push(stod(calcExpress, &indexOffset));
            indexString += indexOffset;
            while (true)
            {
                if (indexString < calcExpress.length())
                {
                    operatorStack.push(calcExpress[indexString]);
                    indexString += 1;
                    operandStack.push(stod(calcExpress.substr(indexString), &indexOffset));
                    indexString += indexOffset;
                }
                else if (indexString == calcExpress.length())
                {
                    while (!operatorStack.empty())
                    {
                        ExcuteArithmeticOperation<double>(operatorStack, operandStack);
                    }
                    break;
                }
                
                while (!operatorStack.empty() && GetOperatorPrecedence(calcExpress[indexString]) <= GetOperatorPrecedence(operatorStack.top()))
                {
                    ExcuteArithmeticOperation<double>(operatorStack, operandStack);
                }
            }
            
            cout << calcExpress << " = " << operandStack.top() << std::endl;
            operandStack.pop();
        }
    }
    catch (const exception& errorEvent)
    {
        cerr << errorEvent.what() << endl;
    }
    
    cout << "Calculator ending..." << endl;
    
    return 0;
}
