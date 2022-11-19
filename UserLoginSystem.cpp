#include "UserLoginSystem.h"

Pair<String, bool> UserLoginSystem::login() {
    String username, pwd;
    std::cout << "请输入账号：";
    std::cin >> username;
    Map<String, String>::Iterator it = userList.find(username);
    if (!it) {
        std::cout << "该账号不存在" << std::endl;
        return Pair<String, bool>(String(), false);
    }
    std::cout << "请输入密码：";
    std::cin >> pwd;
    if (it->getSecond() == pwd) {
        std::cout << "登录成功" << std::endl;
    } else {
        std::cout << "密码错误" << std::endl;
    }
    return Pair<String, bool>(username, true);
}

void UserLoginSystem::updatePassword(const String& username) {
    String pwdOld, pwd, pwd_;
    std::cout << "请输入原密码：";
    std::cin >> pwdOld;
    Map<String, String>::Iterator it = userList.find(username);
    if (!it) {
        std::cout << "用户不存在" << std::endl;
        return;
    } else if (it->getSecond() != pwdOld) {
        std::cout << "原密码错误" << std::endl;
        return;
    }
    std::cout << "请输入新密码：";
    std::cin >> pwd;
    std::cout << "请再次输入新密码：";
    std::cin >> pwd_;
    if (pwd != pwd_) {
        std::cout << "两次密码输入不一致" << std::endl;
        return;
    }
    userList.at(username) = pwd;
    std::cout << "密码修改成功" << std::endl;
}

void UserLoginSystem::deleteUser(const String& username) {
    String pwd;
    std::cout << "请输入密码以验证身份：";
    std::cin >> pwd;
    Map<String, String>::Iterator it = userList.find(username);
    if (!it) {
        std::cout << "用户不存在" << std::endl;
        return;
    } else if (it->getSecond() != pwd) {
        std::cout << "身份验证失败" << std::endl;
        return;
    }
    std::cout << "删除账号成功" << std::endl;
    userList.erase(userList.find(username));
}

Pair<String, bool> UserLoginSystem::registor() {
    String username, pwd, pwd_;
    std::cout << "请输入账号：";
    std::cin >> username;
    Map<String, String>::Iterator it = userList.find(username);
    if (it) {
        std::cout << "该账号已存在" << std::endl;
        return Pair<String, bool>(String(), false);;
    }
    std::cout << "请输入密码：";
    std::cin >> pwd;
    std::cout << "请再次输入密码：";
    std::cin >> pwd_;
    if (pwd != pwd_) {
        std::cout << "两次密码输入不一致" << std::endl;
        return Pair<String, bool>(String(), false);
    }
    userList.insert(Pair<String, String>(username, pwd));
    std::cout << "注册成功" << std::endl;
    return Pair<String, bool>(username, true);
}
