cmake_minimum_required(VERSION 2.8)
project(06.Semaforos)


set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -DPIZZA")
add_executable(pizza main.cc Semaforo.cpp Machine.cpp Machine.h Constants.h)
