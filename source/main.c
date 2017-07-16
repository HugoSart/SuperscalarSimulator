#include <stdio.h>
#include <stdlib.h>
#include "simulator/machine/cpu/cpu.h"
#include "simulator/system/system.h"
#include "simulator/machine/cpu/pipeline.h"
#include "simulator/machine/cpu/structures/fifo.h"
#include "simulator/machine/cpu/types.h"


int main() {

    Memory mem = mem_init(MEM_SIZE, MEM_TEXT_ADDRESS);
    CPU cpu = cpu_init(&mem);
    so_load(&mem, "/home/hsart/Documentos/CLion Workspace/SuperscalarSimulator/assembler/build/output");

    pipe_fetch(&cpu);
    pipe_decode(&cpu);
    pipe_fetch(&cpu);
    pipe_decode(&cpu);
    pipe_fetch(&cpu);
    pipe_decode(&cpu);

    so_show(&cpu);

    return EXIT_SUCCESS;
}