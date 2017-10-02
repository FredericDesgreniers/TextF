cmake_minimum_required(VERSION 3.8)
project(TextF)

set(CMAKE_CXX_STANDARD 17)

set(SOURCE_FILES main.cpp Node.cpp Node.h TextTree.cpp TextTree.h)
add_executable(TextF ${SOURCE_FILES})