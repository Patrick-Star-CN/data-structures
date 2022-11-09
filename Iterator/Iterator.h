#ifndef DATA_STRUCTURES_ITERATOR_H
#define DATA_STRUCTURES_ITERATOR_H

template<typename T>
class BaseIterator {
public:
    virtual constexpr BaseIterator<T> operator++(int) = 0;

    virtual BaseIterator<T> &operator++() = 0;

    virtual T &operator*() = 0;
};

template<typename T>
class BidirectionalIterator : public BaseIterator<T> {
public:
    virtual constexpr BaseIterator<T> operator--(int) = 0;

    virtual BaseIterator<T> &operator--() = 0;
};

template<typename T>
class RandomAccessIterator : public BidirectionalIterator<T> {
public:
    virtual constexpr BaseIterator<T> operator+(int) = 0;

    virtual BaseIterator<T> &operator+=(int) = 0;

    virtual constexpr BaseIterator<T> operator-(int) = 0;

    virtual BaseIterator<T> &operator-=(int) = 0;
};

#endif //DATA_STRUCTURES_ITERATOR_H
