cmake_minimum_required(VERSION 3.6)
project(5Assignment)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp HostNet.cpp HostNet.h Queue.cpp Queue.h Host.h)
add_executable(5Assignment ${SOURCE_FILES})