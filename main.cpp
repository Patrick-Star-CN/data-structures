#include <iostream>
#include "LinkList/LinkList.h"
using namespace std;

int main() {
    LinkList<int> list;
    list.pushBack(5);
    list.pushBack(2);
    list.pushBack(9);
    list.pushBack(7);
    list.pushBack(1);
    list.InsertSortList();
    return 0;
}
