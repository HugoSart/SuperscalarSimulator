//
// Created by hsart on 09/07/17.
//

#include <stdarg.h>
#include "cpu.h"

CPU cpu_init(Memory *mem) {
    CPU cpu = { .cache    = cache_init(mem, CACHE_SIZE),
                .inst_set = inst_init(),
                .reg_set  = reg_init(),
                .alu      = alu_init()};
    return cpu;
}

void cpu_exec(CPU *cpu, EInstructions e, ...) {
    va_list valist;
    va_start(valist, 5);
    cpu->inst_set.instruction[e](&cpu->alu, valist);
    va_end(valist);
}