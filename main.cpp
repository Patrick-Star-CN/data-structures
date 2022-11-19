#include "UserLoginSystem.h"
#include <iostream>

using namespace std;

int main() {
    UserLoginSystem userLoginSystem;
    Pair<String, bool> res_ = userLoginSystem.registor();
    if (res_.getSecond()) {
        Pair<String, bool> res = userLoginSystem.login();
        if (res.getSecond()) {
            userLoginSystem.updatePassword(res.getFirst());
            userLoginSystem.deleteUser(res.getFirst());
        }
    }
    return 0;
}
