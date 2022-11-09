#ifndef DATA_STRUCTURES_DEQUE_H
#define DATA_STRUCTURES_DEQUE_H

#include <iostream>
#include <cassert>

template<typename T>
class Deque {
private:


    T *data;
    unsigned int capacity;
    unsigned int size;
    unsigned int first;
    unsigned int last;

    void zoom();

public:
    class Iterator {
    private:
        T *first;
        T *ptr;
        unsigned int capacity;

    public:
        Iterator() : ptr(nullptr), first(nullptr), capacity(0) {}

        explicit Iterator(T *p, T *data, unsigned int capacity) : ptr(p), first(data), capacity(capacity) {}

        Iterator(const Iterator &right) : ptr(right.ptr) {}

        const Iterator operator++(int);

        const Iterator operator--(int);

        Iterator &operator++();

        Iterator &operator--();

        Iterator operator+(int);

        Iterator operator-(int);

        Iterator &operator+=(int);

        Iterator &operator-=(int);

        bool operator==(const Iterator &) const;

        bool operator!=(const Iterator &) const;

        T &operator*();
    };

    Deque() : data(nullptr), first(0), last(0), capacity(0), size(0) {}

    explicit Deque(unsigned int capacity) : first(0), last(0), capacity(capacity), size(0) {
        data = new(std::nothrow) T[capacity];
        assert(data != nullptr);
    }

    ~Deque() {
        delete[] data;
        data = nullptr;
    }

    Iterator begin();

    Iterator end();

    void pushBack(const T &);

    void pushBack(T &&);

    void pushFront(const T &);

    void pushFront(T &&);

    void popBack();

    void popFront();

    T &back();

    T &front();

    bool empty();
};

template<typename T>
typename Deque<T>::Iterator Deque<T>::begin() {
    return Iterator(data + first, data, capacity);
}

template<typename T>
typename Deque<T>::Iterator Deque<T>::end() {
    return Iterator(data + (last + 1) % capacity, data, capacity);
}

template<typename T>
void Deque<T>::pushBack(const T &v) {
    if (empty()) {
        data[0] = v;
        size = 1;
        first = 0;
        last = 0;
        return;
    }
    if (size == capacity - 1) {
        Deque<T>::zoom();
    }
    ++last;
    if (last == first + capacity) {
        last = 0;
    }
    data[last] = v;
    ++size;
}

template<typename T>
void Deque<T>::pushBack(T &&v) {
    if (empty()) {
        data[0] = v;
        size = 1;
        first = 0;
        last = 0;
        return;
    }
    if (size == capacity - 1) {
        Deque<T>::zoom();
    }
    ++last;
    if (last == capacity) {
        last = 0;
    }
    data[last] = v;
    ++size;
}

template<typename T>
void Deque<T>::pushFront(const T &v) {
    if (empty()) {
        data[0] = v;
        size = 1;
        first = 0;
        last = 0;
        return;
    }
    if (size == capacity - 1) {
        Deque<T>::zoom();
    }
    if (first == 0) {
        first = capacity;
    }
    --first;
    data[first] = v;
    ++size;
}

template<typename T>
void Deque<T>::pushFront(T &&v) {
    if (empty()) {
        data[0] = v;
        size = 1;
        first = 0;
        last = 0;
        return;
    }
    if (size == capacity - 1) {
        Deque<T>::zoom();
    }
    if (first == 0) {
        first = capacity;
    }
    --first;
    data[first] = v;
    ++size;
}

template<typename T>
void Deque<T>::popBack() {
    --last;
    if (last == -1) {
        last = capacity - 1;
    }
    --size;
}

template<typename T>
void Deque<T>::popFront() {
    ++first;
    if (first == capacity) {
        first = 0;
    }
    --size;
}

template<typename T>
T &Deque<T>::back() {
    return data[first];
}

template<typename T>
T &Deque<T>::front() {
    return data[last];
}

template<typename T>
bool Deque<T>::empty() {
    return size == 0;
}

template<typename T>
void Deque<T>::zoom() {
    T *newData = new T[capacity * 2];
    int i = 0;
    for (Iterator it = begin(); it != end(); it++, i++) {
        newData[i] = *it;
    }
    delete[] data;
    capacity *= 2;
    data = newData;
    first = 0;
    last = size - 1;
}

template<typename T>
const typename Deque<T>::Iterator Deque<T>::Iterator::operator++(int) {
    Deque::Iterator tmp(*this);
    ++(*this);
    return tmp;
}

template<typename T>
const typename Deque<T>::Iterator Deque<T>::Iterator::operator--(int) {
    Deque::Iterator tmp(*this);
    --(*this);
    return tmp;
}

template<typename T>
typename Deque<T>::Iterator &Deque<T>::Iterator::operator++() {
    if (ptr - first == capacity - 1) {
        ptr = first;
        return (*this);
    }
    ++ptr;
    return (*this);
}

template<typename T>
typename Deque<T>::Iterator &Deque<T>::Iterator::operator--() {
    if (ptr == first) {
        ptr = first + capacity;
        return (*this);
    }
    --ptr;
    return (*this);
}

template<typename T>
typename Deque<T>::Iterator Deque<T>::Iterator::operator+(int n) {
    Deque::Iterator tmp(*this);
    tmp += n;
    return tmp;
}

template<typename T>
typename Deque<T>::Iterator Deque<T>::Iterator::operator-(int n) {
    Deque::Iterator tmp(*this);
    tmp -= n;
    return tmp;
}

template<typename T>
typename Deque<T>::Iterator &Deque<T>::Iterator::operator+=(int n) {
    if (n == 0) {
        return (*this);
    }
    n += ptr - first;
    if (n > 0) {
        ptr = first + n % capacity;
    } else {
        int z = capacity - 1 - n;
        ptr = first + (capacity - 1 - z % capacity);
    }
    return (*this);
}

template<typename T>
typename Deque<T>::Iterator &Deque<T>::Iterator::operator-=(int n) {
    return (*this) += -n;
}

template<typename T>
T &Deque<T>::Iterator::operator*() {
    return *(ptr);
}

template<typename T>
bool Deque<T>::Iterator::operator==(const Deque::Iterator &rhs) const {
    return ptr == rhs.ptr;
}

template<typename T>
bool Deque<T>::Iterator::operator!=(const Deque::Iterator &rhs) const {
    return !(rhs == *this);
}

#endif //DATA_STRUCTURES_DEQUE_H
