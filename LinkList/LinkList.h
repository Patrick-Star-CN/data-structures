#ifndef DATA_STRUCTURES_ARRAYLIST_H
#define DATA_STRUCTURES_ARRAYLIST_H

#include <iostream>
#include <cassert>

template<typename T>
class LinkList {
private:
    class ListNode {
    public:
        explicit ListNode(const T &data) {
            this->data = data;
            next = nullptr;
            prior = nullptr;
        }

        explicit ListNode(T &&data) {
            this->data = data;
            next = nullptr;
            prior = nullptr;
        }

        T getData() const {
            return data;
        }

        T &getData() {
            return data;
        }

        void setData(T d) {
            data = d;
        }

        ListNode *getNext() const {
            return next;
        }

        void setNext(ListNode *n) {
            next = n;
        }

        ListNode *getPrior() const {
            return prior;
        }

        void setPrior(ListNode *p) {
            prior = p;
        }

    private:
        T data;
        ListNode *next;
        ListNode *prior;
    };

public:
    class Iterator {
    private:
        ListNode *ptr;

    public:
        explicit Iterator(ListNode *ptr) : ptr(ptr) {}

        explicit Iterator(T data) : ptr(new ListNode(data)) {}

        Iterator(const Iterator &right) : ptr(right.ptr) {}

        T &operator*() {
            return (ptr->getData());
        }

        T *operator->() {
            return &(ptr->getData());
        }

        operator ListNode *() {
            return ptr;
        }

        constexpr Iterator operator++(int) {
            Iterator tmp(*this);
            ++(*this);
            return tmp;
        }

        Iterator &operator++() {
            ptr = ptr->getNext();
            return (*this);
        }

        constexpr Iterator operator+(int right) {
            Iterator tmp(*this);
            tmp += right;
            return tmp;
        }

        Iterator &operator+=(int right) {
            if (right >= 0) {
                for (int i = 0; i < right && ptr; ++i) {
                    ptr = ptr->getNext();
                }
            } else {
                for (int i = 0; i > right && ptr; --i) {
                    ptr = ptr->getPrior();
                }
            }
            return (*this);
        }

        constexpr Iterator operator--(int) {
            Iterator tmp(*this);
            --(*this);
            return tmp;
        }

        Iterator &operator--() {
            ptr = ptr->getPrior();
            return (*this);
        }

        constexpr Iterator operator-(int right) {
            Iterator tmp(*this);
            tmp -= right;
            return tmp;
        }

        Iterator &operator-=(int right) {
            return (*this) += (-right);
        }

        bool operator==(const Iterator &right) {
            return ptr == right.ptr;
        }

        bool operator!=(const Iterator &right) {
            return ptr != right.ptr;
        }

        bool operator<(const Iterator &right) {
            return ptr < right.ptr;
        }

        bool operator<=(const Iterator &right) {
            return ptr <= right.ptr;
        }

        bool operator>(const Iterator &right) {
            return ptr > right.ptr;
        }

        bool operator>=(const Iterator &right) {
            return ptr >= right.ptr;
        }
    };

    class ConstIterator {
    private:
        const ListNode *ptr;

    public:
        explicit ConstIterator(ListNode *ptr) : ptr(ptr) {}

        explicit ConstIterator(T data) : ptr(new ListNode(data)) {}

        ConstIterator(const ConstIterator &right) : ptr(right.ptr) {}

        const T operator*() const {
            return (ptr->getData());
        }

        const T *operator->() const {
            return &(ptr->getData());
        }

        constexpr ConstIterator operator++(int) {
            ConstIterator tmp(*this);
            ++(*this);
            return tmp;
        }

        ConstIterator &operator++() {
            ptr = ptr->getNext();
            return (*this);
        }

        constexpr ConstIterator operator--(int) {
            ConstIterator tmp(*this);
            --(*this);
            return tmp;
        }

        ConstIterator &operator--() {
            ptr = ptr->getPrior();
            return (*this);
        }

        bool operator==(const ConstIterator &right) {
            return ptr == right.ptr;
        }

        bool operator!=(const ConstIterator &right) {
            return ptr != right.ptr;
        }

        bool operator<(const ConstIterator &right) {
            return ptr < right.ptr;
        }

        bool operator<=(const ConstIterator &right) {
            return ptr <= right.ptr;
        }

        bool operator>(const ConstIterator &right) {
            return ptr > right.ptr;
        }

        bool operator>=(const ConstIterator &right) {
            return ptr >= right.ptr;
        }
    };

private:

    ListNode *head;
    ListNode *tail;

    unsigned int distance(const Iterator &, const Iterator &);

public:
    LinkList();

    LinkList(T);

    LinkList(const LinkList<T> &);

    LinkList &operator=(const LinkList &);

    virtual ~LinkList();

    Iterator begin();

    ConstIterator cBegin() const;

    Iterator end();

    ConstIterator cEnd() const;

    unsigned int size() const;

    void pushBack(const T &);

    void pushBack(T &&);

    void pushFront(const T &);

    void pushFront(T &&);

    void insert(Iterator, const T &);

    void insert(Iterator, T &&);

    void insert(Iterator, unsigned int, const T &);

    void erase(T data);

    bool empty();

    bool operator==(const LinkList &) const;

    bool operator!=(const LinkList &) const;

};

#endif //DATA_STRUCTURES_ARRAYLIST_H

template<typename T>
LinkList<T>::LinkList() {
    head = nullptr;
    tail = nullptr;
}

template<typename T>
LinkList<T>::LinkList(T data) {
    auto node = new ListNode(data);
    assert(node != nullptr);
    head = node;
    tail = node;
}

template<typename T>
LinkList<T>::~LinkList() {
    if (head == nullptr) {
        return;
    }
    auto ptr = head;
    auto ptr_ = this->head;
    while (ptr != nullptr) {
        ptr_ = ptr->getNext();
        delete ptr;
        ptr = ptr_;
    }
    head = nullptr;
    tail = nullptr;
}

template<typename T>
unsigned int LinkList<T>::size() const {
    return distance(begin(), end());
}

template<typename T>
void LinkList<T>::pushBack(const T &data) {
    auto node = new ListNode(data);
    assert(node != nullptr);
    if (empty()) {
        head = node;
        tail = node;
        return;
    }
    node->setPrior(tail);
    tail->setNext(node);
    tail = node;
}

template<typename T>
void LinkList<T>::pushBack(T &&data) {
    auto node = new ListNode(data);
    assert(node != nullptr);
    if (empty()) {
        head = node;
        tail = node;
        return;
    }
    node->setPrior(tail);
    tail->setNext(node);
    tail = node;
}

template<typename T>
void LinkList<T>::erase(T data) {
    auto ptr = tail;
    if (ptr->getData() == data) {
        tail = ptr->getPrior();
        tail->setNext(nullptr);
        delete ptr;
        ptr = nullptr;
        return;
    }
    ptr = head;
    if (ptr->getData() == data) {
        head = ptr->getNext();
        head->setPrior(nullptr);
        delete ptr;
        ptr = nullptr;
        return;
    }
    auto ptr_ = ptr;
    ptr = ptr->getNext();
    while (ptr != nullptr) {
        if (ptr->getData() == data) {
            ptr_->setNext(ptr->getNext());
            ptr->getNext()->setPrior(ptr_);
            delete ptr;
            ptr = nullptr;
            return;
        }
        ptr_ = ptr;
        ptr = ptr->getNext();
    }
}

template<typename T>
bool LinkList<T>::empty() {
    return head == nullptr;
}

template<typename T>
LinkList<T>::LinkList(const LinkList<T> &ori) {
    LinkList::ConstIterator it = ori.cBegin();
    auto node = new ListNode(*it);
    assert(node != nullptr);
    head = node;
    ++it;
    LinkList::Iterator it_ = begin();
    while (it != ori.cEnd()) {
        node = new ListNode(*it);
        assert(node != nullptr);
        ((LinkList<T>::ListNode *)(it_))->setNext(node);
        node->setPrior(it_);
        ++it;
        ++it_;
    }
    tail = node;
}

template<typename T>
LinkList<T> &LinkList<T>::operator=(const LinkList &ori) {
    LinkList::ConstIterator it = ori.cBegin();
    auto node = new ListNode(*it);
    assert(node != nullptr);
    head = node;
    ++it;
    LinkList::Iterator it_ = begin();
    while (it != ori.cEnd()) {
        node = new ListNode(*it);
        assert(node != nullptr);
        ((LinkList<T>::ListNode *)(it_))->setNext(node);
        node->setPrior(it_);
        ++it;
        ++it_;
    }
    tail = node;
    return (*this);
}


template<typename T>
bool LinkList<T>::operator==(const LinkList &right) const {
    if (size() != right.size()) {
        return false;
    }
    LinkList::Iterator it1 = begin();
    LinkList::Iterator it2 = right.begin();
    while (it1 != end() && it2 != right.end() && (*it1) == (*it2)) {
        ++it1;
        ++it2;
    }
    return it1 != end() && it2 != right.end();
}

template<typename T>
bool LinkList<T>::operator!=(const LinkList &right) const {
    return right != *this;
}

template<typename T>
typename LinkList<T>::Iterator LinkList<T>::begin() {
    return LinkList::Iterator(head);
}

template<typename T>
typename LinkList<T>::ConstIterator LinkList<T>::cBegin() const {
    return LinkList::ConstIterator(head);
}

template<typename T>
typename LinkList<T>::Iterator LinkList<T>::end() {
    return LinkList::Iterator(nullptr);
}

template<typename T>
typename LinkList<T>::ConstIterator LinkList<T>::cEnd() const {
    return LinkList::ConstIterator(nullptr);
}

template<typename T>
void LinkList<T>::pushFront(const T &data) {
    auto node = new ListNode(data);
    if (empty()) {
        head = node;
        tail = node;
        return;
    }
    node->setNext(head);
    head->setPrior(node);
    head = node;
}

template<typename T>
void LinkList<T>::pushFront(T &&data) {
    auto node = new ListNode(data);
    if (empty()) {
        head = node;
        tail = node;
        return;
    }
    node->setNext(head);
    head->setPrior(node);
    head = node;
}

template<typename T>
void LinkList<T>::insert(LinkList::Iterator pos, const T &data) {
    auto node = new ListNode(data);
    node->setNext(pos);
    node->setPrior(pos - 1);
}

template<typename T>
void LinkList<T>::insert(LinkList::Iterator pos, T &&data) {
    auto node = new ListNode(data);
    node->setNext(pos);
    node->setPrior(pos - 1);
}

template<typename T>
void LinkList<T>::insert(LinkList::Iterator pos, unsigned int count, const T &data) {
    auto node = new ListNode(data);
    node->setPrior(pos - 1);
    for (int i = 0; i < count - 1; ++i) {
        auto node_ = new ListNode(data);
        node->setNext(node_);
        node_->setPrior(node);
        node = node_;
    }
    node->setNext(pos);
}

template<typename T>
unsigned int LinkList<T>::distance(const LinkList::Iterator &begin, const LinkList::Iterator &end) {
    unsigned int sum = 0;
    for (LinkList::Iterator it = begin; it != end; ++it, ++sum) {}
    return sum;
}
