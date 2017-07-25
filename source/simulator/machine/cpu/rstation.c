//
// Created by hsart on 16/07/17.
//

#include "../types.h"
#include "../util.h"
#include "rstation.h"
#include "cpu.h"

int rstation_index(CPU *cpu, ReservationStation *rstation) {
    for (int i = 0; i < 7; i++) {
        if (rstation == &cpu->pipeline.rstation[i]) {
            return i;
        }
    }
    return RS_UNKNOWN;
}

void rstation_clean(CPU *cpu, ReservationStation *rstation) {

    rstation->busy = NOT_BUSY;
    rstation->vk = REG_UNKNOWN;
    rstation->vj = REG_UNKNOWN;
    rstation->qk = REG_UNKNOWN;
    rstation->qj = REG_UNKNOWN;
    rstation->result.value = 0;
    rstation->instruction.ref = NULL;
    rstation->instruction.code.opcode = 0;
    rstation->instruction.rtype = RTYPE_UNKNOWN;
    rstation->A = 0;

    for (int i = 0; i < REG_COUNT; i++) {
        if (cpu_reg_get(cpu, i)->rstation == rstation)
            cpu_reg_get(cpu, i)->rstation = NULL;
    }

}