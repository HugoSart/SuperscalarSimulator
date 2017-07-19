//
// Created by hsart on 09/07/17.
//

#ifndef SUPERSCALARSIMULATOR_CPU_H
#define SUPERSCALARSIMULATOR_CPU_H

#include "types.h"
#include "alu.h"
#include "cache.h"
#include "instructions.h"

typedef struct cpu_t CPU;

CPU cpu_init(Memory *mem);
void cpu_exec(CPU *, EInstructions, ...);
void cpu_reg_set(CPU *, ERegisters, int value);
int cpu_reg_get(CPU *, ERegisters);
int cpu_reg_index(CPU *cpu, ERegisters);
ReservationStation *cpu_reg_busy(CPU *, ERegisters);

#endif //SUPERSCALARSIMULATOR_CPU_H
