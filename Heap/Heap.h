//
// Created by 卿无言 on 2022/12/8.
//

#ifndef DATA_STRUCTURES_HEAP_H
#define DATA_STRUCTURES_HEAP_H

const int Capacity=1024;
template <typename T>
class heap {
public:
    heap();
    bool empty( ) const;
    T top();
    void add(const T& item);
    void removeTop();
    void deleteAllValues();
private:
    T myArray[Capacity];
    unsigned int mySize;
};

template<typename T>
bool heap<T>::empty() const {
    return mySize == 0;
}

template<typename T>
T heap<T>::top() {
    return myArray[0];
}

template<typename T>
void heap<T>::add(const T &item) {
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
void heap<T>::removeTop() {

}

template<typename T>
void heap<T>::deleteAllValues() {
    mySize = 0;
}

template<typename T>
heap<T>::heap() {
    mySize = 0;
    myArray[0] = 0;
}

#endif //DATA_STRUCTURES_HEAP_H
