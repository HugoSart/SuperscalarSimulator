//
// Created by hsart on 16/07/17.
//

#ifndef SUPERSCALARSIMULATOR_MOBO_H
#define SUPERSCALARSIMULATOR_MOBO_H

#include "../memory/memory.h"
#include "../cpu/types.h"
#include "../cpu/cpu.h"

typedef struct bus128_t {
    Word data[4];
    int busy;
} Bus128;

typedef struct mobo_t {
    Memory *mem;
    CPU *cpu;
    Bus128 data_bus;
    Bus control_bus, address_bus;
} Mobo;

Mobo mobo_init(CPU *cpu, Memory *mem) {
    return (Mobo){ .cpu = cpu, .mem = mem, .address_bus = {0}, .control_bus = {0}, .data_bus = {0} };
}
void mobo_clock(Mobo *mobo);

#endif //SUPERSCALARSIMULATOR_MOBO_H
