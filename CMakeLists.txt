cmake_minimum_required(VERSION 3.7)
project(SuperscalarSimulator)

set(CMAKE_C_STANDARD 99)

set(SOURCE_FILES main.c assembler/op_def.h assembler/bop.h assembler/bop.c assembler/op_def.c simulator/machine/memory/memory.c simulator/machine/cpu/cache.h simulator/machine/cpu/cache.c simulator/machine/memory/util.h simulator/machine/memory/util.c simulator/system/system.h simulator/system/system.c simulator/machine/cpu/instructions.h simulator/machine/cpu/instructions.c simulator/machine/cpu/cpu.c simulator/machine/cpu/cpu.h simulator/machine/cpu/alu.c simulator/machine/cpu/alu.h simulator/machine/cpu/pipeline.c simulator/machine/cpu/pipeline.h)
add_executable(SuperscalarSimulator ${SOURCE_FILES})