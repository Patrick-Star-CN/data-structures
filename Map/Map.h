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
        Node *father;
        Pair<T, U> data;
    public:
        explicit Node(Pair<T, U> data) : data(data), left(nullptr), right(nullptr), father(nullptr) {}

        explicit Node(Pair<T, U> data, Node *father) : data(data), left(nullptr), right(nullptr), father(father) {}

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

        Node *getFather() const {
            return father;
        }

        void setFather(Node *f) {
            Node::father = f;
        }

        bool hasFather() const {
            return father != nullptr;
        }

        int treeIsLeftChild(Node *x) {
            if (!x->hasFather()) {
                return -1;
            }
            return x == x->getFather()->getLeft();
        }

        Node *treeMin(Node *root) {
            while (root->hasLeft()) {
                root = root->getLeft();
            }
            return root;
        }

        Node *treeMax(Node *root) {
            while (root->hasRight()) {
                root = root->getRight();
            }
            return root;
        }

        Node *treeNext(Node *x) {
            if (x->hasRight()) {
                return treeMin(x->getRight());
            }
            while (treeIsLeftChild(x) == 0) {
                x = x->getFather();
            }
            if (treeIsLeftChild(x) == -1) {
                return nullptr;
            }
            return x->getFather();
        }

        Node *treePrev(Node *x) {
            if (x->hasLeft()) {
                return treeMax(x->getLeft());
            }
            while (treeIsLeftChild(x) == 1) {
                x = x->getFather();
            }
            if (treeIsLeftChild(x) == -1) {
                return nullptr;
            }
            return x->getFather();
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
    return ConstIterator(Node::treeMin(root));;
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


#endif //DATA_STRUCTURES_MAP_H