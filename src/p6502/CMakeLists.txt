cmake_minimum_required (VERSION 3.8)

project (p6502 C)

set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)

add_library(p6502 SHARED
   perfect6502.c
   perfect6502.h
   netlist_sim.c
   netlist_sim.h
   ext_cycle.c
   ext_cycle.h
   exported.h
)

target_include_directories(p6502 PUBLIC 
	${CMAKE_CURRENT_SOURCE_DIR}
)

if (${CMAKE_CXX_COMPILER_ID} STREQUAL "GNU")
    target_compile_options(p6502 PRIVATE -Wall -Wextra)
elseif(${CMAKE_CXX_COMPILER_ID} STREQUAL "MSVC")
    target_compile_options(p6502 PRIVATE /EHsc /MTd /W2 /c)
    target_compile_definitions(p6502 PRIVATE WIN_EXPORT)
endif()
