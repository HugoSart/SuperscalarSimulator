cmake_minimum_required(VERSION 3.7)
project(SuperscalarSimulator)

set(CMAKE_C_FLAGS "-lpthread")

set(CMAKE_C_STANDARD 99)
set(SOURCE_FILES
        source/main.c
        assembler/bop.h
        assembler/bop.c
        source/simulator/system/system.h
        source/simulator/system/system.c
        source/simulator/machine/memory/memory.h
        source/simulator/machine/memory/memory.c
        source/simulator/machine/cpu/cache.h
        source/simulator/machine/cpu/cache.c
        source/simulator/machine/util.h
        source/simulator/machine/types.h
        source/simulator/machine/cpu/instructions.h
        source/simulator/machine/cpu/instructions.c
        source/simulator/machine/cpu/alu.c
        source/simulator/machine/cpu/alu.h
        source/simulator/machine/cpu/pipeline.c
        source/simulator/machine/cpu/pipeline.h
        source/simulator/machine/cpu/cpu.c
        source/simulator/machine/cpu/cpu.h
        source/simulator/machine/cpu/structures/inst_fifo.c
        source/simulator/machine/cpu/structures/inst_fifo.h
        source/simulator/machine/cpu/rstation.c
        source/simulator/machine/cpu/rstation.h
        source/simulator/machine/cpu/register.c
        source/simulator/machine/cpu/register.h
        source/simulator/machine/motherboard/mobo.c
        source/simulator/machine/motherboard/mobo.h source/simulator/machine/cpu/structures/cdb_fifo.c source/simulator/machine/cpu/structures/cdb_fifo.h)

add_executable(SuperscalarSimulator ${SOURCE_FILES})