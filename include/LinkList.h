#ifndef DATA_STRUCTURES_ARRAYLIST_H
#define DATA_STRUCTURES_ARRAYLIST_H

#include "ListNode.h"
#include <iostream>

template <typename T>
class LinkList {
public:
    LinkList();

    LinkList(T);

    virtual ~LinkList();

    ListNode<T> *getHead() const;

    int getLength() const;

    void insert(T);

    void display(std::ostream&);

    void erase(T data);

    bool empty();

private:
    ListNode<T> *head;

    int length;

    void setLength(int length);

    void setHead(ListNode<T>*);
};


#endif //DATA_STRUCTURES_ARRAYLIST_H

template <typename T>
LinkList<T>::LinkList(T data) {
    this->length = 1;
    auto head = new ListNode<T>(data);
    this->head = head;
}

template <typename T>
LinkList<T>::LinkList() {
    this->length = 0;
    this->head = nullptr;
}

template <typename T>
LinkList<T>::~LinkList() {
    auto ptr = head;
    auto ptr_ = ptr;
    if (ptr != nullptr) {
        ptr_ = ptr->getNext();
        delete ptr;
        ptr = ptr_;
    }
    head = nullptr;
}

template <typename T>
ListNode<T> *LinkList<T>::getHead() const {
    return head;
}

template <typename T>
int LinkList<T>::getLength() const {
    return length;
}

template <typename T>
void LinkList<T>::setLength(int length) {
    this->length = length;
}

template <typename T>
void LinkList<T>::insert(T data) {
    auto node = new ListNode<T>(data);
    if (this->getHead() == nullptr) {
        this->setLength(1);
        this->setHead(node);
    } else {
        auto ptr = this->getHead();
        auto ptr_ = ptr;
        while (ptr != nullptr) {
            ptr_ = ptr;
            ptr = ptr->getNext();
        }
        ptr_->setNext(node);
        length++;
    }
}

template<typename T>
void LinkList<T>::setHead(ListNode<T> *head) {
    this->head = head;
}

template<typename T>
void LinkList<T>::display(std::ostream &out) {
    auto ptr = this->getHead();
    while (ptr != nullptr) {
        out << ptr->getData() << std::endl;
        ptr = ptr->getNext();
    }
}

template<typename T>
void LinkList<T>::erase(T data) {
    auto ptr = this->getHead();
    if (ptr == nullptr) {
        return;
    }
    if (data == ptr->getData()) {
        this->setHead(ptr->getNext());
        delete ptr;
        return;
    }

    auto ptr_ = ptr;
    ptr = ptr->getNext();
    while (ptr != nullptr) {
        if (ptr->getData() == data) {
            ptr_->setNext(ptr->getNext());
            delete ptr;
            return;
        }
        ptr_ = ptr;
        ptr = ptr->getNext();
    }
}

template<typename T>
bool LinkList<T>::empty() {
    return this->getHead() == nullptr;
}
