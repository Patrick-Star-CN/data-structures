#include <iostream>
#include "BST/BST.h"
using namespace std;

int main() {
    BST<int> tree;
    tree.insert(23);
    tree.insert(11);
    tree.insert(56);
    tree.insert(5);
    tree.insert(20);
    tree.insert(30);
    tree.insert(89);
    tree.insert(77);
    tree.insert(45);
    tree.insert(50);
    tree.inOrderTraversal();
    tree.preOrderTraversal();
    tree.postOrderTraversal();
    tree.treePrint();
    return 0;
}
