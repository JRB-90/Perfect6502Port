cmake_minimum_required (VERSION 3.8)

project (cpucheck C)

find_library(p6502 NAMES p6502)
find_library(console-utils NAMES console-utils)

add_executable(cpucheck
   main.c
)

target_include_directories(cpucheck PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(cpucheck PUBLIC
    p6502
    console-utils
)
