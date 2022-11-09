#ifndef DATA_STRUCTURES_MAP_H
#define DATA_STRUCTURES_MAP_H

template<typename T, typename U>
class Pair {
private:
    T key;
    U value;

public:
    explicit Pair(T k, U v) : key(k), value(v) {}

    Pair(const Pair<T, U> &right) : key(right.key), value(right.value) {}

    T getKey() const;

    void setKey(T);

    U getValue() const;

    void setValue(U);
};

template<typename T, typename U>
T Pair<T, U>::getKey() const {
    return key;
}

template<typename T, typename U>
void Pair<T, U>::setKey(T k) {
    Pair::key = k;
}

template<typename T, typename U>
U Pair<T, U>::getValue() const {
    return value;
}

template<typename T, typename U>
void Pair<T, U>::setValue(U v) {
    Pair::value = v;
}

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


        Node(const Node &right) : left(right.left), right(right.right), data(right.data) {}

        Node *getLeft() const;

        void setLeft(Node *);

        bool hasLeft() const;

        Node *getRight() const;

        void setRight(Node *);

        bool hasRight() const;

        Node *getFather() const;

        void setFather(Node *);

        bool hasFather() const;

        const Pair<T, U> &getData() const;

        void setData(const Pair<T, U> &);
    };

    class Iterator {
    private:
        Node *ptr;

    public:
        explicit Iterator(Node *ptr) : ptr(ptr) {}

        explicit Iterator(Pair<T, U> data) : ptr(new Node(data)) {}

        Iterator(const Iterator &right) : ptr(right.ptr) {}

        Pair<T, U> &operator*();

        const Iterator operator++(int);

        Iterator &operator++();

        const Iterator operator--(int);

        Iterator &operator--();

        bool operator==(const Iterator &);

        bool operator!=(const Iterator &);

        bool operator<(const Iterator &);

        bool operator<=(const Iterator &);

        bool operator>(const Iterator &);

        bool operator>=(const Iterator &);
    };

    class ConstIterator {
    private:
        const Node *ptr;

    public:
        explicit ConstIterator(Node *ptr) : ptr(ptr) {}

        explicit ConstIterator(Pair<T, U> data) : ptr(new Node(data)) {}

        ConstIterator(const ConstIterator &right) : ptr(right.ptr) {}

        Pair<T, U> &operator*();

        const ConstIterator operator++(int);

        ConstIterator &operator++();

        const ConstIterator operator--(int);

        ConstIterator &operator--();

        bool operator==(const ConstIterator &);

        bool operator!=(const ConstIterator &);

        bool operator<(const ConstIterator &);

        bool operator<=(const ConstIterator &);

        bool operator>(const ConstIterator &);

        bool operator>=(const ConstIterator &);
    };

    unsigned int distance(Iterator, Iterator);

    Node *root;

public:
    Map() : root(nullptr) {}

    Map(const Map<T, U> &right) : root(right.root) {}

    ~Map();

    Iterator begin();

    ConstIterator cBegin();

    Iterator end();

    ConstIterator cEnd();

    Pair<T, U> &at(const T &);

    const Pair<T, U> &at(const T &) const;

    unsigned int size();


};

template<typename T, typename U>
Pair<T, U> &Map<T, U>::ConstIterator::operator*() {
    return ptr->getData();
}

template<typename T, typename U>
const typename Map<T, U>::ConstIterator Map<T, U>::ConstIterator::operator++(int) {
    Map<T, U>::ConstIterator tmp(*this);
    ++(*this);
    return tmp;
}

template<typename T, typename U>
typename Map<T, U>::ConstIterator &Map<T, U>::ConstIterator::operator++() {
    if (ptr->hasRight()) {
        ptr = ptr->getRight();
        while (ptr->hasLeft()) {
            ptr = ptr->getLeft();
        }
    } else if (ptr->hasFather() && ptr->getFather()->hasLeft() == this) {
        ptr = ptr->getFather();
    }
    return (*this);
}

template<typename T, typename U>
const typename Map<T, U>::ConstIterator Map<T, U>::ConstIterator::operator--(int) {
    Map<T, U>::ConstIterator tmp(*this);
    --(*this);
    return tmp;
}

template<typename T, typename U>
typename Map<T, U>::ConstIterator &Map<T, U>::ConstIterator::operator--() {
    if (ptr->hasLeft()) {
        ptr = ptr->getLeft();
        while (ptr->hasRight()) {
            ptr = ptr->getRight();
        }
    } else if (ptr->hasFather() && ptr->getFather()->hasRight() == this) {
        ptr = ptr->getFather();
    }
    return (*this);
}

template<typename T, typename U>
bool Map<T, U>::ConstIterator::operator==(const Map::ConstIterator &right) {
    return ptr->getData().getKey() == right.ptr->getData().getKey();
}

template<typename T, typename U>
bool Map<T, U>::ConstIterator::operator!=(const Map::ConstIterator &right) {
    return ptr->getData().getKey() != right.ptr->getData().getKey();
}

template<typename T, typename U>
bool Map<T, U>::ConstIterator::operator<(const Map::ConstIterator &right) {
    return ptr->getData().getKey() < right.ptr->getData().getKey();
}

template<typename T, typename U>
bool Map<T, U>::ConstIterator::operator<=(const Map::ConstIterator &right) {
    return ptr->getData().getKey() <= right.ptr->getData().getKey();
}

template<typename T, typename U>
bool Map<T, U>::ConstIterator::operator>(const Map::ConstIterator &right) {
    return ptr->getData().getKey() > right.ptr->getData().getKey();
}

template<typename T, typename U>
bool Map<T, U>::ConstIterator::operator>=(const Map::ConstIterator &right) {
    return ptr->getData().getKey() >= right.ptr->getData().getKey();
}

template<typename T, typename U>
Pair<T, U> &Map<T, U>::Iterator::operator*() {
    return ptr->getData();
}

template<typename T, typename U>
const typename Map<T, U>::Iterator Map<T, U>::Iterator::operator++(int) {
    Map<T, U>::Iterator tmp(*this);
    ++(*this);
    return tmp;
}

template<typename T, typename U>
typename Map<T, U>::Iterator &Map<T, U>::Iterator::operator++() {
    if (ptr->hasRight()) {
        ptr = ptr->getRight();
        while (ptr->hasLeft()) {
            ptr = ptr->getLeft();
        }
    } else if (ptr->hasFather() && ptr->getFather()->hasLeft() == this) {
        ptr = ptr->getFather();
    }
    return (*this);
}

template<typename T, typename U>
const typename Map<T, U>::Iterator Map<T, U>::Iterator::operator--(int) {
    Map<T, U>::Iterator tmp(*this);
    --(*this);
    return tmp;
}

template<typename T, typename U>
typename Map<T, U>::Iterator &Map<T, U>::Iterator::operator--() {
    if (ptr->hasLeft()) {
        ptr = ptr->getLeft();
        while (ptr->hasRight()) {
            ptr = ptr->getRight();
        }
    } else if (ptr->hasFather() && ptr->getFather()->hasRight() == this) {
        ptr = ptr->getFather();
    }
    return (*this);
}

template<typename T, typename U>
bool Map<T, U>::Iterator::operator==(const Map::Iterator &right) {
    return ptr->getData().getKey() == right.ptr->getData().getKey();
}

template<typename T, typename U>
bool Map<T, U>::Iterator::operator!=(const Map::Iterator &right) {
    return ptr->getData().getKey() != right.ptr->getData().getKey();
}

template<typename T, typename U>
bool Map<T, U>::Iterator::operator<(const Map::Iterator &right) {
    return ptr->getData().getKey() < right.ptr->getData().getKey();
}

template<typename T, typename U>
bool Map<T, U>::Iterator::operator<=(const Map::Iterator &right) {
    return ptr->getData().getKey() <= right.ptr->getData().getKey();
}

template<typename T, typename U>
bool Map<T, U>::Iterator::operator>(const Map::Iterator &right) {
    return ptr->getData().getKey() > right.ptr->getData().getKey();
}

template<typename T, typename U>
bool Map<T, U>::Iterator::operator>=(const Map::Iterator &right) {
    return ptr->getData().getKey() >= right.ptr->getData().getKey();
}

template<typename T, typename U>
typename Map<T, U>::Node *Map<T, U>::Node::getLeft() const {
    return left;
}

template<typename T, typename U>
void Map<T, U>::Node::setLeft(Map::Node *l) {
    Node::left = l;
}

template<typename T, typename U>
typename Map<T, U>::Node *Map<T, U>::Node::getRight() const {
    return right;
}

template<typename T, typename U>
void Map<T, U>::Node::setRight(Map::Node *r) {
    Node::right = r;
}

template<typename T, typename U>
const Pair<T, U> &Map<T, U>::Node::getData() const {
    return data;
}

template<typename T, typename U>
void Map<T, U>::Node::setData(const Pair<T, U> &d) {
    Node::data = d;
}

template<typename T, typename U>
bool Map<T, U>::Node::hasLeft() const {
    return left != nullptr;
}

template<typename T, typename U>
bool Map<T, U>::Node::hasRight() const {
    return right != nullptr;
}

template<typename T, typename U>
typename Map<T, U>::Node *Map<T, U>::Node::getFather() const {
    return father;
}

template<typename T, typename U>
void Map<T, U>::Node::setFather(Map::Node *f) {
    Node::father = f;
}

template<typename T, typename U>
bool Map<T, U>::Node::hasFather() const {
    return father != nullptr;
}

#endif //DATA_STRUCTURES_MAP_H
