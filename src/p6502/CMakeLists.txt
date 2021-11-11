cmake_minimum_required (VERSION 3.8)

project (p6502 C)

add_library(p6502 STATIC
   perfect6502.c
   perfect6502.h
   netlist_sim.c
   netlist_sim.h
)

target_include_directories(p6502 PUBLIC 
	${CMAKE_CURRENT_SOURCE_DIR}
)
