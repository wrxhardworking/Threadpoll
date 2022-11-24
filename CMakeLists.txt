cmake_minimum_required(VERSION 3.23)
project(fifo)

set(CMAKE_CXX_STANDARD 14)

add_executable(fifo TaskQueue.hpp  Threadpool.cc test/test.cpp)
add_subdirectory(test)