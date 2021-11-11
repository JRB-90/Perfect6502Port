cmake_minimum_required (VERSION 3.8)

project (console-utils C)

add_library(console-utils STATIC
   console_utils.h
   console_utils.c
)

target_include_directories(console-utils PUBLIC 
	${CMAKE_CURRENT_SOURCE_DIR}
)
