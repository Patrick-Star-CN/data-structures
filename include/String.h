#ifndef DATA_STRUCTURES_STRING_H
#define DATA_STRUCTURES_STRING_H
#include <assert.h>

class String {
public:
    String();
    String(unsigned);
    String(char);
    String(const char *);
    String(const String &);
    ~String();

    void operator=(const String &);

    unsigned length() const;
    char *getBuffer() const;


private:
    int len;
    unsigned bufLen;
    char *buffer;

};

unsigned cStrLen(const char *);

#endif //DATA_STRUCTURES_STRING_H
