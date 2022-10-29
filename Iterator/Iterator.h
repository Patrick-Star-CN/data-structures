#ifndef DATA_STRUCTURES_ITERATOR_H
#define DATA_STRUCTURES_ITERATOR_H

template<typename T>
class BaseIterator {
public:
    virtual constexpr BaseIterator<T> operator++(int) = 0;

protected:
    T *now;
};

template<typename T>
class InputIterator : public BaseIterator<T> {
public:
    template<typename U>
    friend U operator*(const InputIterator<U> &);
};

template<typename T>
class ForwardIterator : public BaseIterator<T> {
public:
    template<typename U>
    friend U &operator*(const InputIterator<U> &);
};

template<typename T>
class BidirectionalIterator : public ForwardIterator<T> {
public:
    virtual constexpr BaseIterator<T> operator--(int) = 0;
};

template<typename T>
class RandomAccessIterator : public BidirectionalIterator<T> {
public:
    virtual constexpr BaseIterator<T> operator+(int) = 0;

    virtual constexpr BaseIterator<T> operator-(int) = 0;
};

#endif //DATA_STRUCTURES_ITERATOR_H

template<typename U>
U operator*(const InputIterator<U> &right) {
    return *(right.now);
}
