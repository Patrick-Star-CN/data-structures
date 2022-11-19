#ifndef DATA_STRUCTURES_USERLOGINSYSTEM_H
#define DATA_STRUCTURES_USERLOGINSYSTEM_H
#include "Map/Map.h"
#include "String/String.h"
#include <iostream>

class UserLoginSystem {
public:
    Pair<String, bool> registor();

    Pair<String, bool> login();

    void updatePassword(const String&);

    void deleteUser(const String&);

private:
    Map<String, String> userList;
};


#endif //DATA_STRUCTURES_USERLOGINSYSTEM_H
