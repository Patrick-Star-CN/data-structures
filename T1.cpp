#include <iostream>
#include "Stack/Stack.h"
#include "Deque/Deque.h"
#include "Map/Map.h"

using namespace std;

class Enode {
public:
    int vertex;
    Enode *next;
};

class Vnode {
public:
    char vdata;
    Enode *EdgeList;
};

void init(Vnode *vnode, Enode *enode) {
    enode[0].vertex = 1;
    enode[0].next = nullptr;
    enode[1].vertex = 2;
    enode[1].next = &enode[0];
    enode[2].vertex = 3;
    enode[2].next = &enode[1];
    enode[3].vertex = 4;
    enode[3].next = nullptr;
    enode[4].vertex = 0;
    enode[4].next = nullptr;
    enode[5].vertex = 4;
    enode[5].next = nullptr;
    enode[6].vertex = 2;
    enode[6].next = nullptr;
    vnode[0].EdgeList = &enode[2];
    vnode[1].EdgeList = &enode[3];
    vnode[2].EdgeList = &enode[4];
    vnode[3].EdgeList = &enode[5];
    vnode[4].EdgeList = &enode[6];
}

void DFS(Vnode *vnode, Enode *enode) {
    Map<char, bool> map;
    map.insert(Pair<char, bool>('A', false));
    map.insert(Pair<char, bool>('B', false));
    map.insert(Pair<char, bool>('C', false));
    map.insert(Pair<char, bool>('D', false));
    map.insert(Pair<char, bool>('E', false));
    Stack<Vnode> stack;
    auto ptr = vnode[0].EdgeList;
    while (ptr) {
        stack.push(vnode[ptr->vertex]);
        ptr = ptr->next;
    }
    cout << "DFS:" << vnode[0].vdata << " ";
    map.find(vnode[0].vdata)->getSecond() = true;
    while (!stack.empty()) {
        auto tmp = stack.top();
        stack.pop();
        if (!map.find(tmp.vdata)->getSecond()) {
            auto p = tmp.EdgeList;
            while (p) {
                stack.push(vnode[p->vertex]);
                p = p->next;
            }
            cout << tmp.vdata << " ";
            map.find(tmp.vdata)->getSecond() = true;
        }
    }
    cout << endl;
}

void BFS(Vnode *vnode, Enode *enode) {
    Map<char, bool> map;
    map.insert(Pair<char, bool>('A', false));
    map.insert(Pair<char, bool>('B', false));
    map.insert(Pair<char, bool>('C', false));
    map.insert(Pair<char, bool>('D', false));
    map.insert(Pair<char, bool>('E', false));
    Deque<Vnode> deque;
    auto ptr = vnode[0].EdgeList;
    while (ptr) {
        deque.pushBack(vnode[ptr->vertex]);
        ptr = ptr->next;
    }
    cout << "BFS:" << vnode[0].vdata << " ";
    map.find(vnode[0].vdata)->getSecond() = true;
    while (!deque.empty()) {
        auto tmp = deque.front();
        deque.popFront();
        if (!map.find(tmp.vdata)->getSecond()) {
            auto p = tmp.EdgeList;
            while (p) {
                deque.pushBack(vnode[p->vertex]);
                p = p->next;
            }
            cout << tmp.vdata << " ";
            map.find(tmp.vdata)->getSecond() = true;
        }
    }
}

int main() {
    Vnode vnode[5] = {{'A'},
                      {'B'},
                      {'C'},
                      {'D'},
                      {'E'}};
    Enode enode[7];
    init(vnode, enode);
    DFS(vnode, enode);
    BFS(vnode, enode);
    return 0;
}