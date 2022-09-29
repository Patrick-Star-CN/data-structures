cmake_minimum_required(VERSION 3.23)
project(data_structures)

set(CMAKE_CXX_STANDARD 14)

add_executable(data_structures main.cpp
        include/LinkList.h
        include/ListNode.h include/Test.h include/String.h src/String.cpp)
