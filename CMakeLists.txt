cmake_minimum_required(VERSION 3.5)

project(AIG)

set(CMAKE_CXX_COMPILER "g++-7")
set (CMAKE_CXX_STANDARD 17)

add_library(aig src/aig.cpp src/aig.h)

add_executable(main src/main.cpp)

target_link_libraries(main aig)
