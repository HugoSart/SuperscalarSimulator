#include <stdio.h>
#include <stdlib.h>
#include "simulator/machine/cpu/cpu.h"
#include "simulator/system/system.h"
#include "simulator/machine/cpu/pipeline.h"
#include "simulator/machine/cpu/structures/fifo.h"
#include "simulator/machine/cpu/types.h"
#include "simulator/machine/util.h"


int main() {

    Memory mem = mem_init(MEM_SIZE, MEM_TEXT_ADDRESS);
    CPU cpu = cpu_init(&mem);
    so_load(&mem, "/home/hsart/Documentos/CLion Workspace/SuperscalarSimulator/assembler/build/output");

    for (int i = 0; i < 32; i++) {
        cpu.reg[i].content.value = i;
    }

    so_show_rcr(&cpu);

    while(true) {
 //       system("clear");
        so_show_rrf(&cpu);
        getchar();
        cpu_clock(&cpu);
    }
    return EXIT_SUCCESS;
}