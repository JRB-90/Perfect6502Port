cmake_minimum_required (VERSION 3.8)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

project("perfect6502")

add_subdirectory("src/measure")
add_subdirectory("src/p6502")
add_subdirectory("src/cpucheck")
add_subdirectory("src/console-utils")
