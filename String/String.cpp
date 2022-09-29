#include "String.h"

unsigned String::length() const{
    return cStrLen(buffer);
}

String::String(): bufLen(1) {
    buffer = new char[bufLen];
    assert(buffer != nullptr);
    buffer[0] = '\0';
}

String::String(unsigned size): bufLen(size) {
    buffer = new char[size];
    assert(buffer != nullptr);
    for (unsigned i = 0; i < bufLen; i ++) {
        buffer[i] = '\0';
    }
}

String::String(char c): bufLen(2) {
    buffer = new char[bufLen];
    assert(buffer != nullptr);
    buffer[0] = c;
    buffer[1] = '\0';
}

String::String(const char *initStr): bufLen(1 + cStrLen(initStr)){
    buffer = new char[bufLen];
    assert(buffer != nullptr);
    for (unsigned i = 0; i < bufLen - 1; i ++) {
        buffer[i] = initStr[i];
    }
    buffer[bufLen - 1] = '\0';
}

String::String(const String &initStr): bufLen(1 + cStrLen(initStr.buffer)) {
    buffer = new char[bufLen];
    assert(buffer != nullptr);
    for (unsigned i = 0; i < bufLen - 1; i ++) {
        buffer[i] = initStr.buffer[i];
    }
    buffer[bufLen - 1] = '\0';
}

String::~String() {
    delete []buffer;
    bufLen = 0;
    buffer = nullptr;
}

char *String::getBuffer() const {
    return buffer;
}

void String::operator=(const String &right) {
    const unsigned rightLength = right.length();
    if (rightLength >= bufLen) {
        delete []buffer;
        bufLen = 1 + rightLength;
        buffer = new char[bufLen];
        assert(buffer != nullptr);
    }
    unsigned i = 0;
    for (; right.buffer[i] != '\0'; i ++) {

    }
}

unsigned cStrLen(const char *s) {
    unsigned len = 0;
    for(; s[len] != '\0'; len ++);
    return len;
}