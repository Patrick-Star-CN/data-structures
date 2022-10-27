#ifndef DATA_STRUCTURES_STRING_H
#define DATA_STRUCTURES_STRING_H
#include <cassert>
#include <iostream>

class String {
private:
    unsigned bufLen;
    char *buffer;

    int *getPrefix() const;
    int KMPMatch(const String &pattern, unsigned) const;
    int compare(const String &);

    class iterator {
    public:
        char *ptr;

        iterator(char *ptr): ptr(ptr){}
    };

public:
    String();
    String(unsigned);
    String(char);
    String(const char *);
    String(const String &);
    ~String();

    explicit operator const char *() const;

    String &operator=(const String &);
    String &operator=(const char *);
    String operator+(const String& right);
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
    String::iterator begin() const;
    String::iterator end() const;

    String subString(unsigned , unsigned) const;
    String replaceAll(const String &, const String &);
    unsigned find(const String &, unsigned = 0) const;
    String reverse(const String::iterator, const String::iterator);

    std::istream &getLine(std::istream &);
    std::istream &read(std::istream &, char = ' ');
};

unsigned cStrLen(const char *);
std::istream &operator>>(std::istream &, String &);
std::ostream &operator<<(std::ostream &, const String &);
String toString(int);

#endif //DATA_STRUCTURES_STRING_H
