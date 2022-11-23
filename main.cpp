#include <iostream>

using namespace std;
template<typename DataType>
class BinNode {
public:
    DataType data;
    bool rightThread;
    BinNode *left;
    BinNode *right;
    BinNode(): rightThread(false), left(0), right(0) {}
    BinNode(DataType item): data(item), left(0), right(0) {}
};
template<typename DataType>
class BST {
public:
    BinNode<DataType> *root;
    BST(): root(0) {}
    bool empty();
    void insert(DataType item);
    void RightThread();
    void rightThread(BinNode<DataType> *);
    void InorderRightThreadTree();
    BinNode<DataType> *treeMax(BinNode<DataType> *);
    BinNode<DataType> *treeMin(BinNode<DataType> *);
    BinNode<DataType> *treeFind(BinNode <DataType> *, DataType);
};

template<typename DataType>
bool BST<DataType>::empty() {
    return root == 0;
}

template<typename DataType>
BinNode<DataType> *BST<DataType>::treeMin(BinNode<DataType> *r) {
    while (r->left) {
        r = r->left;
    }
    return r;
}

template<typename DataType>
void BST<DataType>::InorderRightThreadTree() {
    auto ptr = root;
    while (ptr) {
        ptr = treeMin(ptr);
        cout << ptr->data << " ";
        while (ptr->rightThread) {
            ptr = ptr->right;
            cout << ptr->data << " ";
        }
        ptr = ptr->right;
    }
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
void BST<DataType>::RightThread() {
    rightThread(root);
}

template<typename DataType>
void BST<DataType>::rightThread(BinNode<DataType> *r) {
    if (r->left) {
        auto pre = treeMax(r->left);
        pre->rightThread = true;
        pre->right = r;
        rightThread(r->left);
    }
    if (r->right && !r->rightThread) {
        rightThread(r->right);
    }
}

template<typename DataType>
BinNode<DataType> *BST<DataType>::treeMax(BinNode<DataType> *r) {
    while (r->right && !r->rightThread) {
        r = r->right;
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

int main() {
    BST<int> tree;
    tree.insert(8);
    tree.insert(5);
    tree.insert(11);
    tree.insert(2);
    tree.insert(6);
    tree.insert(10);
    tree.insert(12);
    tree.insert(1);
    tree.insert(4);
    tree.insert(7);
    tree.insert(9);
    tree.insert(13);
    tree.insert(3);
    tree.RightThread();
    tree.InorderRightThreadTree();
    return 0;
}
