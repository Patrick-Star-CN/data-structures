#include <iostream>
#include "Stack/Stack.h"
#include "String/String.h"

using namespace std;

template<typename T>
T baseCal(T left, T right, char c) {
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
        return (int) left % (int) right;
    }
    throw std::runtime_error("OPERATOR_ERROR");
}

template<typename T>
void calculate(Stack<T> &number, Stack<char> &operatorChar) {
    T sum;
    sum = number.top();
    number.pop();
    sum = baseCal<T>(number.top(), sum, operatorChar.top());
    number.pop();
    number.push(sum);
    operatorChar.pop();
}

template<typename T>
void cal(Stack<T> &number, istream &in) {
    Stack<char> operatorChar;
    char c;
    bool flag = false;
    T num;
    while ((c = in.peek()) != '\n') {
        if (c == ' ') {
            getchar();
            continue;
        } else if (isdigit(c)) {
            in >> num;
            if (flag) {
                num = -num;
                flag = false;
            }
            number.push(num);
        } else {
            in >> c;
            if (c == '(') {
                operatorChar.push(c);
                while (in.peek() == ' ') {
                    getchar();
                }
                if (in.peek() == '-') {
                    flag = true;
                    getchar();
                }
            } else if (c == ')') {
                while (operatorChar.top() != '(') {
                    calculate<T>(number, operatorChar);
                }
                operatorChar.pop();
            } else if (c == '-' && number.empty()) {
                flag = true;
            } else if (!operatorChar.empty() &&
                       (operatorChar.top() == '*' || operatorChar.top() == '/' || operatorChar.top() == '%')) {
                calculate<T>(number, operatorChar);
                operatorChar.push(c);
            } else {
                operatorChar.push(c);
            }
        }
    }
    while (!operatorChar.empty()) {
        calculate<T>(number, operatorChar);
    }
    cout << "ans=" << number.top();
}

void putBack(istream &in, String str) {
    in.putback('\n');
    auto it = str.end();
    for (it--; it != str.begin(); it--) {
        in.putback(*it);
    }
    in.putback(*it);
}

int main() {
    int typeNum;
    String str(unsigned(100));
    cout << "请输入表达式(推荐数字或变量与符号之间用空格间隔,请使用半角符号)" << endl;
    str.getLine(cin);
    if (str.find("%") != -1) {
        typeNum = 1;
    } else if (str.find(".") != -1) {
        typeNum = 2;
    } else {
        for (auto it = str.begin(); it != str.end(); it++) {
            if (isalpha(*it)) {
                typeNum = 3;
                break;
            }
        }
        if (typeNum != 3) {
            typeNum = 1;
        }
    }
    switch (typeNum) {
        case 1: {
            Stack<int> number;
            putBack(cin, str);
            try {
                cal<int>(number, cin);
            } catch (runtime_error error) {
                cout << "输入的表达式有误";
            }
            break;
        }
        case 2: {
            Stack<double> number;
            putBack(cin, str);
            try {
                cal<double>(number, cin);
            } catch (runtime_error error) {
                cout << "输入的表达式有误";
            }
            break;
        }
        case 3: {
            Stack<double> number;
            String str_;
            String s;
            double num;
            char num_[100];
            cout << "请输入变量值(变量与数值用:间隔，变量间用空格间隔)" << endl;
            while (cin.peek() != '\n') {
                str_.read(cin, ':');
                getchar();
                cin >> num;
                sprintf(num_, "%lf", num);
                str.replaceAll(str_, num_);
            }
            putBack(cin, str);
            try {
                cal<double>(number, cin);
            } catch (runtime_error error) {
                cout << "输入的表达式有误";
            }
            break;
        }
    }
    return 0;
}