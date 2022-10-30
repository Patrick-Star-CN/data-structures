#ifndef DATA_STRUCTURES_STRING_H
#define DATA_STRUCTURES_STRING_H

#include <cassert>
#include <iostream>

class String {
private:
    unsigned int bufLen;
    char *buffer;

    int *getPrefix() const;

    int KMPMatch(const String &pattern, unsigned int) const;

    int compare(const String &);

    void clear();

    class Iterator {
    public:
        Iterator(char *ptr) : now(ptr) {}

        Iterator() : now(nullptr) {}

        bool operator==(const Iterator &rhs) const;

        bool operator!=(const Iterator &rhs) const;

        Iterator operator++(int);

        Iterator operator--(int);

        char &operator*() const;

    private:
        char *now;
    };

public:
    String();

    String(unsigned);

    String(char);

    String(const char *);

    String(const String &);

    ~String();

    operator const char *() const;

    operator char *() const;

    String &operator=(const String &);

    String &operator=(const char *);

    String operator+(const String &right);

    friend String operator+(const char, String &right);

    char &operator[](unsigned);

    bool operator<=(const String &right);

    bool operator<(const String &right);

    bool operator>=(const String &right);

    bool operator>(const String &right);

    bool operator==(const String &right);

    bool operator!=(const String &right);

    void operator+=(const String &right);

    char *getBuffer() const;

    unsigned length() const;

    String::Iterator begin() const;

    String::Iterator end() const;

    String subString(unsigned, unsigned) const;

    String replaceAll(const String &, const String &);

    unsigned find(const String &, unsigned = 0) const;

    String reverse(const String::Iterator, const String::Iterator);

    std::istream &getLine(std::istream &);

    std::istream &read(std::istream &, char = ' ');
};

unsigned cStrLen(const char *);

std::istream &operator>>(std::istream &, String &);

std::ostream &operator<<(std::ostream &, const String &);

String toString(int);

#endif //DATA_STRUCTURES_STRING_H
