#include <iostream>
#include "include/Test.h"
#include "include/LinkList.h"


int main() {
    Test test(1), test2(2);
    LinkList<Test> list;
    std::cout << list.empty();
    list.insert(test2);
    list.insert(test);
    list.display(std::cout);
    list.erase(1);
    list.display(std::cout);
    std::cout << list.empty();
    return 0;
}
