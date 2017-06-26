cmake_minimum_required(VERSION 3.7)
project(SuperscalarSimulator)

set(CMAKE_C_STANDARD 99)

set(SOURCE_FILES main.c assembler/op_def.h assembler/bop.h assembler/bop.c assembler/op_def.c memory/memory.c memory/cache.h memory/cache.c)
add_executable(SuperscalarSimulator ${SOURCE_FILES})