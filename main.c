#include <stdio.h>
#include <stdlib.h>
#include "simulator/machine/cpu/cpu.h"
#include "simulator/machine/cpu/registers.h"
#include "simulator/machine/cpu/types.h"

#define FUNC_4(r, a, b, c) ()

int main() {

    Memory mem = mem_init(MEM_SIZE, MEM_TEXT_ADDRESS);
    CPU cpu = cpu_init(&mem);
    printf("Result: %d\n", cpu.alu.operation[OP_ADD](cpu.reg_set.reg[A0].value, cpu.reg_set.reg[A1].value));

    return EXIT_SUCCESS;
}