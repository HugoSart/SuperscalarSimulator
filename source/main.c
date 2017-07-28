#include <stdio.h>
#include <stdlib.h>
#include "simulator/machine/cpu/cpu.h"
#include "simulator/system/system.h"
#include "simulator/machine/cpu/pipeline.h"
#include "simulator/machine/cpu/structures/inst_fifo.h"
#include "simulator/machine/types.h"
#include "simulator/machine/util.h"


int main() {

    system("../assembler/build/assembler -c input.s output");

    Memory *mem = mem_new(MEM_SIZE, MEM_TEXT_ADDRESS);
    CPU *cpu = cpu_new(mem);
    so_load(mem, "/home/hsart/Documentos/CLion Workspace/SuperscalarSimulator/assembler/build/output");

    Mobo *mobo = mobo_new(cpu, mem);

    for (int i = 0; i < 32; i++) {
        cpu->reg[i].content.value = i*2;
    }

    while(true) {
        so_show_rcr(cpu);
        so_show_rrf(cpu);
        getchar();
        cpu_clock(cpu);
    }
    return EXIT_SUCCESS;
}