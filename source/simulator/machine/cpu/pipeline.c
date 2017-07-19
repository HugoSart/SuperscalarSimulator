//
// Created by hsart on 10/07/17.
//

#include "types.h"
#include "structures/fifo.h"
#include "cache.h"
#include "instructions.h"
#include "cpu.h"
#include "register.h"

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
        if (rstation == cpu->pipeline.rstation) {
            return i;
        }
    }
    return -1;
}

void pipe_fetch(CPU *cpu) {

    cpu->pipeline.ri = mem_read_word(cpu->cache.mem, cpu->pipeline.pc.decimal);
    cpu->pipeline.pc.decimal += WORD_SIZE;

}

void pipe_decode(CPU *cpu) {

    Opcode opcode = { .opcode = cpu->pipeline.ri.decimal };
    ERType type = RTYPE_UNKNOWN;
    printf("OPCODE: %d\n", opcode.opcode);
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
        if (check_type(instruction->ref->type) == RS_ADD && cpu->pipeline.rstation[i].type == check_type(instruction->ref->type)) {
            if (cpu->pipeline.rstation[i].busy == 0) {
                cpu->pipeline.rstation[i].op = instruction->ref;
                if (cpu->reg[instruction->code.r.rs].rstation != NULL)
                    cpu->pipeline.rstation[i].qj = rstation_index(cpu, cpu->reg[instruction->code.r.rs].rstation);
                else {
                    cpu->pipeline.rstation[i].vj = cpu_reg_index(cpu, &cpu->reg[instruction->code.r.rs]);
                    cpu->pipeline.rstation[i].qj = REG_UNKNOWN;
                }
                if (cpu->reg[instruction->code.r.rt].rstation != NULL)
                    cpu->pipeline.rstation[i].qk = rstation_index(cpu, cpu->reg[instruction->code.r.rt].rstation);
                else {
                    cpu->pipeline.rstation[i].vk = cpu_reg_index(cpu, &cpu->reg[instruction->code.r.rt]);
                    cpu->pipeline.rstation[i].qk = REG_UNKNOWN;
                }
                cpu->pipeline.rstation[i].busy = clock(instruction->ref->type);
                cpu->reg[instruction->code.r.rd].rstation = &cpu->pipeline.rstation[i];
                fifo_remove(&cpu->pipeline.queue);
                break;
            } else if (check_type(instruction->ref->type) == RS_ADD && cpu->pipeline.rstation[i].type == check_type(instruction->ref->type)) {

            }
        }
    }

}

void pipe_exec(CPU *cpu) {
    for (int i = 0; i < 7; i++) {
        if (cpu->pipeline.rstation[i].busy == 1) {
            if (cpu->pipeline.rstation[i].qj == REG_UNKNOWN && cpu->pipeline.rstation[i].qk == REG_UNKNOWN) {
                cpu->pipeline.rstation[i].op->realization(cpu, cpu->pipeline.rstation[i].vj, cpu->pipeline.rstation[i].vk);
            }
        } else if (cpu->pipeline.rstation[i].busy > 1) cpu->pipeline.rstation[i].busy--;
    }
}

void pipe_mem_access(CPU *cpu, unsigned int code) {

}

void pipe_write_back(CPU *cpu, unsigned int code) {

}

Pipeline pipe_init() {
    Pipeline pipeline = { .pc = {0}, .ri = {0}, .queue = fifo_init(),
            .stage[FETCH]       = &pipe_fetch,
            .stage[DECODE]      = &pipe_decode,
            .stage[ISSUE]       = &pipe_issue,
            .stage[EXEC]        = &pipe_exec,
            .stage[MEM_ACCESS]  = &pipe_mem_access,
            .stage[WRITE_BACK]  = &pipe_write_back};

    pipeline.rstation[0].type = RS_ADD;
    pipeline.rstation[1].type = RS_ADD;
    pipeline.rstation[2].type = RS_ADD;
    pipeline.rstation[3].type = RS_MUL;
    pipeline.rstation[4].type = RS_MUL;
    pipeline.rstation[5].type = RS_LOAD;
    pipeline.rstation[6].type = RS_LOAD;

    return pipeline;
}
