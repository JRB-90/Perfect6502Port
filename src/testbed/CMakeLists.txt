cmake_minimum_required (VERSION 3.8)

project (testbed C)

find_library(p6502 NAMES p6502)
find_library(console-utils NAMES console-utils)

add_executable(testbed
   main.c
)

target_include_directories(testbed PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(testbed PUBLIC
    p6502
    console-utils
)
