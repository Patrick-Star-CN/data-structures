#ifndef DATA_STRUCTURES_MAP_H
#define DATA_STRUCTURES_MAP_H

template<typename T, typename U>
class Pair {
private:
    T key;
    U value;

public:
    explicit Pair(T k, U v): key(k), value(v) {}

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
    };

    class Iterator {
    private:
        Node *ptr;

    };

    Node *root;

public:

};

#endif //DATA_STRUCTURES_MAP_H
