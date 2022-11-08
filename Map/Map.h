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

    void setKey(T key);

    U getValue() const;

    void setValue(U value);
};

template<typename T, typename U>
T Pair<T, U>::getKey() const {
    return key;
}

template<typename T, typename U>
void Pair<T, U>::setKey(T key) {
    Pair::key = key;
}

template<typename T, typename U>
U Pair<T, U>::getValue() const {
    return value;
}

template<typename T, typename U>
void Pair<T, U>::setValue(U value) {
    Pair::value = value;
}

template<typename T, typename U>
class Map {
private:
    class Node {
    private:
        Node *left;
        Node *right;
        Pair<T, U> data;
    public:
        explicit Node(Pair<T, U> data) : data(data), left(nullptr), right(nullptr) {}

        Node(const Node &right) : left(right.left), right(right.right), data(right.data) {}

        Node *getLeft() const;

        void setLeft(Node *left);

        bool hasLeft() const;

        Node *getRight() const;

        void setRight(Node *right);

        bool hasRight() const;

        const Pair<T, U> &getData() const;

        void setData(const Pair<T, U> &data);
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

    Node *root;

public:

};

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
void Map<T, U>::Node::setLeft(Map::Node *left) {
    Node::left = left;
}

template<typename T, typename U>
typename Map<T, U>::Node *Map<T, U>::Node::getRight() const {
    return right;
}

template<typename T, typename U>
void Map<T, U>::Node::setRight(Map::Node *right) {
    Node::right = right;
}

template<typename T, typename U>
const Pair<T, U> &Map<T, U>::Node::getData() const {
    return data;
}

template<typename T, typename U>
void Map<T, U>::Node::setData(const Pair<T, U> &data) {
    Node::data = data;
}

template<typename T, typename U>
bool Map<T, U>::Node::hasLeft() const {
    return left != nullptr;
}

template<typename T, typename U>
bool Map<T, U>::Node::hasRight() const {
    return right != nullptr;
}

#endif //DATA_STRUCTURES_MAP_H
