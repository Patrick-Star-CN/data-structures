#ifndef DATA_STRUCTURES_MAP_H
#define DATA_STRUCTURES_MAP_H

#include <iostream>

template<typename T, typename U>
class Pair {
private:
    T key;
    U value;

public:
    explicit Pair(T k, U v) : key(k), value(v) {}

    Pair(const Pair<T, U> &ori) : key(ori.key), value(ori.value) {}

    T getKey() const {
        return key;
    }

    void setKey(T k) {
        key = k;
    }

    U getValue() const {
        return value;
    }

    void setValue(U v) {
        value = v;
    }
};

template<typename T, typename U>
class Map {
private:
    class Node {
    private:
        Node *left;
        Node *right;
        Node *parent;
        bool isBlack;
        Pair<T, U> data;
    public:
        explicit Node(Pair<T, U> data) : data(data), left(nullptr), right(nullptr), parent(nullptr), isBlack(false) {}

        explicit Node(Pair<T, U> data, Node *father) : data(data), left(nullptr), right(nullptr), parent(father), isBlack(false) {}

        Node(const Node &ori) : left(ori.left), right(ori.right), data(ori.data) {}

        Node *getLeft() const {
            return left;
        }

        void setLeft(Node *l) {
            Node::left = l;
        }

        bool hasLeft() const {
            return left != nullptr;
        }

        Node *getRight() const {
            return right;
        }

        void setRight(Node *r) {
            Node::right = r;
        }

        bool hasRight() const {
            return right != nullptr;
        }

        const Pair<T, U> &getData() const {
            return data;
        }

        void setData(const Pair<T, U> &d) {
            Node::data = d;
        }

        Node *getParent() const {
            return parent;
        }

        void setParent(Node *f) {
            Node::parent = f;
        }

        bool hasParent() const {
            return parent != nullptr;
        }

        const bool getIsBlack() {
            return isBlack;
        }

        void setIsBlack(bool black) {
            isBlack = black;
        }

        int treeIsLeftChild(Node *x) {
            if (!x->hasParent()) {
                return -1;
            }
            return x == x->getParent()->getParent();
        }

        Node *treeMin(Node *r) {
            while (r->hasLeft()) {
                r = r->getLeft();
            }
            return r;
        }

        Node *treeMax(Node *r) {
            while (r->hasRight()) {
                r = r->getRight();
            }
            return r;
        }

        Node *treeNext(Node *x) {
            if (x->hasRight()) {
                return treeMin(x->getRight());
            }
            while (treeIsLeftChild(x) == 0) {
                x = x->getParent();
            }
            if (treeIsLeftChild(x) == -1) {
                return nullptr;
            }
            return x->getParent();
        }

        Node *treePrev(Node *x) {
            if (x->hasLeft()) {
                return treeMax(x->getLeft());
            }
            while (treeIsLeftChild(x) == 1) {
                x = x->getParent();
            }
            if (treeIsLeftChild(x) == -1) {
                return nullptr;
            }
            return x->getParent();
        }

        Node *treeFind(Node *x, T key) {
            Node *ptr = x;
            while (ptr->getData().getKey() != key) {
                if (ptr->getData().getKey() > key && ptr->hasLeft()) {
                    ptr = ptr->getLeft();
                } else if (ptr->getData().getKey() < key && ptr->hasRight()) {
                    ptr = ptr->getRight();
                } else {
                    break;
                }
            }
        }

        void treeLeftRotate(Node *x) {
            Node *y = x->getRight();
            x->setRight(y->getLeft());
            if (x->hasRight()) {
                x->getRight()->setParent(x);
            }
            y->setParent(x->getParent());
            if (treeIsLeftChild(x) == 1) {
                x->getParent()->setLeft(y);
            } else if (x->hasParent() != -1) {
                x->getParent()->setRight(y);
            }
            y->setLeft(x);
            x->setParent(y);
        }

        void treeRightRotate(Node *x) {
            Node *y = x->getLeft();
            x->setLeft(y->getRight());
            if (x->hasLeft()) {
                x->getLeft()->setParent(x);
            }
            y->setParent(x->getParent());
            if (treeIsLeftChild(x) == 1) {
                x->getParent()->setLeft(y);
            } else if (x->hasParent() != -1) {
                x->getParent()->setRight(y);
            }
            y->setRight(x);
            x->setParent(y);
        }

        void treeBalanceAfterInsert(Node *r, Node *x) {
            x->setIsBlack(x == r);
            while (x != r && !x->getParent()->getIsBlack()) {
                if (treeIsLeftChild(x->getParent()) == 1) {
                    Node *y = x->getParent()->getParent()->getRight();
                    if (y != nullptr && !y->getIsBlack()) {
                        x = x->getParent();
                        x->setIsBlack(true);
                        x = x->getParent();
                        x->setIsBlack(x == r);
                        y->setIsBlack(true);
                    } else {
                        if (treeIsLeftChild(x) == 0) {
                            x = x->getParent();
                            treeLeftRotate(x);
                        }
                        x = x->getParent();
                        x->setIsBlack(true);
                        x = x->getParent();
                        x->setIsBlack(false);
                        treeRightRotate(x);
                        break;
                    }
                } else {
                    Node *y = x->getParent()->getParent()->getLeft();
                    if (y != nullptr && !y->getIsBlack()) {
                        x = x->getParent();
                        x->setIsBlack(true);
                        x = x->getParent();
                        x->setIsBlack(x == r);
                        y->setIsBlack(true);
                    } else {
                        if (treeIsLeftChild(x) == 1) {
                            x = x->getParent();
                            treeRightRotate(x);
                        }
                        x = x->getParent();
                        x->setIsBlack(true);
                        x = x->getParent();
                        x->setIsBlack(false);
                        treeLeftRotate(x);
                        break;
                    }
                }
            }
        }

        void treeRemove(Node *r, Node *z) {
            Node *y = (z->hasLeft() && z->hasRight() ? treeNext(z) : z);
            Node *x = y->hasLeft() ? y->getLeft() : y->getRight();
            Node *w = nullptr;
            if (x != nullptr) {
                x->setParent(y->getParent());
            }
            if (treeIsLeftChild((y)) == -1) {
                r = x;
            } else if (treeIsLeftChild((y)) == 1) {
                y->getParent()->setLeft(x);
                w = y->getParent()->getRight();
            } else {
                y->getParent()->setRight(x);
                w = y->getParent()->getLeft();
            }
            bool removedBlack = y->getIsBlack();
            if (y != z) {
                y->setParent(z->getParent());
                if (treeIsLeftChild(z) == 1) {
                    y->getParent()->setLeft(y);
                } else {
                    y->getParent()->setRight(y);
                }
                y->setLeft(z->getLeft());
                y->getLeft()->setParent(y);
                y->setRight(z->getRight());
                if (y->hasRight()) {
                    y->getRight()->setParent(y);
                }
                y->setIsBlack(z->getIsBlack());
                if (r == z) {
                    r = y;
                }
            }
            if (removedBlack && r != nullptr) {
                if (x != nullptr) {
                    x->setIsBlack(true);
                } else {
                    while (true) {
                        if (treeIsLeftChild(w) == 0) {
                            if (!w->getIsBlack()) {
                                w->setIsBlack(true);
                                w->getParent()->setIsBlack(false);
                                treeLeftRotate(w->getParent());
                                if (r == w->getLeft()) {
                                    r = w;
                                }
                                w = w->getLeft()->getRight();
                            }
                            if ((!w->hasLeft() || w->getLeft()->getIsBlack()) &&
                                (!w->hasRight() || w->getRight()->getIsBlack())) {
                                w->setIsBlack(false);
                                x = w->getParent();
                                if (x == r || !x->getIsBlack()) {
                                    x->setIsBlack(true);
                                    break;
                                }
                                w = treeIsLeftChild(x) ?
                                    x->getParent()->getRight() :
                                    x->getParent()->getLeft();
                            } else {
                                if (!w->hasRight() || w->getRight()->getIsBlack()) {
                                    w->getLeft()->setIsBlack(true);
                                    w->setIsBlack(false);
                                    treeRightRotate(w);
                                    w = w->getParent();
                                }
                                w->setIsBlack(w->getParent()->getIsBlack());
                                w->getParent()->setIsBlack(true);
                                w->getRight()->setIsBlack(true);
                                treeLeftRotate(w->getParent());
                                break;
                            }
                        } else {
                            if (!w->getIsBlack()) {
                                w->setIsBlack(true);
                                w->getParent()->setIsBlack(false);
                                treeRightRotate(w->getParent());
                                if (r == w->getRight()) {
                                    r = w;
                                }
                                w = w->getRight()->getLeft();
                            }
                            if ((!w->hasLeft() || w->getLeft()->getIsBlack()) &&
                                (!w->hasRight() || w->getRight()->getIsBlack())) {
                                w->setIsBlack(false);
                                x = w->getParent();
                                if (x == r || !x->getIsBlack()) {
                                    x->setIsBlack(true);
                                    break;
                                }
                                w = treeIsLeftChild(x) ?
                                    x->getParent()->getRight() :
                                    x->getParent()->getLeft();
                            } else {
                                if (!w->hasRight() || w->getRight()->getIsBlack()) {
                                    w->getRight()->setIsBlack(true);
                                    w->setIsBlack(false);
                                    treeLeftRotate(w);
                                    w = w->getParent();
                                }
                                w->setIsBlack(w->getParent()->getIsBlack());
                                w->getParent()->setIsBlack(true);
                                w->getLeft()->setIsBlack(true);
                                treeRightRotate(w->getParent());
                                break;
                            }
                        }
                    }
                }

            }
        }
    };

    class ConstIterator {
    private:
        const Node *ptr;

    public:
        explicit ConstIterator(Node *ptr) : ptr(ptr) {}

        explicit ConstIterator(Pair<T, U> data) : ptr(new Node(data)) {}

        ConstIterator(const ConstIterator &ori) : ptr(ori.ptr) {}

        ConstIterator &operator=(const ConstIterator &ori) {
            if (&ori == this) {
                return (*this);
            }
            ptr = ori.ptr;
            return (*this);
        }

        ConstIterator &operator=(const Node *p) {
            ptr = p;
            return (*this);
        }

        explicit operator Node *() {
            return ptr;
        }

        const Pair<T, U> operator*() {
            return ptr->getData();
        }

        const Pair<T, U> *operator->() {
            return &(ptr->getData());
        }

        constexpr ConstIterator operator++(int) {
            ConstIterator tmp(*this);
            ++(*this);
            return tmp;
        }

        ConstIterator &operator++() {
            ptr = Node::treeNext(ptr);
            return (*this);
        }

        constexpr ConstIterator operator--(int) {
            ConstIterator tmp(*this);
            --(*this);
            return tmp;
        }

        ConstIterator &operator--() {
            ptr = Node::treePrev(ptr);
            return (*this);
        }

        bool operator==(const ConstIterator &rhs) {
            return ptr->getData().getKey() == rhs.ptr->getData().getKey();
        }

        bool operator!=(const ConstIterator &rhs) {
            return ptr->getData().getKey() != rhs.ptr->getData().getKey();
        }

        bool operator<(const ConstIterator &rhs) {
            return ptr->getData().getKey() < rhs.ptr->getData().getKey();
        }

        bool operator<=(const ConstIterator &rhs) {
            return ptr->getData().getKey() <= rhs.ptr->getData().getKey();
        }

        bool operator>(const ConstIterator &rhs) {
            return ptr->getData().getKey() > rhs.ptr->getData().getKey();
        }

        bool operator>=(const ConstIterator &rhs) {
            return ptr->getData().getKey() >= rhs.ptr->getData().getKey();
        }
    };

    class Iterator {
    private:
        Node *ptr;

    public:
        explicit Iterator(Node *ptr) : ptr(ptr) {}

        explicit Iterator(Pair<T, U> data) : ptr(new Node(data)) {}

        Iterator(const Iterator &ori) : ptr(ori.ptr) {}

        Iterator &operator=(const Iterator &ori) {
            if (&ori == this) {
                return (*this);
            }
            ptr = ori.ptr;
            return (*this);
        }

        Iterator &operator=(Node *p) {
            ptr = p;
            return (*this);
        }

        Iterator &operator=(const ConstIterator &it) {
            ptr = ((Node *) (it));
            return (*this);
        }

        Pair<T, U> &operator*() {
            return ptr->getData();
        }

        Pair<T, U> *operator->() {
            return &(ptr->getData());
        }

        constexpr Iterator operator++(int) {
            Iterator tmp(*this);
            ++(*this);
            return tmp;
        }

        Iterator &operator++() {
            ptr = Node::treeNext(ptr);
            return (*this);
        }

        constexpr Iterator operator--(int) {
            Iterator tmp(*this);
            --(*this);
            return tmp;
        }

        Iterator &operator--() {
            ptr = Node::treePrev(ptr);
            return (*this);
        }

        bool operator==(const Iterator &rhs) {
            return ptr->getData().getKey() == rhs.ptr->getData().getKey();
        }

        bool operator!=(const Iterator &rhs) {
            return ptr->getData().getKey() != rhs.ptr->getData().getKey();
        }

        bool operator<(const Iterator &rhs) {
            return ptr->getData().getKey() < rhs.ptr->getData().getKey();
        }

        bool operator<=(const Iterator &rhs) {
            return ptr->getData().getKey() <= rhs.ptr->getData().getKey();
        }

        bool operator>(const Iterator &rhs) {
            return ptr->getData().getKey() > rhs.ptr->getData().getKey();
        }

        bool operator>=(const Iterator &rhs) {
            return ptr->getData().getKey() >= rhs.ptr->getData().getKey();
        }
    };

    unsigned int distance(Iterator, Iterator);

    Node *root;

public:
    Map() : root(nullptr) {}

    Map(const Map<T, U> &ori) : root(ori.root) {}

    Map &operator=(const Map<T, U> &);

    ~Map();

    void clear();

    Iterator begin();

    ConstIterator cBegin();

    Iterator end();

    ConstIterator cEnd();

    bool empty();

    T &at(const T &);

    const T &at(const T &) const;

    unsigned int size();

    unsigned int count(const T &);

    Iterator find(const T &key);

    ConstIterator find(const T &key) const;

    bool contains(const T &key) const;

    Iterator upperBound(const T &key);

    ConstIterator upperBound(const T &key) const;

    Iterator lowerBound(const T &key);

    ConstIterator lowerBound(const T &key) const;

    Iterator erase(Iterator);

    Iterator erase(ConstIterator);

    Iterator erase(Iterator, Iterator);

    Iterator erase(ConstIterator, ConstIterator);

    unsigned int erase(const T &key);

    Pair<Iterator, bool> insert(const Pair<T, U> &pair);

    Pair<Iterator, bool> insert(Pair<T, U> &&pair);

    void insert(Iterator, Iterator);

    Pair<Iterator, bool> insertOrAssign(const T &key, U &&value);

    Pair<Iterator, bool> insertOrAssign(T &&key, U &&value);

    U &operator[](const T &key);

    U &operator[](T &&key);
};

template<typename T, typename U>
unsigned int Map<T, U>::distance(Iterator first, Iterator last) {
    unsigned int sum = 0;
    for (Iterator it = first; it != last; ++it, ++sum);
    return sum;
}

template<typename T, typename U>
Map<T, U> &Map<T, U>::operator=(const Map<T, U> &ori) {
    if (&ori == this) {
        return (*this);
    }
    clear();
    root = ori.root;
    return (*this);
}

template<typename T, typename U>
Map<T, U>::~Map() {
    clear();
}

template<typename T, typename U>
void Map<T, U>::clear() {
    Iterator it = begin();
    Iterator iter = it;
    while (it != end()) {
        delete ((Node *) (iter));
        it++;
        iter = it;
    }
    root = nullptr;
}

template<typename T, typename U>
typename Map<T, U>::Iterator Map<T, U>::begin() {
    return Iterator(Node::treeMin(root));
}

template<typename T, typename U>
typename Map<T, U>::ConstIterator Map<T, U>::cBegin() {
    return ConstIterator(Node::treeMin(root));
}

template<typename T, typename U>
typename Map<T, U>::Iterator Map<T, U>::end() {
    return Iterator(nullptr);
}

template<typename T, typename U>
typename Map<T, U>::ConstIterator Map<T, U>::cEnd() {
    return ConstIterator(nullptr);
}

template<typename T, typename U>
T &Map<T, U>::at(const T &key) {
    Iterator it(Node::treeFind(root, key));
    if (it->getKey() == key) {
        return *it;
    }
    throw std::runtime_error("OUT_OF_RANGE");
}

template<typename T, typename U>
const T &Map<T, U>::at(const T &key) const {
    ConstIterator it(Node::treeFind(root, key));
    if (it->getKey() == key) {
        return *it;
    }
    throw std::runtime_error("OUT_OF_RANGE");
}

template<typename T, typename U>
unsigned int Map<T, U>::size() {
    return distance(begin(), end());
}

template<typename T, typename U>
bool Map<T, U>::empty() {
    return begin() == end();
}

template<typename T, typename U>
unsigned int Map<T, U>::count(const T &key) {
    return (contains(key) ? 1 : 0);
}

template<typename T, typename U>
typename Map<T, U>::Iterator Map<T, U>::find(const T &key) {
    Iterator it(Node::treeFind(root, key));
    return (it->getKey() == key ? it : end());
}

template<typename T, typename U>
typename Map<T, U>::ConstIterator Map<T, U>::find(const T &key) const {
    ConstIterator it(Node::treeFind(root, key));
    return (it->getKey() == key ? it : cEnd());
}

template<typename T, typename U>
bool Map<T, U>::contains(const T &key) const {
    ConstIterator it(Node::treeFind(root, key));
    return it->getKey() == key;
}

template<typename T, typename U>
typename Map<T, U>::Iterator Map<T, U>::upperBound(const T &key) {
    Iterator it(Node::treeFind(root, key));
    return (it->getKey() > key ? it : ++it);
}

template<typename T, typename U>
typename Map<T, U>::ConstIterator Map<T, U>::upperBound(const T &key) const {
    ConstIterator it(Node::treeFind(root, key));
    return (it->getKey() > key ? it : ++it);
}

template<typename T, typename U>
typename Map<T, U>::Iterator Map<T, U>::lowerBound(const T &key) {
    Iterator it(Node::treeFind(root, key));
    return (it->getKey() > key ? --it : it);
}

template<typename T, typename U>
typename Map<T, U>::ConstIterator Map<T, U>::lowerBound(const T &key) const {
    ConstIterator it(Node::treeFind(root, key));
    return (it->getKey() > key ? --it : it);
}

template<typename T, typename U>
typename Map<T, U>::Iterator Map<T, U>::erase(Map::Iterator) {
    return Map::Iterator(nullptr);
}

template<typename T, typename U>
typename Map<T, U>::Iterator Map<T, U>::erase(Map::ConstIterator) {
    return Map::Iterator(nullptr);
}

template<typename T, typename U>
typename Map<T, U>::Iterator Map<T, U>::erase(Map::Iterator, Map::Iterator) {
    return Map::Iterator(nullptr);
}

template<typename T, typename U>
typename Map<T, U>::Iterator Map<T, U>::erase(Map::ConstIterator, Map::ConstIterator) {
    return Map::Iterator(nullptr);
}

template<typename T, typename U>
unsigned int Map<T, U>::erase(const T &key) {
    return 0;
}

template<typename T, typename U>
Pair<typename Map<T, U>::Iterator, bool> Map<T, U>::insert(const Pair<T, U> &pair) {


    return Pair<Iterator, bool>(Map::Iterator(), false);
}

template<typename T, typename U>
Pair<typename Map<T, U>::Iterator, bool> Map<T, U>::insert(Pair<T, U> &&pair) {
    return Pair<Iterator, bool>(Map::Iterator(), false);
}

template<typename T, typename U>
void Map<T, U>::insert(Map::Iterator, Map::Iterator) {

}

template<typename T, typename U>
Pair<typename Map<T, U>::Iterator, bool> Map<T, U>::insertOrAssign(const T &key, U &&value) {
    return Pair<Iterator, bool>(Map::Iterator(), false);
}

template<typename T, typename U>
Pair<typename Map<T, U>::Iterator, bool> Map<T, U>::insertOrAssign(T &&key, U &&value) {
    return Pair<Iterator, bool>(Map::Iterator(), false);
}

template<typename T, typename U>
U &Map<T, U>::operator[](const T &key) {
    return ;
}

template<typename T, typename U>
U &Map<T, U>::operator[](T &&key) {
    return ;
}


#endif //DATA_STRUCTURES_MAP_H