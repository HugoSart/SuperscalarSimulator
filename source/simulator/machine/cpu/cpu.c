//
// Created by hsart on 09/07/17.
//

#include "instructions.h"
#include "rstation.h"
#include "pipeline.h"

CPU cpu_init(Memory *mem) {
    CPU cpu = { .cache    = cache_init(mem, CACHE_SIZE),
            .inst_set = inst_init(),
            .alu      = alu_init(),
            .cdb      = {0},
            .pipeline = pipe_init(),
            .rstation = {{0}}};
    cpu.rstation[0].type = RS_ADD;
    cpu.rstation[1].type = RS_ADD;
    cpu.rstation[2].type = RS_MUL;
    cpu.rstation[3].type = RS_LOAD;
    cpu.rstation[4].type = RS_STORE;

    for (int i = 0; i < 5; i++) {
        cpu.rstation[i].vj = RS_UNDEFINED;
        cpu.rstation[i].vk = RS_UNDEFINED;
        cpu.rstation[i].qj = RS_UNDEFINED;
        cpu.rstation[i].qk = RS_UNDEFINED;
    }

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