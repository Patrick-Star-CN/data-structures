#ifndef DATA_STRUCTURES_ARRAYLIST_H
#define DATA_STRUCTURES_ARRAYLIST_H

#include <iostream>
template <typename T>
class LinkList {
private:
    class ListNode {
    public:
        explicit ListNode(T data) {
            this->data = data;
            next = nullptr;
        }

        T data;
        ListNode *next;
    };

    ListNode *head;
    int length;

public:
    LinkList();

    LinkList(T);

    LinkList(const LinkList<T> &);

    virtual ~LinkList();

    LinkList<T>::ListNode *getHead() const;

    int getLength() const;

    void insert(T);

    void display(std::ostream&);

    void erase(T data);

    bool empty();

    bool operator==(const LinkList &) const;

    bool operator!=(const LinkList &) const;

};

#endif //DATA_STRUCTURES_ARRAYLIST_H

template<typename T>
LinkList<T>::LinkList() {
    head = nullptr;
    length = 0;
}

template<typename T>
LinkList<T>::LinkList(T data) {
    auto node = new ListNode(data);
    head = node;
    length = 1;
}

template<typename T>
LinkList<T>::~LinkList() {
    if (head == nullptr) {
        return;
    }
    auto ptr = head;
    auto ptr_ = this->head;
    while (ptr != nullptr) {
        ptr_ = ptr->next;
        delete ptr;
        ptr = ptr_;
    }
    head = nullptr;
    length = 0;
}

template<typename T>
typename LinkList<T>::ListNode *LinkList<T>::getHead() const {
    return head;
}

template<typename T>
int LinkList<T>::getLength() const {
    return length;
}

template<typename T>
void LinkList<T>::insert(T data) {
    auto node = new ListNode(data);
    length ++;
    if (empty()) {
        head = node;
        return;
    }
    auto ptr = head;
    while (ptr->next != nullptr) {
        ptr = ptr->next;
    }
    ptr->next = node;
}

template<typename T>
void LinkList<T>::display(std::ostream &out) {
    auto ptr = head;
    while (ptr != nullptr) {
        out << ptr->data << std::endl;
        ptr = ptr->next;
    }
}

template<typename T>
void LinkList<T>::erase(T data) {
    auto ptr = head;
    if (ptr->data == data) {
        head = ptr->next;
        length --;
        delete ptr;
        ptr = nullptr;
        return;
    }
    auto ptr_ = ptr;
    ptr = ptr->next;
    while (ptr != nullptr) {
        if (ptr->data == data) {
            ptr_->next = ptr->next;
            delete ptr;
            ptr = nullptr;
            length --;
            return;
        }
        ptr_ = ptr;
        ptr = ptr->next;
    }
}

template<typename T>
bool LinkList<T>::empty() {
    return head == nullptr;
}

template<typename T>
LinkList<T>::LinkList(const LinkList<T> &right) {
    length = right.length;
    auto node = new ListNode(right.head->data);
    head = node;
    auto ptr = right.head->next;
    auto _ptr = head;
    while (ptr != nullptr) {
        auto node = new ListNode(ptr->data);
        _ptr->next = node;
        _ptr = _ptr->next;
        ptr = ptr->next;
    }
}

template<typename T>
bool LinkList<T>::operator==(const LinkList &right) const {
    if (length != right.length) {
        return false;
    }
    auto ptr = head;
    auto ptr_ = right.head;
    while (ptr != nullptr && ptr_ != nullptr && ptr->data == ptr_->data) {
        ptr = ptr->next;
        ptr_ = ptr_->next;
    }
    return ptr == nullptr && ptr_ == nullptr;
}

template<typename T>
bool LinkList<T>::operator!=(const LinkList &right) const {
    return right != *this;
}
