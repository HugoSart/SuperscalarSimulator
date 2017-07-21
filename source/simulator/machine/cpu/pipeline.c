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
    } else if (e == TYPE_LOAD || e == TYPE_ACUMULATOR || e == TYPE_STORE) {
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

// Funfando
void pipe_fetch(CPU *cpu) {

    cpu->pipeline.ri = mem_read_word(cpu->cache.mem, cpu->pipeline.pc.decimal);
    if (cpu->pipeline.ri.value == EOF) return;
    cpu->pipeline.pc.decimal += WORD_SIZE;

}

// Semi-Funfando mas funfando
void pipe_decode(CPU *cpu) {

    Opcode opcode = { .opcode = cpu->pipeline.ri.decimal };
    ERType type = RTYPE_UNKNOWN;

    if (cpu->pipeline.ri.value == EOF) return;

    size_t m = 0, n = 0;
    if      (opcode.r.op == 0x00) { m = COLUMN_FUNCT1; type = RTYPE_R;  }
    else if (opcode.r.op == 0x1c) { m = COLUMN_FUNCT2; type = RTYPE_R;  }
    else if (opcode.r.op == 0x01) { m = COLUMN_RT;     type = RTYPE_RI; }

    if      (m == COLUMN_FUNCT1 || m == COLUMN_FUNCT2) n = opcode.r.func;
    else if (m == COLUMN_RT)                           n = opcode.r.rt;
    else                                               n = opcode.r.op;

    if (opcode.opcode == 0)
        fifo_add(&cpu->pipeline.queue, opcode, type, &cpu->inst_set.table[COLUMN_FUNCT2][63]);
    else
        fifo_add(&cpu->pipeline.queue, opcode, type, &cpu->inst_set.table[m][n]);
    //ref.realization(cpu, opcode.opcode);
    //instruction(cpu, cpu->pipeline.ri.decimal);

}

// Funfando
void pipe_issue(CPU *cpu) {

    if (cpu->pipeline.queue.first == NULL) return;

    Instruction *instruction = &cpu->pipeline.queue.first->instruction;

    if (instruction == NULL) return;
    if (instruction->code.opcode == 0) {
        fifo_remove(&cpu->pipeline.queue);
        return;
    }

    Register *rs = cpu_reg_get(cpu, (ERegisters)instruction->code.r.rs),
            *rt = cpu_reg_get(cpu, (ERegisters)instruction->code.r.rt),
            *rd = cpu_reg_get(cpu, (ERegisters)instruction->code.r.rd);
    int imm = instruction->code.ri.imm;

    // TODO: Descobrir o que acontece com FP Operation com immediato

    for (unsigned int r = 0; r < RS_COUNT; r++) {

        if (cpu_rstation(cpu, (ERStation)r)->type != check_type(instruction->ref->type)) continue;
        if (cpu_rstation(cpu, (ERStation)r)->busy != NOT_BUSY)                           continue;

        if (cpu_rstation(cpu, (ERStation)r)->type != RS_TYPE_LOAD) {

            if (rs->rstation != NULL) {
                cpu_rstation(cpu, (ERStation) r)->qj = cpu_rstation_index(cpu, rs->rstation);
            } else {
                cpu_rstation(cpu, (ERStation) r)->vj = cpu_reg_index(cpu, rs);
                cpu_rstation(cpu, (ERStation) r)->qj = REG_UNKNOWN;
            }

            if (rt->rstation != NULL) {
                cpu_rstation(cpu, (ERStation) r)->qk = cpu_rstation_index(cpu, rt->rstation);
            } else {
                cpu_rstation(cpu, (ERStation) r)->vk = cpu_reg_index(cpu, rt);
                cpu_rstation(cpu, (ERStation) r)->qk = REG_UNKNOWN;
            }

            cpu_rstation(cpu, (ERStation) r)->busy = clock(instruction->ref->type);
            rd->rstation = cpu_rstation(cpu, (ERStation) r);

        } else {

            if (rs->rstation != NULL) {
                cpu_rstation(cpu, (ERStation) r)->qj = cpu_rstation_index(cpu, rs->rstation);
            } else {
                cpu_rstation(cpu, (ERStation) r)->vj = cpu_reg_index(cpu, rs);
                cpu_rstation(cpu, (ERStation) r)->qj = REG_UNKNOWN;
            }

            cpu_rstation(cpu, (ERStation)r)->A = imm;

            if (instruction->ref->type == TYPE_LOAD) {
                rt->rstation = cpu_rstation(cpu, (ERStation)r);
            } else {
                if (rt->rstation != NULL) {
                    cpu_rstation(cpu, (ERStation)r)->qk = cpu_rstation_index(cpu, rs->rstation);
                } else {
                    cpu_rstation(cpu, (ERStation)r)->vk = cpu_reg_index(cpu, rt);
                    cpu_rstation(cpu, (ERStation)r)->qk = REG_UNKNOWN;
                }
            }

        }

        cpu_rstation(cpu, (ERStation)r)->instruction = fifo_remove(&cpu->pipeline.queue);
        cpu_rstation(cpu, (ERStation)r)->busy = clock(instruction->ref->type);
        break;

    }

}

void pipe_exec(CPU *cpu) {

    for (int r = 0; r < RS_COUNT; r++) {

        if (cpu_rstation(cpu, (ERStation)r)->qj == REG_UNKNOWN && cpu_rstation(cpu, (ERStation)r)->qk == REG_UNKNOWN) {

            if (cpu_rstation(cpu, (ERStation)r)->busy == 1) {
                cpu_rstation(cpu, (ERStation) r)->instruction.ref->realization(cpu, cpu_rstation(cpu, (ERStation) r));
                cpu_rstation(cpu, (ERStation) r)->busy--;
            } else if (cpu_rstation(cpu, (ERStation)r)->busy > 0) {
                cpu_rstation(cpu, (ERStation) r)->busy--;
            }

        }

        // TODO: Implementar Load/Store Step 1
        // TODO: Implementar Load Step 2

    }

}

void pipe_write_result(CPU *cpu) {

    for (int r = 0; r < RS_COUNT; r++) {
        if (cpu_rstation(cpu, (ERStation)r)->busy == 0) {
            for (int x = 0; x < REG_COUNT; x++) {
                if (cpu_reg_get(cpu, x)->rstation == cpu_rstation(cpu, r)) {
                    printf("Value: %d\n", cpu_rstation(cpu, r)->buffer.content.value);
                    cpu_reg_get(cpu, x)->content.value = cpu_rstation(cpu, r)->buffer.content.value;
                    cpu_reg_get(cpu, x)->rstation = NULL;
                }
            }
            for (int x = 0; x < REG_COUNT; x++) {
                if (cpu_rstation(cpu, x)->qj == r) {
                    cpu_rstation(cpu, x)->vj = cpu_rstation(cpu, r)->buffer.content.value;
                    cpu_rstation(cpu, x)->qj = REG_UNKNOWN;
                }
            }
            for (int x = 0; x < REG_COUNT; x++) {
                if (cpu_rstation(cpu, x)->qk == r) {
                    cpu_rstation(cpu, x)->vk = cpu_rstation(cpu, r)->buffer.content.value;
                    cpu_rstation(cpu, x)->qk = REG_UNKNOWN;
                }
            }
            rstation_clean(cpu_rstation(cpu, r));
        }
    }

    // TODO: Implementar Store

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

    for (int i = 0; i < RS_COUNT; i++) {

        if      (i < 3) pipeline.rstation[i].type = RS_TYPE_ADD;
        else if (i < 5) pipeline.rstation[i].type = RS_TYPE_MUL;
        else if (i < 7) pipeline.rstation[i].type = RS_TYPE_LOAD;
        else            pipeline.rstation[i].type = RS_TYPE_UNKNOWN;

        pipeline.rstation[i].busy = NOT_BUSY;
        pipeline.rstation[i].buffer.rstation = NULL;

    }

    return pipeline;
}
