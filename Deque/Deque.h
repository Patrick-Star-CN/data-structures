#ifndef DATA_STRUCTURES_DEQUE_H
#define DATA_STRUCTURES_DEQUE_H

const int BLOCK_SIZE = 16;

template<typename T>
class Deque {
private:
    class DequeNode {
    public:
        DequeNode() : prior(nullptr), next(nullptr) {
            head = new T[BLOCK_SIZE];
        }

        explicit DequeNode(DequeNode *prior) : prior(prior), next(nullptr) {
            head = new T[BLOCK_SIZE];
        }

        explicit DequeNode(DequeNode *prior, DequeNode *next) : prior(prior), next(next) {
            head = new T[BLOCK_SIZE];
        }

        T *getHead() const {
            return head;
        }

        void setHead(T *head) {
            DequeNode::head = head;
        }

        DequeNode *getNext() const {
            return next;
        }

        void setNext(DequeNode *next) {
            DequeNode::next = next;
        }

        DequeNode *getPrior() const {
            return prior;
        }

        void setPrior(DequeNode *prior) {
            DequeNode::prior = prior;
        }

    private:
        T *head;
        DequeNode *next;
        DequeNode *prior;
    };

    class DequeMapIterator {
    private:
        DequeNode *ptr;

    public:
        DequeMapIterator() : ptr(nullptr) {}

        explicit DequeMapIterator(DequeNode *ptr) : ptr(ptr) {}

        DequeMapIterator(const DequeMapIterator &right) : ptr(right.ptr) {}

        const DequeMapIterator operator++(int);

        const DequeMapIterator operator--(int);

        DequeMapIterator &operator++();

        DequeMapIterator &operator--();

        DequeMapIterator operator+(int);

        DequeMapIterator operator-(int);

        DequeMapIterator &operator+=(int);

        DequeMapIterator &operator-=(int);

        DequeNode *operator*();
    };

    class DequeIterator {
    private:
        DequeMapIterator *first;
        DequeNode *ptr;

    public:
        DequeIterator() : ptr(nullptr) {}

        explicit DequeIterator(DequeNode *ptr) : ptr(ptr) {}

        DequeIterator(const DequeIterator &right) : ptr(right.ptr), first(right.first) {}

        const DequeIterator operator++(int);

        const DequeIterator operator--(int);

        DequeIterator &operator++();

        DequeIterator &operator--();

        DequeIterator operator+(int);

        DequeIterator operator-(int);

        DequeIterator &operator+=(int);

        DequeIterator &operator-=(int);

        T &operator*();
    };

    T *head;

public:
};

template<typename T>
const typename Deque<T>::DequeIterator Deque<T>::DequeIterator::operator++(int) {
    Deque::DequeIterator tmp(*this);
    ++(*this);
    return tmp;
}

template<typename T>
const typename Deque<T>::DequeIterator Deque<T>::DequeIterator::operator--(int) {
    Deque::DequeIterator tmp(*this);
    --(*this);
    return tmp;
}

template<typename T>
typename Deque<T>::DequeIterator &Deque<T>::DequeIterator::operator++() {
    if (ptr == nullptr) {
        return nullptr;
    } else if (ptr - *first == BLOCK_SIZE) {
        ++first;
        ptr = *first;
    }
    ++ptr;
    return (*this);
}

template<typename T>
typename Deque<T>::DequeIterator &Deque<T>::DequeIterator::operator--() {
    if (ptr == nullptr) {
        return nullptr;
    } else if (ptr == *first) {
        --first;
        ptr = *first + BLOCK_SIZE;
    }
    --ptr;
    return (*this);
}

template<typename T>
typename Deque<T>::DequeIterator Deque<T>::DequeIterator::operator+(int n) {
    Deque::DequeIterator tmp(*this);
    tmp += n;
    return tmp;
}

template<typename T>
typename Deque<T>::DequeIterator Deque<T>::DequeIterator::operator-(int n) {
    Deque::DequeIterator tmp(*this);
    tmp -= n;
    return tmp;
}

template<typename T>
typename Deque<T>::DequeIterator &Deque<T>::DequeIterator::operator+=(int n) {
    if (n == 0) {
        return (*this);
    }
    n += ptr - *first;
    if (n > 0) {
        first += n / BLOCK_SIZE;
        ptr = *first + n % BLOCK_SIZE;
    } else {
        int z = BLOCK_SIZE - 1 - n;
        first -= z / BLOCK_SIZE;
        ptr = *first + (BLOCK_SIZE - 1 - z % BLOCK_SIZE);
    }
    return (*this);
}

template<typename T>
typename Deque<T>::DequeIterator &Deque<T>::DequeIterator::operator-=(int n) {
    return (*this) += -n;
}

template<typename T>
T &Deque<T>::DequeIterator::operator*() {
    return *(ptr);
}

template<typename T>
const typename Deque<T>::DequeMapIterator Deque<T>::DequeMapIterator::operator++(int) {
    Deque<T>::DequeMapIterator tmp(*this);
    ++(*this);
    return tmp;
}

template<typename T>
const typename Deque<T>::DequeMapIterator Deque<T>::DequeMapIterator::operator--(int) {
    Deque<T>::DequeMapIterator tmp(*this);
    --(*this);
    return tmp;
}

template<typename T>
typename Deque<T>::DequeMapIterator &Deque<T>::DequeMapIterator::operator++() {
    if (ptr == nullptr) {
        return nullptr;
    }
    ptr = ptr->next;
    return (*this);
}

template<typename T>
typename Deque<T>::DequeMapIterator &Deque<T>::DequeMapIterator::operator--() {
    if (ptr == nullptr) {
        return nullptr;
    }
    ptr = ptr->prior;
    return (*this);
}

template<typename T>
typename Deque<T>::DequeMapIterator Deque<T>::DequeMapIterator::operator+(int n) {
    Deque<T>::DequeMapIterator tmp(*this);
    tmp += n;
    return tmp;
}

template<typename T>
typename Deque<T>::DequeMapIterator Deque<T>::DequeMapIterator::operator-(int n) {
    Deque<T>::DequeMapIterator tmp(*this);
    tmp -= n;
    return tmp;
}

template<typename T>
typename Deque<T>::DequeMapIterator &Deque<T>::DequeMapIterator::operator+=(int n) {
    if (n == 0) {
        return (*this);
    } else if (n < 0) {
        for (int i = 0; i > n; i--) {
            ptr = ptr->getPrior();
            if (!ptr) {
                break;
            }
        }
    } else {
        for (int i = 0; i < n; i++) {
            ptr = ptr->getNext();
            if (!ptr) {
                break;
            }
        }
    }
    return (*this);
}

template<typename T>
typename Deque<T>::DequeMapIterator &Deque<T>::DequeMapIterator::operator-=(int n) {
    return (*this) += -n;
}

template<typename T>
typename Deque<T>::DequeNode *Deque<T>::DequeMapIterator::operator*() {
    return ptr;
}

#endif //DATA_STRUCTURES_DEQUE_H
