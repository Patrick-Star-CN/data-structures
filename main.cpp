#include "LinkList/LinkList.h"
using namespace std;

class Term {
private:
    int zs;
    double xs;
public:
    Term() {}

    Term(int z, double x) : zs(z), xs(x) {}

    int getZs() const {
        return zs;
    }

    void setZs(int zs) {
        Term::zs = zs;
    }

    double getXs() const {
        return xs;
    }

    void setXs(double xs) {
        Term::xs = xs;
    }
};

LinkList<Term> add(const LinkList<Term> &left, const LinkList<Term> &right) {
    LinkList<Term> list;
    for ()
}

int main() {
    LinkList<Term> list1;
    LinkList<Term> list2;
    cout << "请输入多项式P，以指数升序的形式输入，每一项格式为\"系数 指数\"" << endl;
    cout << "输入完成后以\"0 0\"表示结束" << endl;
    int z;
    double x;
    while (cin >> x >> z && (z || x != 0)) {
        list1.insert(Term(z, x));
    }
    cout << "请输入多项式Q，以指数升序的形式输入，每一项格式为\"系数 指数\"" << endl;
    cout << "输入完成后以\"0 0\"表示结束" << endl;
    while (cin >> x >> z && (z || x != 0)) {
        list1.insert(Term(z, x));
    }
    return 0;
}