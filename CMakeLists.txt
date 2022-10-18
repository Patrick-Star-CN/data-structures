cmake_minimum_required(VERSION 3.23)
project(data_structures)

set(CMAKE_CXX_STANDARD 14)

add_executable(data_structures main.cpp
        LinkList/LinkList.h
        String/String.h String/String.cpp)
