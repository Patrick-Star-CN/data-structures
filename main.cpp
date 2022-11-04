#include "Deque/Deque.h"

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
    a.pushBack(1);
    for (auto it = a.begin(); it != a.end(); it ++) {
        cout << *it << " ";
    }
    cout << endl;
    a.popFront();
    for (auto it = a.begin(); it != a.end(); it ++) {
        cout << *it << " ";
    }
    cout << endl;
    a.pushBack(1);
    for (auto it = a.begin(); it != a.end(); it ++) {
        cout << *it << " ";
    }
    cout << endl;
    a.pushBack(1);
    for (auto it = a.begin(); it != a.end(); it ++) {
        cout << *it << " ";
    }
    cout << endl;
    a.pushBack(1);
    for (auto it = a.begin(); it != a.end(); it ++) {
        cout << *it << " ";
    }
    cout << endl;
    a.pushBack(1);
    for (auto it = a.begin(); it != a.end(); it ++) {
        cout << *it << " ";
    }
    cout << endl;
    return 0;
}