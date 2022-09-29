//
// Created by 卿无言 on 2022/9/23.
//

#ifndef DATA_STRUCTURES_TEST_H
#define DATA_STRUCTURES_TEST_H
class Test {
public:
    Test(int l): l(l) {}

    Test() {}

    friend std::ostream & operator<<(std::ostream &, Test);

    bool operator==(const Test &rhs) const;

    bool operator!=(const Test &rhs) const;

private:
    int l;
};

std::ostream & operator<<(std::ostream &out, Test right) {
    out << right.l;
    return out;
}

bool Test::operator==(const Test &rhs) const {
    return l == rhs.l;
}

bool Test::operator!=(const Test &rhs) const {
    return !(rhs == *this);
}

#endif //DATA_STRUCTURES_TEST_H
