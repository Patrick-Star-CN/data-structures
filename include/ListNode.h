#ifndef DATA_STRUCTURES_LISTNODE_H
#define DATA_STRUCTURES_LISTNODE_H

template <typename T>
class ListNode {
public:
    explicit ListNode(T data);

    T getData() const;

    ListNode<T> *getNext() const;

    void setNext(ListNode<T> *next);

private:
    T data;

    ListNode<T> *next;
};

#endif //DATA_STRUCTURES_LISTNODE_H

template<typename Node>
ListNode<Node>::ListNode(Node data) {
    this->data = data;
    this->next = nullptr;
}

template<typename Node>
Node ListNode<Node>::getData() const {
    return data;
}

template<typename Node>
ListNode<Node> *ListNode<Node>::getNext() const {
    return next;
}

template<typename Node>
void ListNode<Node>::setNext(ListNode<Node> *next) {
    this->next = next;
}
