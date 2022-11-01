#ifndef DATA_STRUCTURES_STACK_H
#define DATA_STRUCTURES_STACK_H

#include <cassert>
#include <iostream>

template<typename T>
class Stack {
public:
    // 构造一个空的栈
    Stack();

    // 构造一个指定缓冲区长度的栈
    explicit Stack(unsigned);

    // 拷贝构造
    Stack(const Stack<T> &);

    // 赋值运算符重载
    Stack &operator=(const Stack<T> &);

    // 赋值运算符重载
    Stack &operator=(Stack<T> &&) noexcept ;

    // 判断栈是否为空
    bool empty();

    // 返回栈顶元素
    T top();

    // 往栈顶压入一个元素
    void push(const T &);

    // 往栈顶压入一个元素
    void push(T &&);

    // 从栈顶弹出一个元素
    void pop();

    void swap(Stack<T> &s);

    template <typename... Args>
    void emplace(Args &&...);

private:
    T *data;
    unsigned size;
    unsigned capacity;
};

#endif //DATA_STRUCTURES_STACK_H

template<typename T>
Stack<T>::Stack():data(nullptr), size(0), capacity(10) {
    data = new T[capacity];
    assert(data != nullptr);
}

template<typename T>
Stack<T>::Stack(unsigned int capacity):capacity(capacity), size(0) {
    data = new T[capacity];
    assert(data != nullptr);
}

template<typename T>
Stack<T>::Stack(const Stack<T> &right) {
    capacity = right.capacity;
    size = right.size;
    data = new T[capacity];
    assert(data != nullptr);
    for (int i = 0; i < size; i++) {
        data[i] = right.data[i];
    }
}

template<typename T>
Stack<T> &Stack<T>::operator=(const Stack<T> &right) {
    capacity = right.capacity;
    size = right.size;
    delete[] data;
    data = new T[capacity];
    assert(data != nullptr);
    for (int i = 0; i < size; i++) {
        data[i] = right.data[i];
    }
    return *this;
}

template<typename T>
void Stack<T>::pop() {
    if (!size) {
        throw std::runtime_error("EMPTY_ERROR");
    }
    size--;
}

template<typename T>
bool Stack<T>::empty() {
    return size == 0;
}

template<typename T>
T Stack<T>::top() {
    if (empty()) {
        throw std::runtime_error("EMPTY_ERROR");
    }
    return data[size - 1];
}

template<typename T>
void Stack<T>::push(const T &v) {
    if (size >= capacity * 0.75) {
        T *newData = new T[capacity * 2];
        assert(newData != nullptr);
        for (int i = 0; i < size; i++) {
            newData[i] = data[i];
        }
        capacity *= 2;
        delete[] data;
        data = newData;
    }

    data[size] = v;
    size++;
}

template<typename T>
void Stack<T>::push(T &&v) {
    if (size >= capacity * 0.75) {
        T *newData = new T[capacity * 2];
        assert(newData != nullptr);
        for (int i = 0; i < size; i++) {
            newData[i] = data[i];
        }
        capacity *= 2;
        delete[] data;
        data = newData;
    }

    data[size] = v;
    size++;
}

template<typename T>
Stack<T> &Stack<T>::operator=(Stack<T> &&right) noexcept {
    capacity = right.capacity;
    size = right.size;
    delete[] data;
    data = new T[capacity];
    assert(data != nullptr);
    for (int i = 0; i < size; i++) {
        data[i] = right.data[i];
    }
    return *this;
}

template<typename T>
void Stack<T>::swap(Stack<T> &s) {

}

template<typename T>
template<typename... Args>
void Stack<T>::emplace(Args &&... args) {

}

