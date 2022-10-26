#include <iostream>
#include "Stack/Stack.h"
#include "String/String.h"
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
    throw "OPERATOR_ERROR";
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
    bool flag = false;
    T num;
    while ((c = cin.peek()) != '\n') {
        if (c == ' ') {
            getchar();
            continue;
        } else if (isdigit(c)) {
            cin >> num;
            if (flag) {
                num = -num;
                flag = false;
            }
            number.push(num);
        } else {
            cin >> c;
            if (c == '(') {
                operatorChar.push(c);
                while (cin.peek() == ' ') {
                    getchar();
                }
                if (cin.peek() == '-') {
                    flag = true;
                    getchar();
                }
            } else if (c == ')') {
                while (operatorChar.top() != '(') {
                    _cal<T, char>(number, operatorChar);
                }
                operatorChar.pop();
            } else if (c == '-' && number.empty()) {
                flag = true;
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
    cout << "ans=" << number.top();
}

int main() {
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
            try {
                cal<int>(number);
            } catch (const char *error) {
                cout << "输入的表达式有误" << endl;
            }
            break;
        }
        case 2: {
            Stack<double> number;
            try {
                cal<double>(number);
            } catch (const char *error) {
                cout << "输入的表达式有误" << endl;
            }
            break;
        }
        case 3: {

        }
    }
    return 0;
}