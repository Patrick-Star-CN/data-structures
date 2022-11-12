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
    Stack &operator=(Stack<T> &&) noexcept;

    // 判断栈是否为空
    bool empty();

    // 返回栈顶元素
    T &top();

    // 往栈顶压入一个元素
    void push(const T &);

    // 往栈顶压入一个元素
    void push(T &&);

    // 从栈顶弹出一个元素
    void pop();

    void swap(Stack<T> &);

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
    data = new(std::nothrow) T[capacity];
    assert(data != nullptr);
}

template<typename T>
Stack<T>::Stack(const Stack<T> &ori) {
    capacity = ori.capacity;
    size = ori.size;
    data = new(std::nothrow) T[capacity];
    assert(data != nullptr);
    for (int i = 0; i < size; i++) {
        data[i] = ori.data[i];
    }
}

template<typename T>
Stack<T> &Stack<T>::operator=(const Stack<T> &ori) {
    if (this == &ori) {
        return (*this);
    }
    capacity = ori.capacity;
    size = ori.size;
    delete[] data;
    data = new(std::nothrow) T[capacity];
    assert(data != nullptr);
    for (int i = 0; i < size; i++) {
        data[i] = ori.data[i];
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
T &Stack<T>::top() {
    if (empty()) {
        throw std::runtime_error("EMPTY_ERROR");
    }
    return data[size - 1];
}

template<typename T>
void Stack<T>::push(const T &v) {
    if (size >= capacity * 0.75) {
        T *newData = new(std::nothrow) T[capacity * 2];
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
        T *newData = new(std::nothrow) T[capacity * 2];
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
Stack<T> &Stack<T>::operator=(Stack<T> &&rhs) noexcept {
    capacity = rhs.capacity;
    size = rhs.size;
    delete[] data;
    data = new(std::nothrow) T[capacity];
    assert(data != nullptr);
    for (int i = 0; i < size; i++) {
        data[i] = rhs.data[i];
    }
    return *this;
}

template<typename T>
void Stack<T>::swap(Stack<T> &other) {
    Stack<T> tmp1(capacity);
    Stack<T> tmp2(other.capacity);
    while (!empty()) {
        tmp1.push(top());
        pop();
    }
    while (!other.empty()) {
        tmp2.push(other.top());
        other.pop();
    }
    delete[] data;
    delete[] other.data;
    data = new(std::nothrow) T[tmp2.capacity];
    assert(data != nullptr);
    other.data = new(std::nothrow) T[tmp1.capacity];
    assert(other.data != nullptr);
    while (!tmp2.empty()) {
        push(tmp2.top());
        tmp2.pop();
    }
    while (!tmp1.empty()) {
        other.push(tmp1.top());
        tmp1.pop();
    }
}