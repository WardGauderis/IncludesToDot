cmake_minimum_required(VERSION 3.14)
project(toDot)

set(CMAKE_CXX_STANDARD 17)

add_executable(toDot Scanner.cpp Scanner.h main.cpp)