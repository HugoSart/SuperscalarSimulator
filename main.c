#include <stdio.h>
#include <stdlib.h>
#include "simulator/machine/cpu/cpu.h"
#include "simulator/machine/cpu/registers.h"
#include "simulator/machine/types.h"
#include "simulator/system/system.h"

#define FUNC_4(r, a, b, c) ()

#include "simulator/machine/cpu/cache.h"
#include "simulator/machine/memory/memory.h"


int main() {

    Memory mem = mem_init(MEM_SIZE, MEM_TEXT_ADDRESS);
    CPU cpu = cpu_init(&mem);
    so_load(&mem, "/home/hsart/Documentos/CLion Workspace/SuperscalarSimulator/assembler/build/output");
    cache_write(&cpu.cache, 132, (BYTE[WORD_SIZE]){7,2,3,4});
    cache_write(&cpu.cache, 112, (BYTE[WORD_SIZE]){8,2,3,4});
    cache_write(&cpu.cache, 4,   (BYTE[WORD_SIZE]){9,9,9,9});
    cpu_set_reg(&cpu, A1, 137);
    cpu_set_reg(&cpu, A2, 153);
    cpu_exec(&cpu, ADD, A0, A1, A2);
    so_show(&cpu);

    return EXIT_SUCCESS;
}