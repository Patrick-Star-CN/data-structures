#ifndef DATA_STRUCTURES_STRING_H
#define DATA_STRUCTURES_STRING_H
#include <cassert>
#include <iostream>

class String {
public:
    String();
    String(unsigned);
    String(char);
    String(const char *);
    String(const String &);
    ~String();

    String &operator=(const String &);
    String &operator=(const char *);
    String operator+(const String& right);
    char &operator[](unsigned);
    explicit operator const char *() const;
    bool operator<=(const String &right);
    bool operator<(const String &right);
    bool operator>=(const String &right);
    bool operator>(const String &right);
    bool operator==(const String &right);
    bool operator!=(const String &right);
    void operator+=(const String &right);

    int compare(const String &);
    unsigned length() const;
    char *getBuffer() const;
    String subString(unsigned , unsigned) const;
    unsigned find(const String &, unsigned = 0) const;
    std::istream &getLine(std::istream &);
    String replaceAll(const String &, const String &);


private:
    unsigned bufLen;
    char *buffer;

    int *getPrefix() const;
    int KMPMatch(const String &pattern, unsigned) const;

};

unsigned cStrLen(const char *);
std::istream &operator>>(std::istream &, String &);
std::ostream &operator<<(std::ostream &, const String &);

#endif //DATA_STRUCTURES_STRING_H
