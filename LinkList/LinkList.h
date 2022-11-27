#ifndef DATA_STRUCTURES_ARRAYLIST_H
#define DATA_STRUCTURES_ARRAYLIST_H

#include <iostream>
#include <cassert>
#include <list>

template<typename T>
class LinkList {
private:
    class ListNode {
    public:
        explicit ListNode(const T &v) {
            data = v;
            next = nullptr;
            prior = nullptr;
        }

        explicit ListNode(T &&v) {
            data = v;
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

        // 交换两个节点，确保 rhs 是在调用点后
        void swap(ListNode *rhs) {
            if (getNext() == rhs) {
                auto p = this->getPrior();
                auto n = rhs->getNext();
                this->setNext(n);
                if (n) {
                    n->setPrior(this);
                }
                this->setNext(rhs);

                rhs->setPrior(p);
                if (p) {
                    p->setNext(rhs);
                }
                rhs->setNext(this);
            } else {
                if (this->getPrior()) {
                    this->getPrior()->setNext(rhs);
                }
                auto p = rhs->getPrior();
                p->setNext(this);
                rhs->setPrior(this->getPrior());
                this->setPrior(p);

                this->getNext()->setPrior(rhs);
                auto n = rhs->getNext();
                if (n) {
                    n->setPrior(this);
                }
                rhs->setNext(this->getNext());
                this->setNext(n);
            }
        }

    private:
        T data;
        ListNode *next;
        ListNode *prior;
    };

public:
    class ConstIterator {
    private:
        const ListNode *ptr;

    public:
        explicit ConstIterator(ListNode *ptr) : ptr(ptr) {}

        explicit ConstIterator(T v) : ptr(new ListNode(v)) {}

        ConstIterator(const ConstIterator &ori) : ptr(ori.ptr) {}

        const T operator*() const {
            return (ptr->getData());
        }

        const T *operator->() const {
            return &(ptr->getData());
        }

        ConstIterator &operator=(const ConstIterator &ori) {
            if (this == &ori) {
                return (*this);
            }
            ptr = ori.ptr;
            return (*this);
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

        bool operator==(const ConstIterator &rhs) {
            return ptr == rhs.ptr;
        }

        bool operator!=(const ConstIterator &rhs) {
            return ptr != rhs.ptr;
        }

        bool operator<(const ConstIterator &rhs) {
            return ptr < rhs.ptr;
        }

        bool operator<=(const ConstIterator &rhs) {
            return ptr <= rhs.ptr;
        }

        bool operator>(const ConstIterator &rhs) {
            return ptr > rhs.ptr;
        }

        bool operator>=(const ConstIterator &rhs) {
            return ptr >= rhs.ptr;
        }
    };

    class Iterator {
    private:
        ListNode *ptr;

    public:
        explicit Iterator(ListNode *ptr) : ptr(ptr) {}

        explicit Iterator(T v) : ptr(new ListNode(v)) {}

        Iterator(const Iterator &ori) : ptr(ori.ptr) {}

        T &operator*() {
            return (ptr->getData());
        }

        T *operator->() {
            return &(ptr->getData());
        }

        explicit operator ListNode *() {
            return ptr;
        }

        explicit operator ConstIterator() {
            return ConstIterator(ptr);
        }

        Iterator &operator=(const Iterator &ori) {
            if (this == &ori) {
                return (*this);
            }
            ptr = ori.ptr;
            return (*this);
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

        constexpr Iterator operator+(int rhs) {
            Iterator tmp(*this);
            tmp += rhs;
            return tmp;
        }

        Iterator &operator+=(int rhs) {
            if (rhs >= 0) {
                for (int i = 0; i < rhs && ptr; ++i) {
                    ptr = ptr->getNext();
                }
            } else {
                for (int i = 0; i > rhs && ptr; --i) {
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

        constexpr Iterator operator-(int rhs) {
            Iterator tmp(*this);
            tmp -= rhs;
            return tmp;
        }

        Iterator &operator-=(int rhs) {
            return (*this) += (-rhs);
        }

        bool operator==(const Iterator &rhs) {
            return ptr == rhs.ptr;
        }

        bool operator!=(const Iterator &rhs) {
            return ptr != rhs.ptr;
        }

        bool operator<(const Iterator &rhs) {
            return ptr < rhs.ptr;
        }

        bool operator<=(const Iterator &rhs) {
            return ptr <= rhs.ptr;
        }

        bool operator>(const Iterator &rhs) {
            return ptr > rhs.ptr;
        }

        bool operator>=(const Iterator &rhs) {
            return ptr >= rhs.ptr;
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

    void assign(const LinkList<T> &);

    void clear();

    unsigned int size() const;

    void pushBack(const T &);

    void pushBack(T &&);

    void pushFront(const T &);

    void pushFront(T &&);

    void popBack();

    void popFront();

    Iterator insert(Iterator, const T &);

    Iterator insert(Iterator, T &&);

    Iterator insert(Iterator, unsigned int, const T &);

    Iterator insert(Iterator, Iterator, Iterator);

    Iterator erase(Iterator);

    Iterator erase(Iterator, Iterator);

    bool empty();

    bool operator==(const LinkList &) const;

    bool operator!=(const LinkList &) const;

    void SelectSortList();

    void InsertSortList();

//TODO void swap(LinkList &other)
//TODO void unique()

};

#endif //DATA_STRUCTURES_ARRAYLIST_H

template<typename T>
LinkList<T>::LinkList() {
    head = nullptr;
    tail = nullptr;
}

template<typename T>
LinkList<T>::LinkList(T v) {
    auto node = new ListNode(v);
    assert(node != nullptr);
    head = node;
    tail = node;
}

template<typename T>
LinkList<T>::~LinkList() {
    clear();
}

template<typename T>
unsigned int LinkList<T>::size() const {
    return distance(begin(), end());
}

template<typename T>
bool LinkList<T>::empty() {
    return begin() == end();
}

template<typename T>
LinkList<T>::LinkList(const LinkList<T> &ori) {
    assign(ori);
}

template<typename T>
LinkList<T> &LinkList<T>::operator=(const LinkList &ori) {
    if (this == &ori) {
        return (*this);
    }
    clear();
    assign(ori);
    return (*this);
}

template<typename T>
bool LinkList<T>::operator==(const LinkList &rhs) const {
    if (size() != rhs.size()) {
        return false;
    }
    LinkList::Iterator it1 = begin();
    LinkList::Iterator it2 = rhs.begin();
    while (it1 != end() && it2 != rhs.end() && (*it1) == (*it2)) {
        ++it1;
        ++it2;
    }
    return it1 != end() && it2 != rhs.end();
}

template<typename T>
bool LinkList<T>::operator!=(const LinkList &rhs) const {
    return rhs != *this;
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
void LinkList<T>::pushBack(const T &v) {
    auto node = new ListNode(v);
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
void LinkList<T>::pushBack(T &&v) {
    auto node = new ListNode(v);
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
void LinkList<T>::pushFront(const T &v) {
    auto node = new ListNode(v);
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
void LinkList<T>::pushFront(T &&v) {
    auto node = new ListNode(v);
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
void LinkList<T>::popBack() {
    auto ptr = tail;
    tail->getPrior()->setNext(nullptr);
    tail = tail->getPrior();
    delete ptr;
}

template<typename T>
void LinkList<T>::popFront() {
    auto ptr = head;
    head->getNext()->setPrior(nullptr);
    head = head->getNext();
    delete ptr;
}

template<typename T>
typename LinkList<T>::Iterator LinkList<T>::insert(LinkList::Iterator pos, const T &v) {
    if (pos == end()) {
        pushBack(v);
        return Iterator(head);
    } else if (pos == begin()) {
        pushFront(v);
        return Iterator(tail);
    }
    auto node = new ListNode(v);
    ((LinkList<T>::ListNode *) (pos - 1))->setNext(node);
    node->setPrior(pos - 1);
    ((LinkList<T>::ListNode *) (pos))->setPrior(node);
    node->setNext(pos);
    return Iterator(node);
}

template<typename T>
typename LinkList<T>::Iterator LinkList<T>::insert(LinkList::Iterator pos, T &&v) {
    if (pos == end()) {
        pushBack(v);
        return Iterator(head);
    } else if (pos == begin()) {
        pushFront(v);
        return Iterator(tail);
    }
    auto node = new ListNode(v);
    ((LinkList<T>::ListNode *) (pos - 1))->setNext(node);
    node->setPrior(((LinkList<T>::ListNode *) (pos - 1)));
    ((LinkList<T>::ListNode *) (pos))->setPrior(node);
    node->setNext(((LinkList<T>::ListNode *) (pos)));
    return Iterator(node);
}

template<typename T>
typename LinkList<T>::Iterator LinkList<T>::insert(LinkList::Iterator pos, unsigned int count, const T &v) {
    if (count == 0) {
        return pos;
    } else if (pos == begin()) {
        for (int i = 0; i < count; ++i) {
            pushFront(v);
        }
        return Iterator(head);
    } else if (pos == end()) {
        for (int i = 0; i < count; ++i) {
            pushBack(v);
        }
        return Iterator(tail);
    }
    auto node = new ListNode(v);
    auto res = node;
    ((LinkList<T>::ListNode *) (pos - 1))->setNext(node);
    node->setPrior(pos - 1);
    for (int i = 0; i < count; ++i) {
        auto node_ = new ListNode(v);
        node->setNext(node_);
        node_->setPrior(node);
        node = node_;
    }
    ((LinkList<T>::ListNode *) (pos))->setPrior(node);
    node->setNext(pos);
    return Iterator(res);
}

template<typename T>
typename LinkList<T>::Iterator
LinkList<T>::insert(LinkList::Iterator pos, LinkList::Iterator first, LinkList::Iterator last) {
    if (first == last) {
        return pos;
    }
    LinkList::Iterator it(first);
    auto node = new ListNode(*it);
    ++it;
    auto res = node;
    for (; it != last; ++it) {
        auto node_ = new ListNode(*it);
        node->setNext(node_);
        node_->setPrior(node);
        node = node_;
    }
    if (pos == begin()) {
        head->setPrior(node);
        head = res;
    } else if (pos == end()) {
        tail->setNext(res);
        tail = node;
    } else {
        ((LinkList<T>::ListNode *) (pos - 1))->setNext(res);
        res->setPrior(pos - 1);
        ((LinkList<T>::ListNode *) (pos))->setPrior(node);
    }
    node->setNext(pos);
    return Iterator(res);
}

template<typename T>
typename LinkList<T>::Iterator LinkList<T>::erase(LinkList::Iterator pos) {
    if (((LinkList<T>::ListNode *) (pos)) == head) {
        popFront();
        return Iterator(head);
    } else if (((LinkList<T>::ListNode *) (pos)) == tail) {
        popBack();
        return end();
    }
    LinkList::ListNode *prior = ((LinkList<T>::ListNode *) (pos - 1));
    LinkList::ListNode *next = ((LinkList<T>::ListNode *) (pos + 1));
    prior->setNext(next);
    next->setPrior(prior);
    delete ((LinkList<T>::ListNode *) (pos));
    return Iterator(next);
}

template<typename T>
typename LinkList<T>::Iterator LinkList<T>::erase(LinkList::Iterator first, LinkList::Iterator last) {
    while (first != last) {
        first = erase(first);
    }
    return last;
}

template<typename T>
unsigned int LinkList<T>::distance(const LinkList::Iterator &first, const LinkList::Iterator &last) {
    unsigned int sum = 0;
    for (LinkList::Iterator it = first; it != last; ++it, ++sum);
    return sum;
}

template<typename T>
void LinkList<T>::assign(const LinkList<T> &ori) {
    if (ori.head == nullptr) {
        return;
    }
    LinkList::ConstIterator it = ori.cBegin();
    auto node = new ListNode(*it);
    assert(node != nullptr);
    head = node;
    ++it;
    LinkList::Iterator it_ = begin();
    while (it != ori.cEnd()) {
        node = new ListNode(*it);
        assert(node != nullptr);
        ((LinkList<T>::ListNode *) (it_))->setNext(node);
        node->setPrior(((LinkList<T>::ListNode *) (it_)));
        ++it;
        ++it_;
    }
    tail = node;
}

template<typename T>
void LinkList<T>::clear() {
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
void LinkList<T>::SelectSortList() {
    for (auto ptr1 = head; ptr1; ptr1 = ptr1->getNext()) {
        auto Min = ptr1;
        for (auto ptr2 = ptr1->getNext(); ptr2; ptr2 = ptr2->getNext()) {
            if (ptr2->getData() < Min->getData()) {
                Min = ptr2;
            }
        }
        if (Min != ptr1) {
            ptr1->swap(Min);
            head = head == ptr1 ? Min : head;
            tail = tail == Min ? ptr1 : tail;
            ptr1 = Min;
        }
    }
}

template<typename T>
void LinkList<T>::InsertSortList() {
    for (auto ptr1 = head->getNext(); ptr1; ptr1 = ptr1->getNext()) {
        auto ptr2 = head;
        for (; ptr2 != ptr1 && ptr2->getData() < ptr1->getData(); ptr2 = ptr2->getNext());
        if (ptr2 != ptr1) {
            auto ptr = ptr1->getPrior();
            ptr1->getPrior()->setNext(ptr1->getNext());
            if (ptr1->getNext()) {
                ptr1->getNext()->setPrior(ptr1->getPrior());
            }

            if (ptr2->getPrior()) {
                ptr2->getPrior()->setNext(ptr1);
            }
            ptr1->setPrior(ptr2->getPrior());
            ptr2->setPrior(ptr1);
            ptr1->setNext(ptr2);
            head = head == ptr2 ? ptr1 : head;
            tail = tail == ptr1 ? ptr : tail;
            ptr1 = ptr;
        }
    }
}
