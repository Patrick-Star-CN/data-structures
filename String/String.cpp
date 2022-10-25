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

String &String::operator=(const String &right) {
    const unsigned rightLength = right.length();
    if (rightLength >= bufLen) {
        delete []buffer;
        bufLen = 1 + rightLength;
        buffer = new char[bufLen];
        assert(buffer != nullptr);
    }
    unsigned i = 0;
    for (; right.buffer[i] != '\0'; i ++) {
        buffer[i] = right.buffer[i];
    }
    buffer[i] = '\0';
    return (*this);
}

String &String::operator=(const char *right) {
    const unsigned rightLength = cStrLen(right);
    if (rightLength >= bufLen) {
        delete []buffer;
        bufLen = 1 + rightLength;
        buffer = new char[bufLen];
        assert(buffer != nullptr);
    }
    unsigned i = 0;
    for (; right[i] != '\0'; i ++) {
        buffer[i] = right[i];
    }
    buffer[i] = '\0';
    return (*this);
}

char nothing;
char &String::operator[](unsigned index) {
    if (index >= cStrLen(buffer)) {
        nothing = '\0';
        return nothing;
    }
    return buffer[index];
}

int String::compare(const String &right) {
    char *p = buffer;
    char *q = right.buffer;

    for (; (*p != '\0') && (*p == *q); p ++, q ++);
    return *p - *q;
}

String::operator const char *() const {
    return buffer;
}

std::istream &String::getLine(std::istream &in) {
    in.getline(buffer, bufLen, '\n');
    return in;
}

unsigned cStrLen(const char *s) {
    unsigned len = 0;
    for(; s[len] != '\0'; len ++);
    return len;
}

std::istream &operator>>(std::istream &in, String &str) {
    char inBuffer[1000];
    if (in >> inBuffer) {
        str = inBuffer;
    } else {
        str = " ";
    }
    return in;
}

std::ostream &operator<<(std::ostream &out, const String &str) {
    out << str.getBuffer();
    return out;
}

String operator+(const String &left, const String &right) {
    String newString(left);
    newString += right;
    return newString;
}

int String::KMPMatch(const String &pattern, unsigned num = 0) const {
    int *prefix = getPrefix(pattern.buffer, pattern.length());
    int tar = 0, pos = 0, num_ = 0;
    while (tar < length()) {
        if (buffer[tar] == pattern.buffer[pos]) {
            tar ++;
            pos ++;
        } else if (pos != 0) {
            pos = prefix[pos - 1];
        } else {
            tar ++;
        }

        if (pos == pattern.length()) {
            if (num == num_) {
                return tar - pos;
            }
            num_ ++;
        }
    }
    return -1;
}

int *String::getPrefix(char *buffer_, int length) const {
    int *prefix = new int[length];
    prefix[0] = 0;
    int i = 1, now = 0;
    while (i < length) {
        if (buffer_[i] == buffer_[now]) {
            now ++;
            prefix[i] = now;
            i ++;
        } else if (now != 0) {
            now = prefix[now - 1];
        } else {
            i ++;
            prefix[i] = now;
        }
    }
    return prefix;
}

bool String::operator<=(const String &right) {
    return compare(right) <= 0;
}

bool String::operator<(const String &right) {
    return compare(right) < 0;
}

bool String::operator>=(const String &right) {
    return compare(right) >= 0;
}

bool String::operator>(const String &right) {
    return compare(right) > 0;
}

bool String::operator==(const String &right) {
    return compare(right) == 0;
}

bool String::operator!=(const String &right) {
    return compare(right) != 0;
}

void String::operator+=(const String &right) {
    int len = bufLen + right.bufLen - 1;
    char *newBuffer = new char[len];
    assert(newBuffer != nullptr);
    int i = 0;
    for (; i < bufLen - 1; i ++) {
        newBuffer[i] = buffer[i];
    }
    for (int j = 0; i < len - 1; i ++, j ++) {
        newBuffer[i] = right.buffer[j];
    }
    newBuffer[i] = '\0';
    bufLen = len;
    delete []buffer;
    buffer = newBuffer;
}

String String::subString(unsigned pos, unsigned len) const {
    String newStr(len + 1);
    for (int i = pos, j = 0; i < pos + len; i ++, j ++) {
        newStr.buffer[j] = buffer[i];
    }
    return newStr;
}

String replace_all(const String &str, const String &subString, const String &newSubstring) {
    String newStr;
    int i = str.KMPMatch(subString, 0), j = 0, k = 0;
    for (; i != -1; k ++, i = str.KMPMatch(subString, k)) {
        newStr += str.subString(j, i - j);
        newStr += newSubstring;

        j = i + cStrLen(subString.getBuffer());
    }
    return newStr;
}