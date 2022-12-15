#include <iostream>
#include "Heap/Heap.h"
using namespace std;

int main() {
    Heap<int> h;
    h.add(9);
    h.add(6);
    h.add(7);
    h.add(3);
    h.add(1);
    h.add(10);
    h.add(2);
    h.add(5);
    while (!h.empty()) {
        cout << h.top() << " ";
        h.removeTop();
    }
    return 0;
}
