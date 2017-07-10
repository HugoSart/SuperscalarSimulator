//
// Created by hsart on 09/07/17.
//

#ifndef SUPERSCALARSIMULATOR_CPU_H
#define SUPERSCALARSIMULATOR_CPU_H

#include "instructions.h"
#include "cache.h"
#include "registers.h"

typedef struct {
    Cache cache;
    ALU alu;
    RegistersSet reg_set;

    InstructionSet inst_set;
} CPU;

CPU cpu_init(Memory *mem);
void cpu_exec(CPU *, EInstructions, ...);

#endif //SUPERSCALARSIMULATOR_CPU_H
