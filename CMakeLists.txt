cmake_minimum_required(VERSION 3.15)
project(sylarServer)

set(CMAKE_CXX_STANDARD 14)

add_executable(sylarServer sylar/main.cpp sylar/log.cpp sylar/log.h)