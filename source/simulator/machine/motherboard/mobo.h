//
// Created by hsart on 16/07/17.
//

#ifndef SUPERSCALARSIMULATOR_MOBO_H
#define SUPERSCALARSIMULATOR_MOBO_H

#include "../memory/memory.h"
#include "../types.h"
#include "../cpu/cpu.h"

Mobo *mobo_new(CPU *cpu, Memory *mem);
void mobo_clock(Mobo *mobo);

#endif //SUPERSCALARSIMULATOR_MOBO_H
