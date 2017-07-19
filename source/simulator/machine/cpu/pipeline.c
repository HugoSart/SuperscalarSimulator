//
// Created by hsart on 10/07/17.
//

#include "types.h"
#include "structures/fifo.h"
#include "cache.h"
#include "instructions.h"
#include "cpu.h"

ERStation check_type(EType e) {
    if (e == TYPE_ARITHMETIC || e == TYPE_LOGICAL || e == TYPE_IF || e == TYPE_SHIFT || e == TYPE_JMP) {
        return RS_ADD;
    } else if (e == TYPE_MULT) {
        return RS_MUL;
    } else if (e == TYPE_LOAD || e == TYPE_ACUMULATOR) {
        return RS_LOAD;
    } else {
        return RS_UNKNOWN;
    }
}

int clock(EType e) {
    switch (e) {
        case TYPE_ARITHMETIC:   return CLOCK_ARITHMETIC;
        case TYPE_SHIFT:        return CLOCK_SHIFT;
        case TYPE_LOGICAL:      return CLOCK_LOGICAL;
        case TYPE_IF:           return CLOCK_IF;
        case TYPE_MULT:         return CLOCK_MULT;
        case TYPE_ACUMULATOR:   return CLOCK_ACUMULATOR;
        case TYPE_JMP:          return CLOCK_JMP;
        case TYPE_LOAD:         return CLOCK_LOAD;
        default:                return CLOCK_UNKNOWN;
    }
}

int rstation_index(CPU *cpu, ReservationStation *rstation) {
    for (int i = 0; i < 7; i++) {
        if (rstation == cpu->rstation) {
            return i;
        }
    }
    return -1;
}

void pipe_fetch(CPU *cpu) {

    cpu->pipeline.ri = cache_read(&cpu->cache, cpu->pipeline.pc.decimal);
    cpu->pipeline.pc.decimal += WORD_SIZE;

}

void pipe_decode(CPU *cpu) {

    Opcode opcode = { .opcode = cpu->pipeline.ri.decimal };
    ERType type = RTYPE_UNKNOWN;

    size_t m = 0, n = 0;
    if      (opcode.r.op == 0x00) { m = COLUMN_FUNCT1; type = RTYPE_R;  }
    else if (opcode.r.op == 0x1c) { m = COLUMN_FUNCT2; type = RTYPE_R;  }
    else if (opcode.r.op == 0x01) { m = COLUMN_RT;     type = RTYPE_RI; }

    if      (m == COLUMN_FUNCT1 || m == COLUMN_FUNCT2) n = opcode.r.func;
    else if (m == COLUMN_RT)                           n = opcode.r.rt;
    else                                               n = opcode.r.op;

    fifo_add(&cpu->pipeline.queue, opcode, type, &cpu->inst_set.table[m][n]);
    fifo_print(&cpu->pipeline.queue);
    //ref.realization(cpu, opcode.opcode);
    //instruction(cpu, cpu->pipeline.ri.decimal);

}

void pipe_issue(CPU *cpu) {

    Instruction *instruction = &cpu->pipeline.queue.first->instruction;
    for (unsigned int i = 0; i < 7; i++) {
        if (cpu->rstation[i].type == check_type(instruction->ref->type)) {
            if (cpu->rstation[i].busy == 0) {
                if (cpu->reg[instruction->code.r.rs].rstation != NULL)
                    cpu->rstation[i].qj = rstation_index(cpu, cpu->reg[instruction->code.r.rs].rstation);
                else
                    cpu->rstation[i].vj = cpu_reg_index(cpu, &cpu->reg[instruction->code.r.rs]);
                if (cpu->reg[instruction->code.r.rt].rstation != NULL)
                    cpu->rstation[i].qj = rstation_index(cpu, cpu->reg[instruction->code.r.rs].rstation);
                else
                    cpu->rstation[i].vj = cpu_reg_index(cpu, &cpu->reg[instruction->code.r.rs]);
            }
        }
    }

}

void pipe_exec(CPU *cpu, unsigned int code) {

}

void pipe_mem_access(CPU *cpu, unsigned int code) {

}

void pipe_write_back(CPU *cpu, unsigned int code) {

}

Pipeline pipe_init() {
    Pipeline pipeline = { .pc = {0}, .ri = {0}, .queue = fifo_init(),
            .stage[FETCH]       = &pipe_fetch,
            .stage[DECODE]      = &pipe_decode,
            .stage[EXEC]        = &pipe_exec,
            .stage[MEM_ACCESS]  = &pipe_mem_access,
            .stage[WRITE_BACK]  = &pipe_write_back};
    return pipeline;
}
