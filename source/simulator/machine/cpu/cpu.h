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
void cpu_clock(CPU *);
void cpu_exec(CPU *, EInstructions, ...);
void cpu_reg_set(CPU *, ERegisters, int value);
Register *cpu_reg_get(CPU *, ERegisters);
ReservationStation *cpu_rstation(CPU *, ERStation);
int cpu_rstation_index(CPU *cpu, ReservationStation *);
int cpu_reg_index(CPU *cpu, Register *);
ReservationStation *cpu_reg_busy(CPU *, ERegisters);

void cpu_cdb_put(CPU *cpu, ERStation tag, ERegisters destination, Word data);
void cpu_cdb_write(CPU *cpu);

#endif //SUPERSCALARSIMULATOR_CPU_H
