//
// Created by hsart on 10/07/17.
//

#include <string.h>
#include "../types.h"
#include "structures/inst_fifo.h"
#include "cache.h"
#include "instructions.h"
#include "cpu.h"
#include "register.h"
#include "../util.h"
#include "rstation.h"
#include "../../system/system.h"

ERStationType check_type(EType e) {
    if (e == TYPE_ARITHMETIC || e == TYPE_LOGICAL || e == TYPE_IF || e == TYPE_SHIFT || e == TYPE_JMP || e == TYPE_BRANCH || e == TYPE_UNKNOWN) {
        return RS_TYPE_ADD;
    } else if (e == TYPE_MULT) {
        return RS_TYPE_MUL;
    } else if (e == TYPE_LOAD || e == TYPE_ACUMULATOR) {
        return RS_TYPE_LOAD;
    } else if (e == TYPE_STORE) {
        return RS_TYPE_STORE;
    } else {
        return RS_TYPE_UNKNOWN;
    }
}

int clock(EType e) {
    switch (e) {
        case TYPE_ARITHMETIC:
            return CLOCK_ARITHMETIC;
        case TYPE_SHIFT:
            return CLOCK_SHIFT;
        case TYPE_LOGICAL:
            return CLOCK_LOGICAL;
        case TYPE_IF:
            return CLOCK_IF;
        case TYPE_MULT:
            return CLOCK_MULT;
        case TYPE_ACUMULATOR:
            return CLOCK_ACUMULATOR;
        case TYPE_JMP:
            return CLOCK_JMP;
        case TYPE_BRANCH:
            return CLOCK_BRANCH;
        case TYPE_LOAD:
            return CLOCK_LOAD;
        case TYPE_STORE:
            return CLOCK_LOAD;
        default:
            return CLOCK_UNKNOWN;
    }
}

int reg_waiting(CPU *cpu, ReservationStation *rs) {

    for (int i = 0; i < REG_COUNT; i++) {
        if (cpu_reg_get(cpu, i)->rstation == rs)
            return i;
    }

    return REG_UNKNOWN;

}

// Funfando
void pipe_fetch(CPU *cpu) {

    if (cpu->pipeline.issue == ISSUE_STOP) return;

    cpu->pipeline.ri = cache_read(&cpu->cache, cpu->pipeline.pc.decimal);
    if (cpu->pipeline.ri.value == EOF) return;
    cpu->pipeline.pc.decimal += WORD_SIZE;

}

// Semi-Funfando mas funfando
void pipe_decode(CPU *cpu) {

    if (cpu->pipeline.issue == ISSUE_STOP) return;
    if (cpu->pipeline.ri.value == EOF) return;

    Opcode opcode = {.opcode = cpu->pipeline.ri.decimal};
    ERType type = RTYPE_UNKNOWN;

    size_t m = 0, n = 0;
    if (opcode.r.op == 0x00) {
        m = COLUMN_FUNCT1;
        type = RTYPE_R;
    }
    else if (opcode.r.op == 0x1c) {
        m = COLUMN_FUNCT2;
        type = RTYPE_R;
    }
    else if (opcode.r.op == 0x01) {
        m = COLUMN_RT;
        type = RTYPE_RT;
    }
    else if (opcode.r.op == 2 || opcode.r.op == 3) type = RTYPE_J;
    else if (opcode.r.op == 4) type = RTYPE_RI;
    else type = RTYPE_RI;

    if (m == COLUMN_FUNCT1 || m == COLUMN_FUNCT2) n = opcode.r.func;
    else if (m == COLUMN_RT) n = opcode.r.rt;
    else n = opcode.r.op;

    if (opcode.opcode == 0)
        ififo_add(&cpu->pipeline.queue, opcode, type, &cpu->inst_set.table[COLUMN_FUNCT2][63]);
    else
        ififo_add(&cpu->pipeline.queue, opcode, type, &cpu->inst_set.table[m][n]);

    if (cpu->inst_set.table[m][n].type == TYPE_JMP || cpu->inst_set.table[m][n].type == TYPE_BRANCH || cpu->inst_set.table[m][n].type == TYPE_UNKNOWN)
        cpu->pipeline.issue = ISSUE_STOP;

    cpu->pipeline.ri.value = EOF;
    //ref.realization(cpu, opcode.opcode);
    //instruction(cpu, cpu->pipeline.ri.decimal);

}

// Funfando
void pipe_issue(CPU *cpu) {

    if (cpu->pipeline.queue.first == NULL) return;

    Instruction *instruction = &cpu->pipeline.queue.first->instruction;

    if (instruction == NULL) return;
    if (instruction->code.opcode == 0) {
        ififo_remove(&cpu->pipeline.queue);
        return;
    }

    if (instruction->ref->type == TYPE_JMP || instruction->ref->type == TYPE_STORE) {
        cpu->pipeline.issue = ISSUE_STOP;
    }

    if (instruction->code.opcode == 0xC && false) {
        cpu->inst_set.table[COLUMN_FUNCT1][12].realization(cpu, NULL);
        ififo_remove(&cpu->pipeline.queue);
        return;
    }

    int op = instruction->code.r.op,
        funct = instruction->code.r.func;

    Register *rs = cpu_reg_get(cpu, (ERegisters) instruction->code.r.rs),
            *rt = cpu_reg_get(cpu, (ERegisters) instruction->code.r.rt),
            *rd = cpu_reg_get(cpu, (ERegisters) instruction->code.r.rd),
            *lo = cpu_reg_get(cpu, LO),
            *hi = cpu_reg_get(cpu, HI);
    int imm = instruction->code.ri.imm,
            shamt = instruction->code.r.z,
            target = instruction->code.j.target;

    // TODO: Descobrir o que acontece com FP Operation com immediato

    for (unsigned int r = 0; r < RS_COUNT; r++) {

        ReservationStation *rstation = cpu_rstation(cpu, (ERStation) r);

        if (rstation->type != check_type(instruction->ref->type)) continue;
        if (rstation->busy != NOT_BUSY) continue;

        if (instruction->ref->type == TYPE_MULT) {

            if (rs->rstation != NULL) {
                rstation->qj = cpu_rstation_index(cpu, rs->rstation);
            } else {
                rstation->vj = rs->content.value;
                rstation->qj = RS_UNKNOWN;
            }

            if (rt->rstation != NULL) {
                rstation->qk = cpu_rstation_index(cpu, rt->rstation);
            } else {
                rstation->vk = rt->content.value;
                rstation->qk = RS_UNKNOWN;
            }

            // Apenas mul possuí destino de escrita
            if (!strcmp(instruction->ref->mnemonic, "mul")) {
                rd->rstation = rstation;
            } else {
                hi->rstation = rstation;
                lo->rstation = rstation;
            }


        } else if (instruction->ref->type == TYPE_ACUMULATOR) {

            // mf?? (MoveFrom...)
            if (funct % 2 == 0) {

                Register *aux = (funct == 0x10) ? hi : lo;

                if (aux->rstation != NULL) {
                    rstation->qj = cpu_rstation_index(cpu, aux->rstation);
                } else {
                    rstation->vj = aux->content.value;
                    rstation->qj = RS_UNKNOWN;
                }

                rd->rstation = rstation;

            } else {

                Register *aux = (funct == 0x11) ? hi : lo;
                aux->rstation = rstation;

                if (rs->rstation != NULL) {
                    rstation->qj = cpu_rstation_index(cpu, rs->rstation);
                } else {
                    rstation->vj = rs->content.value;
                    rstation->qj = RS_UNKNOWN;
                }

            }

        } else if (instruction->ref->type == TYPE_BRANCH) {

            if (rs->rstation != NULL) {
                rstation->qj = cpu_rstation_index(cpu, rs->rstation);
            } else {
                rstation->vj = rs->content.value;
                rstation->qj = RS_UNKNOWN;
            }

            // Apenas beq e bne usam dois registradores
            if (rt->rstation != NULL && (!strcmp(instruction->ref->mnemonic, "beq") || !strcmp(instruction->ref->mnemonic, "bne"))) {
                rstation->qk = cpu_rstation_index(cpu, rt->rstation);
            } else {
                rstation->vk = rt->content.value;
                rstation->qk = RS_UNKNOWN;
            }

            rstation->A = imm;

        } else if (instruction->ref->type == TYPE_JMP) {

            // Verifica se é jr ou jalr
            if (op == 0 && funct >= 8) {

                if (rs->rstation != NULL) {
                    rstation->qj = cpu_rstation_index(cpu, rs->rstation);
                } else {
                    rstation->vj = rs->content.value;
                    rstation->qj = RS_UNKNOWN;
                }

                // Verifica se é jalr
                if (funct == 9) cpu_reg_get(cpu, RA)->rstation = rstation;

            } else {

                // Verifica se é jal
                if (op == 3) cpu_reg_get(cpu, RA)->rstation = rstation;

                rstation->A = target;
            }

        } else if (instruction->ref->type == TYPE_SHIFT) {

            if (rt->rstation != NULL) {
                rstation->qk = cpu_rstation_index(cpu, rt->rstation);
            } else {
                rstation->vk = rt->content.value;
                rstation->qk = RS_UNKNOWN;
            }

            // Tem shamt
            if (funct <= 3) {
                rstation->A = shamt;
            } else {
                if (rs->rstation != NULL) {
                    rstation->qj = cpu_rstation_index(cpu, rs->rstation);
                } else {
                    rstation->vj = rs->content.value;
                    rstation->qj = RS_UNKNOWN;
                }
            }

            rd->rstation = rstation;

        } else if (instruction->ref->type == TYPE_ARITHMETIC || instruction->ref->type == TYPE_LOGICAL || instruction->ref->type == TYPE_IF) {

            // Todos usam rs como valor
            if (rs->rstation != NULL) {
                rstation->qj = cpu_rstation_index(cpu, rs->rstation);
            } else {
                rstation->vj = rs->content.value;
                rstation->qj = RS_UNKNOWN;
            }

            // RI usa rt como retorno
            if (instruction->rtype == RTYPE_RI) {

                rstation->A = imm;

                rt->rstation = rstation;

            } else {

                if (rt->rstation != NULL) {
                    rstation->qk = cpu_rstation_index(cpu, rt->rstation);
                } else {
                    rstation->vk = rt->content.value;
                    rstation->qk = RS_UNKNOWN;
                }

                rd->rstation = rstation;

            }

        } else if (instruction->ref->type == TYPE_LOAD || instruction->ref->type == TYPE_STORE) {

            if (rs->rstation != NULL) {
                rstation->qj = cpu_rstation_index(cpu, rs->rstation);
            } else {
                rstation->vj = rs->content.value;
                rstation->qj = RS_UNKNOWN;
            }

            rstation->A = imm;

            if (instruction->ref->type == TYPE_LOAD)
                rt->rstation = rstation;
            else { // Store ONLY

                if (rt->rstation != NULL) {
                    rstation->qk = cpu_rstation_index(cpu, rt->rstation);
                } else {
                    rstation->vk = rt->content.value;
                    rstation->qk = RS_UNKNOWN;
                }

            }

        } else { // Syscall, usa valor em v0

            Register *v0 = cpu_reg_get(cpu, V0);

            if (v0->rstation != NULL) {
                rstation->qj = cpu_rstation_index(cpu, v0->rstation);
            } else {
                rstation->vj = v0->content.value;
                rstation->qj = RS_UNKNOWN;
            }

        }

        /** else if (cpu_rstation(cpu, (ERStation) r)->type != RS_TYPE_LOAD &&
                   cpu_rstation(cpu, (ERStation) r)->type != RS_TYPE_STORE && instruction->rtype != RTYPE_RI &&
                   instruction->rtype != RTYPE_RT) {

            if (!strcmp(instruction->ref->mnemonic, "j") || !strcmp(instruction->ref->mnemonic, "jal")) {
                cpu_rstation(cpu, (ERStation) r)->A = instruction->code.j.target;
                if (!strcmp(instruction->ref->mnemonic, "jal")) {
                    cpu_reg_get(cpu, RA)->rstation = cpu_rstation(cpu, r);
                }
            } else {

                if (rs->rstation != NULL) {
                    cpu_rstation(cpu, (ERStation) r)->qj = cpu_rstation_index(cpu, rs->rstation);
                } else {
                    if (!strcmp(instruction->ref->mnemonic, "sll") || !strcmp(instruction->ref->mnemonic, "sra") ||
                        !strcmp(instruction->ref->mnemonic, "srl"))
                        cpu_rstation(cpu, (ERStation) r)->vj = shamt;
                    else cpu_rstation(cpu, (ERStation) r)->vj = rs->content.value;
                    cpu_rstation(cpu, (ERStation) r)->qj = REG_UNKNOWN;
                }

                if (strcmp(instruction->ref->mnemonic, "jr") != 0) {

                    if (rt->rstation != NULL && !strcmp(instruction->ref->mnemonic, "j")) {
                        cpu_rstation(cpu, (ERStation) r)->qk = cpu_rstation_index(cpu, rt->rstation);
                    } else {
                        cpu_rstation(cpu, (ERStation) r)->vk = rt->content.value;
                        cpu_rstation(cpu, (ERStation) r)->qk = REG_UNKNOWN;
                    }

                    rd->rstation = cpu_rstation(cpu, (ERStation) r);
                }

            }

        } else {
            // Load or Store (or RI)

            if (rs->rstation != NULL && 0) {
                cpu_rstation(cpu, (ERStation) r)->qj = cpu_rstation_index(cpu, rs->rstation);
            } else {
                cpu_rstation(cpu, (ERStation) r)->vj = rs->content.value;
                cpu_rstation(cpu, (ERStation) r)->qj = REG_UNKNOWN;
            }

            cpu_rstation(cpu, (ERStation) r)->A = imm;

            // Load Only (or RI)
            if ((strcmp(instruction->ref->mnemonic, "beq") && strcmp(instruction->ref->mnemonic, "bne")) &&
                instruction->ref->type != TYPE_STORE &&
                (instruction->ref->type == TYPE_LOAD || instruction->rtype == RTYPE_RI)) {
                rt->rstation = cpu_rstation(cpu, (ERStation) r);
            } else if (instruction->rtype != RTYPE_RT) { // Store Only
                if (rt->rstation != NULL) {
                    if ((!strcmp(instruction->ref->mnemonic, "beq") || !strcmp(instruction->ref->mnemonic, "bne"))) {
                        cpu_rstation(cpu, (ERStation) r)->qk = cpu_rstation_index(cpu, rt->rstation);
                    } else {
                        cpu_rstation(cpu, (ERStation) r)->qk = cpu_rstation_index(cpu, rt->rstation);
                    }
                } else {
                    cpu_rstation(cpu, (ERStation) r)->vk = rt->content.value;
                    cpu_rstation(cpu, (ERStation) r)->qk = REG_UNKNOWN;
                }
            }

        } */

        cpu_rstation(cpu, (ERStation) r)->instruction = ififo_remove(&cpu->pipeline.queue);
        cpu_rstation(cpu, (ERStation) r)->busy = clock(instruction->ref->type);
        break;

    }

}

void pipe_exec(CPU *cpu) {

    for (int r = 0; r < RS_COUNT; r++) {

        ReservationStation *rstation = cpu_rstation(cpu, (ERStation) r);

        if (rstation->qj == RS_UNKNOWN && rstation->qk == RS_UNKNOWN) {

            if (rstation->busy == 1) {

                rstation->instruction.ref->realization(cpu, rstation, &(rstation->result), rstation->vj, rstation->vk, rstation->A);

                int reg_index = reg_waiting(cpu, rstation);
                if (reg_index != REG_UNKNOWN && rstation->result.validation == 1)
                    cpu_cdb_put(cpu, (ERStation) r, (ERegisters) reg_index, rstation->result.content);
                rstation->result.validation = 1;

            }

            if (rstation->busy >= 1)rstation->busy--;

        }

    }

}

void pipe_write_result(CPU *cpu) {

    for (int r = 0; r < RS_COUNT; r++) {
        //if (cpu_rstation(cpu, (ERStation) r)->instruction.ref != NULL) printf("%s: %d\n", cpu_rstation(cpu, (ERStation) r)->instruction.ref->mnemonic, reg_waiting(cpu, r));
        if (cpu_rstation(cpu, (ERStation) r)->busy == 0) {
            for (int x = 0; x < RS_COUNT; x++) {
                if (cpu_rstation(cpu, x)->qj == r) {
                    cpu_rstation(cpu, x)->vj = cpu_rstation(cpu, r)->result.content.value;
                    cpu_rstation(cpu, x)->qj = RS_UNKNOWN;
                }
                if (cpu_rstation(cpu, x)->qk == r) {
                    cpu_rstation(cpu, x)->vk = cpu_rstation(cpu, r)->result.content.value;
                    cpu_rstation(cpu, x)->qk = RS_UNKNOWN;
                }
            }

            if (reg_waiting(cpu, cpu_rstation(cpu, (ERStation) r)) == REG_UNKNOWN) rstation_clean(cpu, cpu_rstation(cpu, r));

        }
    }

    cpu_cdb_write(cpu);

}

Pipeline pipe_init() {
    Pipeline pipeline = {.pc = {0}, .ri = {0}, .queue = ififo_init(),
            .stage[FETCH]       = &pipe_fetch,
            .stage[DECODE]      = &pipe_decode,
            .stage[ISSUE]       = &pipe_issue,
            .stage[EXEC]        = &pipe_exec,
            .stage[WRITE_RESULT]  = &pipe_write_result};

    for (int i = 0; i < RS_COUNT; i++) {

        if (i < 3) pipeline.rstation[i].type = RS_TYPE_ADD;
        else if (i < 5) pipeline.rstation[i].type = RS_TYPE_MUL;
        else if (i < 10) pipeline.rstation[i].type = RS_TYPE_LOAD;
        else if (i < 15) pipeline.rstation[i].type = RS_TYPE_STORE;
        else pipeline.rstation[i].type = RS_TYPE_UNKNOWN;

        pipeline.rstation[i].busy = NOT_BUSY;
        pipeline.rstation[i].result.validation = 1;
        pipeline.rstation[i].result.content.value = 0;
        pipeline.rstation[i].qj = RS_UNKNOWN;
        pipeline.rstation[i].qk = RS_UNKNOWN;

    }

    pipeline.issue = ISSUE_CONTINUE;

    return pipeline;
}
