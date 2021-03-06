//
// Created by hsart on 16/07/17.
//

#include "../types.h"
#include "../util.h"
#include "rstation.h"
#include "cpu.h"
#include "structures/cdb_fifo.h"

int rstation_index(CPU *cpu, ReservationStation *rstation) {
    for (int i = 0; i < RS_COUNT; i++) {
        if (rstation == &cpu->pipeline.rstation[i]) {
            return i;
        }
    }
    return RS_UNKNOWN;
}

void rstation_clean(CPU *cpu, ReservationStation *rstation) {

    rstation->busy = NOT_BUSY;
    rstation->vk = 0;
    rstation->vj = 0;
    rstation->qk = RS_UNKNOWN;
    rstation->qj = RS_UNKNOWN;
    rstation->result.content.value = 0;
    rstation->result.validation = 1;
    rstation->instruction.ref = NULL;
    rstation->instruction.code.opcode = 0;
    rstation->instruction.rtype = RTYPE_UNKNOWN;
    rstation->A = 0;

}