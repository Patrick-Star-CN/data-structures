#include <iostream>
#include "Heap/Heap.h"
using namespace std;

int main() {
    heap<int> h;
    h.add(9);
    h.add(6);
    h.add(7);
    h.add(3);
    h.add(1);
    return 0;
}
