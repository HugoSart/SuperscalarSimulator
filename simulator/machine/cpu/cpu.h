//
// Created by hsart on 09/07/17.
//

#ifndef SUPERSCALARSIMULATOR_CPU_H
#define SUPERSCALARSIMULATOR_CPU_H

#include "../types.h"
#include "cache.h"

typedef enum reg_e {
    ZERO,
    AT,
    V0, V1,
    A0, A1, A2, A3,
    T0, T1, T2, T3, T4, T5, T6, T7,
    S0, S1, S2, S3, S4, S5, S6, S7,
    T8, T9,
    K0, K1,
    GP, SP,
    S8, FP = S8,
    RA,
    REG_COUNT
} ERegisters;

typedef struct cpu_t {
    Cache cache;
    ALU alu;
    Word reg[REG_COUNT];
    Pipeline pipeline;
    InstructionSet inst_set;
    Word cdb;
} CPU;

CPU cpu_init(Memory *mem);
void cpu_exec(CPU *, EInstructions, ...);
void cpu_set_reg(CPU *, ERegisters, int value);

#endif //SUPERSCALARSIMULATOR_CPU_H
