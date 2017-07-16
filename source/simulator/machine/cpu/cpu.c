//
// Created by hsart on 09/07/17.
//

#include "instructions.h"
#include "pipeline.h"
#include "../util.h"

CPU cpu_init(Memory *mem) {
    CPU cpu = { .cache    = cache_init(mem, CACHE_SIZE),
                .inst_set = inst_init(),
                .reg      = {{0}},
                .alu      = alu_init(),
                .cdb      = {0},
                .pipeline = pipe_init()};
    return cpu;
}

void cpu_clock(CPU *cpu) {

}

void cpu_reg_set(CPU *cpu, ERegisters e, int value) {
    cpu->reg[e].content.value = value;
}

int cpu_reg_get(CPU *cpu, ERegisters e) {
    return cpu->reg[e].content.value;
}

ReservationStation *cpu_reg_busy(CPU * cpu, ERegisters e) {
    return cpu->reg->rstation;
}