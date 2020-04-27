cmake_minimum_required(VERSION 2.8)
project(02.Memoria_Compartida)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -DEJEMPLO_1")
add_executable(ejemplo1 main1.cc)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -DEJEMPLO_2")
add_executable(ejemplo2 main2.cc)
