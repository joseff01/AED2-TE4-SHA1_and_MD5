cmake_minimum_required(VERSION 3.19)
project(MD5)

set(CMAKE_CXX_STANDARD 20)

add_executable(MD5 main.cpp MD5Algorithm.cpp MD5Algorithm.h ../LinkedList/List.h)