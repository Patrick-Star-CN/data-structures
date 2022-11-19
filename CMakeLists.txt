cmake_minimum_required(VERSION 3.23)
project(data_structures)

set(CMAKE_CXX_STANDARD 14)

add_executable(data_structures
        main.cpp
        String/String.cpp
        String/String.h
        Map/Map.h
        LinkList/LinkList.h
        UserLoginSystem.cpp
        UserLoginSystem.h)
