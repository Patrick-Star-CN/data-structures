#include "LinkList/LinkList.h"
#include <list>
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

LinkList<Term> der(LinkList<Term> &ori) {
    LinkList<Term> list;
    LinkList<Term>::Iterator it = ori.begin();
    for (; it != ori.end(); ++it) {
        if ((*it).getZs()) {
            list.pushBack(Term((*it).getZs() - 1, (*it).getZs() * (*it).getXs()));
        }
    }
    return list;
}

LinkList<Term> mul(LinkList<Term> &left, LinkList<Term> &right) {
    LinkList<Term> list;
    LinkList<Term>::Iterator it = left.begin();
    LinkList<Term>::Iterator iter = right.begin();
    for (; it != left.end(); ++it) {
        for (; iter != right.end(); ++iter) {
            int zs = (*it).getZs() + (*iter).getZs();
            double xs = (*it).getXs() * (*iter).getXs();
            LinkList<Term>::Iterator it_ = list.begin();
            for (; it_ != list.end(); ++it_) {
                if ((*it_).getZs() >= zs) {
                    break;
                }
            }
            if (it_ == list.end()) {
                list.pushBack(Term(zs, xs));
            } else if ((*it_).getZs() == zs) {
                (*it_) = Term(zs, (*it_).getXs() + xs);
            } else {
                list.insert(it, Term(zs, xs));
            }
        }
    }
    return list;
}

LinkList<Term> add(LinkList<Term> left, LinkList<Term> &right) {
    LinkList<Term> list;
    LinkList<Term>::Iterator it = left.begin();
    LinkList<Term>::Iterator iter = right.begin();
    while (it != left.end() && iter != right.end()) {
        if ((*it).getZs() == (*iter).getZs()) {
            list.pushBack(Term((*it).getZs(), (*it).getXs() + (*iter).getXs()));
            ++it;
            ++iter;
        } else if ((*it).getZs() > (*iter).getZs()) {
            list.pushBack(Term((*iter).getZs(), (*iter).getXs()));
            ++iter;
        } else {
            list.pushBack(Term((*it).getZs(), (*it).getXs()));
            ++it;
        }
    }
    while (it != left.end()) {
        list.pushBack(Term((*it).getZs(), (*it).getXs()));
        ++it;
    }
    while (iter != right.end()) {
        list.pushBack(Term((*iter).getZs(), (*iter).getXs()));
        ++iter;
    }
    return list;
}

void display(ostream &out, LinkList<Term> v) {
    LinkList<Term>::Iterator it = v.begin();
    out << (*it).getXs() << "x^" << (*it).getZs() << " ";
    ++it;
    for (; it != v.end(); ++it) {
        out << showpos << (*it).getXs() << noshowpos << "x^" << (*it).getZs() << " ";
    }
    out << endl;
}

int main() {
    LinkList<Term> list1;
    LinkList<Term> list2;
    cout << "请输入多项式P，以指数升序的形式输入，每一项格式为\"系数 指数\"" << endl;
    cout << "输入完成后以\"0 0\"表示结束" << endl;
    int z;
    double x;
    while (cin >> x >> z && (z || x != 0)) {
        list1.pushBack(Term(z, x));
    }
    cout << "请输入多项式Q，以指数升序的形式输入，每一项格式为\"系数 指数\"" << endl;
    cout << "输入完成后以\"0 0\"表示结束" << endl;
    while (cin >> x >> z && (z || x != 0)) {
        list2.pushBack(Term(z, x));
    }
    display(cout, add(list1, list2));
    display(cout, der(list1));
    display(cout, mul(list1, list2));
    return 0;
}