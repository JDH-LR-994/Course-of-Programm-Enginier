cmake_minimum_required(VERSION 3.30)
project(Cpp)

set(CMAKE_CXX_STANDARD 20)

add_executable(Cpp main.cpp
        MyUniquePtr.hpp
        MySharedPtr.hpp
)
