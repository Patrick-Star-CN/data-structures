#include <iostream>

using namespace std;
typedef int ElementType ;
const int NULL_VALUE=-1; //不存在的位置
const int FREE_NODE=-2; //标记空闲点
class NodeType{
public:
    NodeType(){};
    NodeType(ElementType value, int n=NULL_VALUE):data(value),next(n){  }
    ElementType data;
    int next;
};

const int NUMNODES=1024;
class Array_List{
public:
    Array_List();// 1）构造空列表
//Array_List(const Array_List& origList); 可以省略，考虑为什么可以省略？
//系统会分配一个缺省的拷贝构造函数，而静态数组可以被直接拷贝。
//~Array_List(); 可以省略，考虑为什么可以省略？
//因为静态数组实现的链表没有涉及到动态空间开辟，所以系统分配的缺省的析构函数已经够用了。
//Array_List& operator=(const Array_List&   rightHandSide); 可以省略，考虑为什么可以省略？
//同上，不需要深拷贝，系统分配的缺省的赋值函数已经够用了。

    bool empty() const;//判空
    void insert(ElementType item,int preLoc); //2）插入
    void erase(int preLoc);//3）删除
    void display(ostream& out)const;//4）输出列表元素（遍历）
private:
    NodeType Array[NUMNODES];
    //int free;//指向第一个空闲节点
    int first;//表首结点，
    int mySize;//列表规模
};

Array_List::Array_List() {
    first = NULL_VALUE;
    mySize = 0;
    for (int i = 0; i < NUMNODES; i ++) {
        Array[i].next = FREE_NODE;
    }
}

bool Array_List::empty() const {
    return first == NULL_VALUE;
}

void Array_List::insert(ElementType item, int preLoc) {
    if (mySize == NUMNODES) {
        return;
    }
    mySize ++;
    if (empty()) {
        Array[0] = NodeType(item, NULL_VALUE);
        first = 0;
        return;
    }
    for (int i = 0; i < NUMNODES; i ++) {
        if (Array[i].next == FREE_NODE) {
            Array[i].data = item;
            if (preLoc == -1) {
                Array[i].next = first;
                first = i;
            } else {
                int nLoc = Array[preLoc].next;
                Array[preLoc].next = i;
                Array[i].next = nLoc;
            }
            break;
        }
    }
}

void Array_List::erase(int preLoc) {
    if (empty()) {
        return;
    }
    mySize --;
    int nLoc = preLoc == -1 ? first : Array[preLoc].next;
    if (preLoc == -1) {
        first = Array[first].next;
    } else {
        Array[preLoc].next = Array[Array[preLoc].next].next;
    }
    Array[nLoc].next = FREE_NODE;
}

void Array_List::display(ostream &out) const {
    for (int i = first; i != NULL_VALUE; i = Array[i].next) {
        out << Array[i].data << " ";
    }
}

int main(){
    Array_List a;
    for (int i=0;i<NUMNODES/2;i++){
        a.insert(i*2,-1);
    }
    for (int i=NUMNODES/2;i<NUMNODES; i++) {
        a.insert(i*2,i-1);
    }
    a.erase(3);
    a.erase(5);
    a.erase(8);
    a.insert(17,-1);
    a.insert(20,-1);
    a.display(cout);
    return 0;
}