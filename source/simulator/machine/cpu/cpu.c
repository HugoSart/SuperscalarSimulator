//
// Created by hsart on 09/07/17.
//

#include "instructions.h"
#include "rstation.h"
#include "pipeline.h"
#include "../types.h"
#include "register.h"
#include "structures/cdb_fifo.h"
#include "../util.h"

CPU *cpu_new(Memory *mem) {

    CPU *cpu = malloc(sizeof(CPU));
    *cpu = (CPU){ .cache    = cache_init(mem, CACHE_SIZE),
            .inst_set = inst_init(),
            .alu      = alu_init(),
            .cdb      = {{0}},
            .pipeline = pipe_init(),
            .cdb = { .data = NULL, .destination = REG_UNKNOWN, .tag = RS_UNKNOWN, .busy = NOT_BUSY, .queue = cdbfifo_init()}};

    cpu->cache._p_cpu = cpu;

    return cpu;
}

void cpu_reg_set(CPU *cpu, ERegisters e, int value) {
    cpu->reg[e].content.value = value;
}

Register *cpu_reg_get(CPU *cpu, ERegisters e) {
    return &cpu->reg[e];
}

int cpu_reg_index(CPU *cpu, Register *r) {
    for (int i = 0; i < REG_COUNT; i++) {
        if (&cpu->reg[i] == r) return i;
    }
    return -1;
}

ReservationStation *cpu_rstation(CPU *cpu, ERStation e) {
    return &cpu->pipeline.rstation[e];
}

int cpu_rstation_index(CPU *cpu, ReservationStation *rstation) {
    for (int r = 0; r < RS_COUNT; r++) {
        if (cpu_rstation(cpu, r) == rstation) return r;
    }
    return RS_UNKNOWN;
}

void cpu_cdb_put(CPU *cpu, ERStation tag, ERegisters destination, Word data) {

    if (destination != REG_UNKNOWN)
        cdbfifo_add(&cpu->cdb.queue, tag, destination, data);

    if (cpu->cdb.busy == NOT_BUSY && cpu->cdb.queue.first != NULL) {
        cpu->cdb.tag = cpu->cdb.queue.first->tag;
        cpu->cdb.destination = cpu->cdb.queue.first->destination;
        cpu->cdb.data = cpu->cdb.queue.first->data;
        cpu->cdb.busy = 1;
        cdbfifo_remove(&cpu->cdb.queue);
    }

}

void cpu_cdb_write(CPU *cpu) {

    if (cpu->cdb.destination == REG_UNKNOWN) return;

    cpu_reg_get(cpu, cpu->cdb.destination)->content = cpu->cdb.data;
    cpu_reg_get(cpu, cpu->cdb.destination)->rstation = NULL;

    cpu->cdb.tag = RS_UNKNOWN;
    cpu->cdb.destination = REG_UNKNOWN;
    cpu->cdb.data.value = 0;
    cpu->cdb.busy = NOT_BUSY;

    if (cpu->cdb.busy == NOT_BUSY && cpu->cdb.queue.first != NULL) {
        cpu->cdb.tag = cpu->cdb.queue.first->tag;
        cpu->cdb.destination = cpu->cdb.queue.first->destination;
        cpu->cdb.data = cpu->cdb.queue.first->data;
        cpu->cdb.busy = 1;
        cdbfifo_remove(&cpu->cdb.queue);
    }


}

ReservationStation *cpu_reg_busy(CPU * cpu, ERegisters e) {
    return cpu->reg->rstation;
}

void cpu_clock(CPU *cpu) {
    cpu->pipeline.stage[WRITE_RESULT](cpu);
    cpu->pipeline.stage[EXEC](cpu);
    cpu->pipeline.stage[ISSUE](cpu);
    cpu->pipeline.stage[DECODE](cpu);
    cpu->pipeline.stage[FETCH](cpu);
}