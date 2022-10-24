#include <iostream>
#include <ctype.h>
#include "Stack/Stack.h"
using namespace std;

template<typename T>
T __cal(T left, T right, char c) {
    switch (c) {
        case '+': {
            return left + right;
        }
        case '-': {
            return left - right;
        }
        case '*': {
            return left * right;
        }
        case '/': {
            return left / right;
        }
    }
    if (typeid(T) == typeid(int) && c == '%') {
        return (int)left % (int)right;
    }
}

template<typename T1, typename T2>
void _cal(Stack<T1> &number, Stack<T2> &operatorChar) {
    T1 sum;
    sum = number.top();
    number.pop();
    sum = __cal<T1>(number.top(), sum, operatorChar.top());
    number.pop();
    number.push(sum);
    //cout << sum << endl;
    operatorChar.pop();
}

template<typename T>
void cal(Stack<T> &number) {
    Stack<char> operatorChar;
    char c;
    T num;
    while ((c = cin.peek()) != '\n') {
        if (c == ' ') {
            c = getchar();
        } else if (isdigit(c)) {
            cin >> num;
            number.push(num);
        } else {
            cin >> c;
            if (c == '(') {
                operatorChar.push(c);
            } else if (c == ')') {
                while (operatorChar.top() != '(') {
                    _cal<T, char>(number, operatorChar);
                }
                operatorChar.pop();
            } else if (!operatorChar.empty() && (operatorChar.top() == '*' || operatorChar.top() == '/' || operatorChar.top() == '%')) {
                _cal<T, char>(number, operatorChar);
                operatorChar.push(c);
            } else {
                operatorChar.push(c);
            }
        }
    }
    while (!operatorChar.empty()) {
        _cal<T, char>(number, operatorChar);
    }
    cout << number.top();
}

int  main() {
    int typeNum;
    cout << "请输入想要计算的表达式类型：" << endl
         << "1: 整数型;" << endl
         << "2: 浮点型;" << endl
         << "3: 变量型;" << endl;
    cin >> typeNum;
    char ch = getchar();
    switch (typeNum) {
        case 1: {
            Stack<int> number;
            cal<int>(number);
            break;
        }
        case 2: {
            Stack<double> number;
            cal<double>(number);
            break;
        }
    }
    return 0;
}