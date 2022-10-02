#ifndef DATA_STRUCTURES_STRING_H
#define DATA_STRUCTURES_STRING_H
#include <cassert>
#include <iostream>

class String {
public:
    String();
    explicit String(unsigned);
    explicit String(char);
    explicit String(const char *);
    String(const String &);
    ~String();

    String &operator=(const String &);
    String &operator=(const char *);
    char &operator[](unsigned);
    explicit operator const char *() const;
    bool operator<=(const String &right);
    bool operator<(const String &right);
    bool operator>=(const String &right);
    bool operator>(const String &right);
    bool operator==(const String &right);
    bool operator!=(const String &right);


    int compare(const String &);
    unsigned length() const;
    char *getBuffer() const;
    int KMPMatch(const String &pattern);

    std::istream &getLine(std::istream &);

private:
    int len;
    unsigned bufLen;
    char *buffer;

    int *getPrefix(char *buffer_, int length);
};

unsigned cStrLen(const char *);
std::istream &operator>>(std::istream &, String &);
std::ostream &operator<<(std::ostream &, String &);

#endif //DATA_STRUCTURES_STRING_H
