#include "Map/Map.h"
#include <iostream>

using namespace std;

int main() {
    Map<int, int> map;
    map.insert(Pair<int, int>(4, 1));
    map.insert(Pair<int, int>(6, 1));
    map.insert(Pair<int, int>(3, 1));
    map.insert(Pair<int, int>(1, 1));
    map.insert(Pair<int, int>(2, 1));
//    map.insert(Pair<int, int>(3, 1));
//    map.insert(Pair<int, int>(2, 1));
//    map.insert(Pair<int, int>(1, 1));
    return 0;
}
