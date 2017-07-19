//
// Created by hsart on 09/07/17.
//

#include "instructions.h"
#include "rstation.h"
#include "pipeline.h"
#include "types.h"

CPU cpu_init(Memory *mem) {
    CPU cpu = { .cache    = cache_init(mem, CACHE_SIZE),
            .inst_set = inst_init(),
            .alu      = alu_init(),
            .cdb      = {0},
            .pipeline = pipe_init()};


    for (int i = 0; i < 7; i++) {
        cpu.pipeline.rstation[i].vj = REG_COUNT;
        cpu.pipeline.rstation[i].vk = REG_COUNT;
        cpu.pipeline.rstation[i].qj = REG_COUNT;
        cpu.pipeline.rstation[i].qk = REG_COUNT;
    }

    return cpu;
}

void cpu_clock(CPU *cpu) {
    cpu->pipeline.stage[FETCH](cpu);
    cpu->pipeline.stage[DECODE](cpu);
    cpu->pipeline.stage[ISSUE](cpu);
    cpu->pipeline.stage[EXEC](cpu);
}

void cpu_reg_set(CPU *cpu, ERegisters e, int value) {
    cpu->reg[e].content.value = value;
}

int cpu_reg_get(CPU *cpu, ERegisters e) {
    return cpu->reg[e].content.value;
}

int cpu_reg_index(CPU *cpu, Register *r) {
    for (int i = 0; i < REG_COUNT; i++) {
        if (&cpu->reg[i] == r) return i;
    }
    return -1;
}

ReservationStation *cpu_reg_busy(CPU * cpu, ERegisters e) {
    return cpu->reg->rstation;
}