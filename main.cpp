#include <iostream>
#include <vector>
using namespace std;
vector<int> number, v(10, 20);
int num, i;
//仔细阅读下列代码 并按要求给出display输出的内容，其中display的定义如下：
void display(vector<int>& vec) {
    for (vector<int>::iterator it = vec.begin(); it != vec.end(); it++)
        cout << *it << " ";
    cout << endl;
}
bool IsMin2Max(const vector<int>& vec) {
    vector<int>::const_iterator it = vec.begin();
    vector<int>::const_iterator it_ = vec.begin();
    for (it ++; it != vec.end(); it ++, it_ ++) {
        if (*it < *it_) {
            return false;
        }
    }
    return true;
}

template<class T>
T FW(const vector<T>& vec) {
    auto it = vec.begin();
    T Max = *it, Min = *it;
    for (it ++; it != vec.end(); it ++) {
        if (*it < Min) {
            Min = *it;
        }
        if (*it > Max) {
            Max = *it;
        }
    }
    return Max - Min;
}

int main(){

// (1)依次输入99 33 44 88 22 11 55 66 77  -1 ，执行后的display输出为？
    while (1) {
        cin >> num;
        if (num < 0) break;
        number.push_back(num);
    }
    display(number);
    cout << FW<int>(number);
    return 0;
}