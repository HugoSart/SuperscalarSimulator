//
// Created by hsart on 09/07/17.
//

#ifndef SUPERSCALARSIMULATOR_CPU_H
#define SUPERSCALARSIMULATOR_CPU_H

#include "../types.h"

CPU cpu_init(Memory *mem);
void cpu_exec(CPU *, EInstructions, ...);
void cpu_set_reg(CPU *, ERegisters, int value);

#endif //SUPERSCALARSIMULATOR_CPU_H
