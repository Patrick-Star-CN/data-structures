//
// Created by 卿无言 on 2022/12/8.
//

#ifndef DATA_STRUCTURES_HEAP_H
#define DATA_STRUCTURES_HEAP_H

const int Capacity=1024;
template <typename T>
class Heap {
public:
    Heap();
    bool empty() const;
    T top();
    void add(const T& item);
    void removeTop();
    void deleteAllValues();
private:
    T myArray[Capacity];
    unsigned int mySize;
};

template<typename T>
bool Heap<T>::empty() const {
    return mySize == 0;
}

template<typename T>
T Heap<T>::top() {
    return myArray[1];
}

template<typename T>
void Heap<T>::add(const T &item) {
    ++mySize;
    myArray[mySize] = item;
    int r = mySize / 2;
    int c = mySize;
    while (r > 0) {
        if (myArray[r] <= myArray[c]) {
            break;
        }
        T tmp = myArray[r];
        myArray[r] = myArray[c];
        myArray[c] = tmp;
        c = r;
        r /= 2;
    }
}

template<typename T>
void Heap<T>::removeTop() {
    myArray[1] = myArray[mySize];
    --mySize;
    int c = 2;
    int r = 1;
    while (c <= mySize) {
        if (c < mySize && myArray[c] > myArray[c + 1]) {
            ++c;
        }
        if (myArray[r] > myArray[c]) {
            T tmp = myArray[r];
            myArray[r] = myArray[c];
            myArray[c] = tmp;
            r = c;
            c *= 2;
        } else {
            break;
        }
    }
}

template<typename T>
void Heap<T>::deleteAllValues() {
    mySize = 0;
}

template<typename T>
Heap<T>::Heap() {
    mySize = 0;
    myArray[0] = 0;
}

#endif //DATA_STRUCTURES_HEAP_H
