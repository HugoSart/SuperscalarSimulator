//
// Created by hsart on 10/07/17.
//

#include "types.h"
#include "structures/fifo.h"
#include "cache.h"
#include "instructions.h"
#include "cpu.h"
#include "register.h"
#include "../util.h"
#include "rstation.h"

ERStationType check_type(EType e) {
    if (e == TYPE_ARITHMETIC || e == TYPE_LOGICAL || e == TYPE_IF || e == TYPE_SHIFT || e == TYPE_JMP) {
        return RS_TYPE_ADD;
    } else if (e == TYPE_MULT) {
        return RS_TYPE_MUL;
    } else if (e == TYPE_LOAD || e == TYPE_ACUMULATOR) {
        return RS_TYPE_LOAD;
    } else {
        return RS_TYPE_UNKNOWN;
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

void pipe_fetch(CPU *cpu) {

    cpu->pipeline.ri = mem_read_word(cpu->cache.mem, cpu->pipeline.pc.decimal);
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
    //ref.realization(cpu, opcode.opcode);
    //instruction(cpu, cpu->pipeline.ri.decimal);

}

void pipe_issue(CPU *cpu) {
    Instruction *instruction = &cpu->pipeline.queue.first->instruction;

    if (instruction == NULL) return;
    if (instruction->code.opcode == 0) {
        fifo_remove(&cpu->pipeline.queue);
        return;
    }

    Register *rs = cpu_reg_get(cpu, (ERegisters)instruction->code.r.rs),
            *rt = cpu_reg_get(cpu, (ERegisters)instruction->code.r.rt),
            *rd = cpu_reg_get(cpu, (ERegisters)instruction->code.r.rt);

    for (unsigned int r = 0; r < 7; r++) {

        if (cpu_rstation(cpu, (ERStation)r)->type != check_type(instruction->ref->type)) continue;
        if (cpu_rstation(cpu, (ERStation)r)->busy != NOT_BUSY)                           continue;

        if (rs->rstation != NULL) {
            cpu_rstation(cpu, (ERStation)r)->qj = cpu_rstation_index(cpu, rs->rstation);
        } else {
            cpu_rstation(cpu, (ERStation)r)->vj = cpu_reg_index(cpu, rs);
            cpu_rstation(cpu, (ERStation)r)->qj = REG_UNKNOWN;
        }

        if (rt->rstation != NULL) {
            cpu_rstation(cpu, (ERStation)r)->qk = cpu_rstation_index(cpu, rt->rstation);
        } else {
            cpu_rstation(cpu, (ERStation)r)->vk = cpu_reg_index(cpu, rt);
            cpu_rstation(cpu, (ERStation)r)->qk = REG_UNKNOWN;
        }

        cpu_rstation(cpu, (ERStation)r)->busy = clock(instruction->ref->type);
        rd->rstation = cpu_rstation(cpu, (ERStation)r);

        fifo_remove(&cpu->pipeline.queue);
        break;

    }

}

void pipe_exec(CPU *cpu) {

}

void pipe_write_result(CPU *cpu) {

}

void pipe_write_back(CPU *cpu) {

}

Pipeline pipe_init() {
    Pipeline pipeline = { .pc = {0}, .ri = {0}, .queue = fifo_init(),
            .stage[FETCH]       = &pipe_fetch,
            .stage[DECODE]      = &pipe_decode,
            .stage[ISSUE]       = &pipe_issue,
            .stage[EXEC]        = &pipe_exec,
            .stage[WRITE_RESULT]  = &pipe_write_result};

    for (int i = 0; i < 7; i++) {

        if      (i < 3) pipeline.rstation[i].type = RS_TYPE_ADD;
        else if (i < 5) pipeline.rstation[i].type = RS_TYPE_MUL;
        else if (i < 7) pipeline.rstation[i].type = RS_TYPE_LOAD;

        pipeline.rstation[i].busy = NOT_BUSY;
        pipeline.rstation[i].buffer.rstation = NULL;

    }

    return pipeline;
}
