#include "Deque/Deque.h"
#include <map>

using namespace std;

int main() {
    Deque<int> a(2);
    a.pushBack(1);
    a.pushBack(2);
    a.pushBack(5);
    for (auto it = a.begin(); it != a.end(); it ++) {
        cout << *it << " ";
    }
    cout << endl;
    a.popBack();
    a.pushBack(3);
    a.popFront();
    a.popFront();
    a.pushBack(6);
    for (auto it = a.begin(); it != a.end(); it ++) {
        cout << *it << " ";
    }
    cout << endl;
    a.pushBack(12);
    for (auto it = a.begin(); it != a.end(); it ++) {
        cout << *it << " ";
    }
    a.pushBack(123);
    for (auto it = a.begin(); it != a.end(); it ++) {
        cout << *it << " ";
    }
    cout << endl;
    a.pushBack(121);
    for (auto it = a.begin(); it != a.end(); it ++) {
        cout << *it << " ";
    }
    cout << endl;
    return 0;
}