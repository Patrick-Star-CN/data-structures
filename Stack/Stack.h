#ifndef DATA_STRUCTURES_STACK_H
#define DATA_STRUCTURES_STACK_H
#include <cassert>
#include <iostream>
template<typename T>
class Stack {
public:
    Stack();

    explicit Stack(unsigned);

    Stack(const Stack<T> &);

    void operator=(const Stack<T> &);

    void pop();

    bool empty();

    T top();

    void push(const T &);

    void display(std::ostream &);

private:
    T *data;
    unsigned size;
    unsigned capacity;
};
#endif //DATA_STRUCTURES_STACK_H

template<typename T>
Stack<T>::Stack():data(nullptr), size(0), capacity(10) {
    data = new T [capacity];
}

template<typename T>
Stack<T>::Stack(unsigned int capacity):capacity(capacity), size(0) {
    data = new T [capacity];
}

template<typename T>
Stack<T>::Stack(const Stack<T> &right) {
    capacity = right.capacity;
    size = right.size;
    data = new T [capacity];
    for (int i = 0; i < size; i ++) {
        data[i] = right.data[i];
    }
}

template<typename T>
void Stack<T>::operator=(const Stack<T> &right) {
    capacity = right.capacity;
    size = right.size;
    data = new T [capacity];
    for (int i = 0; i < size; i ++) {
        data[i] = right.data[i];
    }
}

template<typename T>
void Stack<T>::pop() {
    if (!size) {
        throw "EMPTY_ERROR";
    }
    size --;
}

template<typename T>
bool Stack<T>::empty() {
    return size == 0;
}

template<typename T>
T Stack<T>::top() {
    if (empty()) {
        throw "EMPTY_ERROR";
    }
    return data[size - 1];
}

template<typename T>
void Stack<T>::push(const T &data_) {
    if (size >= capacity * 0.75) {
        T *newData = new T [capacity * 2];
        for (int i = 0; i < size; i ++) {
            newData[i] = data[i];
        }
        capacity *= 2;
        delete [] data;
        data = newData;
    }

    data[size] = data_;
    size ++;
}

template<typename T>
void Stack<T>::display(std::ostream &out) {
    for (int i = 0; i < size; i ++) {
        out << data[i] << " ";
    }
    out << std::endl;
}


