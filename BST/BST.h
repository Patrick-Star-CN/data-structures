#ifndef DATA_STRUCTURES_BST_H
#define DATA_STRUCTURES_BST_H

#include "../Deque/Deque.h"
#include <iostream>
#include <cmath>

template<typename DataType>
class BinNode {
public:
    DataType data;
    bool rightThread;
    BinNode *left;
    BinNode *right;

    BinNode() : rightThread(false), left(0), right(0) {}

    BinNode(DataType item) : data(item), left(0), right(0) {}
};

template<typename DataType>
class BST {
public:
    BinNode<DataType> *root;

    BST() : root(0) {}

    ~BST();

    bool empty();

    void insert(DataType item);

    void erase(DataType item);

    BinNode<DataType> *treeMax(BinNode<DataType> *);

    BinNode<DataType> *treeMin(BinNode<DataType> *);

    BinNode<DataType> *treeFind(BinNode<DataType> *, DataType);

    void preOrderTraversal();

    void inOrderTraversal();

    void postOrderTraversal();

    void levelOrderTraversal();

    void preOrder(BinNode<DataType> *);

    void inOrder(BinNode<DataType> *);

    void postOrder(BinNode<DataType> *);

    void treePrint();

    void inOrderPrint(BinNode<DataType> *, int);
};

template<typename DataType>
bool BST<DataType>::empty() {
    return root == 0;
}

template<typename DataType>
void BST<DataType>::insert(DataType item) {
    if (empty()) {
        root = new BinNode<DataType>(item);
        return;
    }
    auto pos = treeFind(root, item);
    if (pos->data < item) {
        pos->right = new BinNode<DataType>(item);
    } else {
        pos->left = new BinNode<DataType>(item);
    }
}

template<typename DataType>
void BST<DataType>::erase(DataType item) {
    if (empty()) {
        return;
    }
    auto pos = treeFind(root, item);
    if (pos->data != item) {
        return;
    }
    auto next = (pos->left && pos->right) ? treeMin(pos->right) : pos;
    auto parent = root;
    while (true) {
        if (parent->left && parent->left->data == next->data || parent->right && parent->right->data == next->data) {
            break;
        }
        if (parent->data > next->data && parent->left) {
            parent = parent->left;
        } else if (parent->data < next->data && parent->right) {
            parent = parent->right;
        }
    }
    if (pos != next) {
        pos->data = next->data;
    }
    if (parent->left && parent->left->data == next->data) {
        parent->left = next->left != nullptr ? next->left : next->right;
    } else {
        parent->right = next->left != nullptr ? next->left : next->right;
    }
    if (next->left) {
        next->data = next->left->data;
    } else if (next->right) {
        next->data = next->right->data;
    }
    delete next;
}

template<typename DataType>
BinNode<DataType> *BST<DataType>::treeMax(BinNode<DataType> *r) {
    while (r->right && !r->rightThread) {
        r = r->right;
    }
    return r;
}

template<typename DataType>
BinNode<DataType> *BST<DataType>::treeMin(BinNode<DataType> *r) {
    while (r->left) {
        r = r->left;
    }
    return r;
}

template<typename DataType>
BinNode<DataType> *BST<DataType>::treeFind(BinNode<DataType> *r, DataType item) {
    while (r->data != item) {
        if (r->data > item && r->left) {
            r = r->left;
        } else if (r->data < item && r->right) {
            r = r->right;
        } else {
            break;
        }
    }
    return r;
}

template<typename DataType>
BST<DataType>::~BST() {
    Deque<BinNode<DataType> *> deque;
    auto ptr = root;
    deque.pushBack(root);
    while (!deque.empty()) {
        ptr = deque.front();
        if (ptr->left) {
            deque.pushBack(ptr->left);
        }
        if (ptr->right) {
            deque.pushBack(ptr->right);
        }
        delete ptr;
        deque.popFront();
    }
}

template<typename DataType>
void BST<DataType>::preOrderTraversal() {
    if (!root) {
        return;
    }
    std::cout << root->data << " ";
    if (root->left) {
        preOrder(root->left);
    }
    if (root->right) {
        preOrder(root->right);
    }
    std::cout << std::endl;
}

template<typename DataType>
void BST<DataType>::inOrderTraversal() {
    if (!root) {
        return;
    }
    if (root->left) {
        inOrder(root->left);
    }
    std::cout << root->data << " ";
    if (root->right) {
        inOrder(root->right);
    }
    std::cout << std::endl;
}

template<typename DataType>
void BST<DataType>::postOrderTraversal() {
    if (!root) {
        return;
    }
    if (root->left) {
        postOrder(root->left);
    }
    if (root->right) {
        postOrder(root->right);
    }
    std::cout << root->data << " ";
    std::cout << std::endl;
}

template<typename DataType>
void BST<DataType>::preOrder(BinNode<DataType> *ptr) {
    if (!ptr) {
        return;
    }
    std::cout << ptr->data << " ";
    if (ptr->left) {
        preOrder(ptr->left);
    }
    if (ptr->right) {
        preOrder(ptr->right);
    }
}

template<typename DataType>
void BST<DataType>::inOrder(BinNode<DataType> *ptr) {
    if (!ptr) {
        return;
    }
    if (ptr->left) {
        inOrder(ptr->left);
    }
    std::cout << ptr->data << " ";
    if (ptr->right) {
        inOrder(ptr->right);
    }
}

template<typename DataType>
void BST<DataType>::postOrder(BinNode<DataType> *ptr) {
    if (!ptr) {
        return;
    }
    if (ptr->left) {
        postOrder(ptr->left);
    }
    if (ptr->right) {
        postOrder(ptr->right);
    }
    std::cout << ptr->data << " ";
}

template<typename DataType>
void BST<DataType>::levelOrderTraversal() {
    Deque<BinNode<DataType> *> deque;
    auto ptr = root;
    deque.pushBack(root);
    while (!deque.empty()) {
        ptr = deque.front();
        if (ptr->left) {
            deque.pushBack(ptr->left);
        }
        if (ptr->right) {
            deque.pushBack(ptr->right);
        }
        std::cout << ptr->data << " ";
        deque.popFront();
    }
    std::cout << std::endl;
}

template<typename DataType>
void BST<DataType>::treePrint() {
    inOrderPrint(root, 0);
}

template<typename DataType>
void BST<DataType>::inOrderPrint(BinNode<DataType> *ptr, int num) {
    if (!ptr) {
        return;
    }
    if (ptr->left) {
        inOrderPrint(ptr->left, num + 1);
    }
    for (int i = 0; i < num; ++i) {
        std::cout << '\t';
    }
    std::cout << ptr->data << std::endl;
    if (ptr->right) {
        inOrderPrint(ptr->right, num + 1);
    }
}

#endif //DATA_STRUCTURES_BST_H
