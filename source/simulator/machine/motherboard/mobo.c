//
// Created by hsart on 16/07/17.
//

#include "mobo.h"
#include "../cpu/rstation.h"

Mobo *mobo_new(CPU *cpu, Memory *mem) {
    Mobo *mobo = malloc(sizeof(Mobo));
    *mobo = (Mobo){ .cpu = cpu, .mem = mem,
        .address_bus.busy = NOT_BUSY, .address_bus.data.value = 0,
        .control_bus.busy = NOT_BUSY, .control_bus.data.value = 0,
        .data_bus.busy = NOT_BUSY, .data_bus.data = {{0}} };
    cpu->_p_mobo = mobo;
    mem->_p_mobo = mobo;
    return mobo;
}

void mobo_clock(Mobo *mobo) {
    cpu_clock(mobo->cpu);
    mem_clock(mobo->mem);
}