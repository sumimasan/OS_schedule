cmake_minimum_required(VERSION 3.22)
project(Mutex)

set(CMAKE_CXX_STANDARD 14)

add_executable(Mutex ReaderAndwriter.cpp semaphone_demo.cpp ProducerAndConsumer.cpp Common.h Bridge.cpp)
