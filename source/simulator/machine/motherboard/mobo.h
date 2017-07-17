//
// Created by hsart on 16/07/17.
//

#ifndef SUPERSCALARSIMULATOR_MOBO_H
#define SUPERSCALARSIMULATOR_MOBO_H

#include "../memory/memory.h"
#include "../cpu/types.h"
#include "../cpu/cpu.h"

typedef struct mobo_t {
    Memory *mem;
    CPU *cpu;
    Word control_bus, address_bus, data_bus;
} Mobo;

Mobo mobo_init(CPU *cpu, Memory *mem) {
    return (Mobo){ .cpu = cpu, .mem = mem, .address_bus = {0}, .control_bus = {0}, .data_bus = {0} };
}

#endif //SUPERSCALARSIMULATOR_MOBO_H
