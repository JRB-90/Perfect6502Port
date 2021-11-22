cmake_minimum_required (VERSION 3.8)

project (measure C)

find_library(p6502 NAMES p6502)

add_executable(measure
   measure.c
)

target_include_directories(measure PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(measure PRIVATE
    p6502
)

set_target_properties(measure
    PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)
