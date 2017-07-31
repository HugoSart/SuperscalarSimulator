//
// Created by hsart on 09/07/17.
//

#include <string.h>
#include "instructions.h"
#include "cpu.h"
#include "../util.h"
#include "../../system/system.h"
#include "../types.h"
#include <stdarg.h>

#define PARAM_STANDARD CPU *cpu, ...

#define INIT_ARGS va_list va; \
        va_start(va, 5); \
        ReservationStation *rs = va_arg(va, ReservationStation*); \
        RSResult *result = va_arg(va, RSResult*); \
        int vj = va_arg(va, int); \
        int vk = va_arg(va, int); \
        int A = va_arg(va, int)

// VER MOVF E BRANCHES

void inst_add(InstructionSet *, void *, char *, EType, size_t, size_t);

// Instruction implementations
void add     (PARAM_STANDARD) {
    INIT_ARGS;
    result->content.value = alu_exec(&cpu->alu, OP_ADD, vj, vk);
}
void addu    (PARAM_STANDARD) {
    INIT_ARGS;
    result->content.value = alu_exec(&cpu->alu, OP_ADDU, vj, vk);
}
void addi    (PARAM_STANDARD) {
    INIT_ARGS;
    result->content.value = alu_exec(&cpu->alu, OP_ADD, vj, A);
}
void addiu   (PARAM_STANDARD) {
    INIT_ARGS;
    result->content.value = alu_exec(&cpu->alu, OP_ADDU, vj, A);
}

void sub     (PARAM_STANDARD) {
    INIT_ARGS;
    result->content.value = alu_exec(&cpu->alu, OP_SUB, vj, vk);
}
void subu    (PARAM_STANDARD) {
    INIT_ARGS;
    result->content.value = alu_exec(&cpu->alu, OP_SUBU, vj, vk);
}

void clo     (PARAM_STANDARD) {
    INIT_ARGS;
    result->content.value = alu_exec(&cpu->alu, OP_CLO, vj, vk);
}
void clz     (PARAM_STANDARD) {
    INIT_ARGS;
    result->content.value = alu_exec(&cpu->alu, OP_CLZ, vj, vk);
}

void _div    (PARAM_STANDARD) {
    INIT_ARGS;;
    cpu_cdb_put(cpu, rstation_index(cpu, rs), LO, (Word) {.value = vj / vk});
    cpu_cdb_put(cpu, rstation_index(cpu, rs), HI, (Word) {.value = vj % vk});
}
void divu    (PARAM_STANDARD) {
    INIT_ARGS;;
    cpu_cdb_put(cpu, rstation_index(cpu, rs), LO, (Word) {.value = (unsigned int)vj / (unsigned int)vk});
    cpu_cdb_put(cpu, rstation_index(cpu, rs), HI, (Word) {.value = (unsigned int)vj % (unsigned int)vk});
}

void mul     (PARAM_STANDARD) {
    INIT_ARGS;
    result->content.value = alu_exec(&cpu->alu, OP_MULT, vj, vk);
}
void mult    (PARAM_STANDARD) {
    INIT_ARGS;
    CLOHI clohi = { .value = alu_exec(&cpu->alu, OP_MULT, vj, vk) };
    cpu_cdb_put(cpu, rstation_index(cpu, rs), LO, (Word) {.value = clohi.lohi.lo});
    cpu_cdb_put(cpu, rstation_index(cpu, rs), HI, (Word) {.value = clohi.lohi.hi});
}
void multu   (PARAM_STANDARD) {
    INIT_ARGS;
    CLOHI clohi = { .value = alu_exec(&cpu->alu, OP_MULTU, vj, vk) };
    cpu_cdb_put(cpu, rstation_index(cpu, rs), LO, (Word) {.value = clohi.lohi.lo});
    cpu_cdb_put(cpu, rstation_index(cpu, rs), HI, (Word) {.value = clohi.lohi.hi});
}

void andi    (PARAM_STANDARD) {
    INIT_ARGS;
    result->content.value = alu_exec(&cpu->alu, OP_AND, vj, A);
}
void and     (PARAM_STANDARD) {
    INIT_ARGS;
    result->content.value = alu_exec(&cpu->alu, OP_AND, vj, vk);
}
void nor     (PARAM_STANDARD) {
    INIT_ARGS;
    result->content.value = alu_exec(&cpu->alu, OP_NOR, vj, vk);
}
void or      (PARAM_STANDARD) {
    INIT_ARGS;
    result->content.value = alu_exec(&cpu->alu, OP_OR, vj, vk);
} // \/ Troquei o op e funcionou !?!?!!??!?
void ori     (PARAM_STANDARD) {
    INIT_ARGS;
    result->content.value = alu_exec(&cpu->alu, OP_OR, vj, A);
} // DANDO SEG FAULT SABE LÁ DEUS PQ, Apenas essa, que está idêntica a todas as outras, e apenas se é chamada após alguma outra
void xor     (PARAM_STANDARD) {
    INIT_ARGS;
    result->content.value = alu_exec(&cpu->alu, OP_XOR, vj, vk);
}
void xori    (PARAM_STANDARD) {
    INIT_ARGS;
    result->content.value = alu_exec(&cpu->alu, OP_XOR, vj, A);
}

void sll     (PARAM_STANDARD) {
    INIT_ARGS;
    result->content.value = alu_exec(&cpu->alu, OP_LLSHIFT, vk, vj);
}
void sllv    (PARAM_STANDARD) {
    INIT_ARGS;
    result->content.value = alu_exec(&cpu->alu, OP_LLSHIFT, vk, vj);
}
void sra     (PARAM_STANDARD) {
    INIT_ARGS;
    result->content.value = alu_exec(&cpu->alu, OP_ARSHIFT, vk, vj);
}
void srav    (PARAM_STANDARD) {
    INIT_ARGS;
    result->content.value = alu_exec(&cpu->alu, OP_ARSHIFT, vk, vj);
}
void srl     (PARAM_STANDARD) {
    INIT_ARGS;
    result->content.value = alu_exec(&cpu->alu, OP_LRSHIFT, vk, vj);
}
void srlv    (PARAM_STANDARD) {
    INIT_ARGS;
    result->content.value = alu_exec(&cpu->alu, OP_LRSHIFT, vk, vj);
}

void mfhi    (PARAM_STANDARD) {
    INIT_ARGS;
    result->content = cpu_reg_get(cpu, HI)->content;
}
void mthi    (PARAM_STANDARD) {
    INIT_ARGS;
    cpu_cdb_put(cpu, rstation_index(cpu, rs), HI, (Word){.value = vj});
    result->validation = 0;
}
void mflo    (PARAM_STANDARD) {
    INIT_ARGS;
    result->content = cpu_reg_get(cpu, LO)->content;
}
void mtlo    (PARAM_STANDARD) {
    INIT_ARGS;
    cpu_cdb_put(cpu, rstation_index(cpu, rs), LO, (Word){.value = vj});
    result->validation = 0;
}

void slt     (PARAM_STANDARD) {
    INIT_ARGS;
    result->content.value = alu_exec(&cpu->alu, OP_SMALLER, vj, vk);
}
void sltu    (PARAM_STANDARD) {
    INIT_ARGS;
    result->content.value = alu_exec(&cpu->alu, OP_USMALLER, vj, vk);
}
void slti    (PARAM_STANDARD) {
    INIT_ARGS;
    result->content.value = alu_exec(&cpu->alu, OP_SMALLER, vj, A);
}
void sltiu   (PARAM_STANDARD) {
    INIT_ARGS;
    result->content.value = alu_exec(&cpu->alu, OP_USMALLER, vj, A);
}

void j       (PARAM_STANDARD) {
    INIT_ARGS;
    cpu->pipeline.pc.value = A;
    cpu->pipeline.ri.value = EOF;
    cpu->pipeline.issue = ISSUE_CONTINUE;
}
void jr      (PARAM_STANDARD) {
    INIT_ARGS;
    cpu->pipeline.pc.value = vj;
    cpu->pipeline.ri.value = EOF;
    cpu->pipeline.issue = ISSUE_CONTINUE;
}
void jal     (PARAM_STANDARD) {
    INIT_ARGS;
    result->content.value = cpu->pipeline.pc.value;
    cpu->pipeline.pc.value = A;
    cpu->pipeline.ri.value = EOF;
    cpu->pipeline.issue = ISSUE_CONTINUE;
}
void jalr    (PARAM_STANDARD) {
    INIT_ARGS;
    result->content.value = cpu->pipeline.pc.value;
    cpu->pipeline.pc.value = vj;
    cpu->pipeline.ri.value = EOF;
    cpu->pipeline.issue = ISSUE_CONTINUE;
}

void beq     (PARAM_STANDARD) {
    INIT_ARGS;
    if (cpu->alu.operation[OP_EQUALS](vj, vk)) {
        cpu->pipeline.pc.value = A;
        cpu->pipeline.ri.value = EOF;
    }
    cpu->pipeline.issue = ISSUE_CONTINUE;
}
void bgez    (PARAM_STANDARD) {
    INIT_ARGS;
    if (cpu->alu.operation[OP_TEQUALS](vj, 0)) {
        cpu->pipeline.pc.value = A;
        cpu->pipeline.ri.value = EOF;
    }
    cpu->pipeline.issue = ISSUE_CONTINUE;
}
void bgezal  (PARAM_STANDARD) {
    INIT_ARGS;
    if (cpu->alu.operation[OP_TEQUALS](vj, 0)) {
        result->content.value = cpu->pipeline.pc.value;
        cpu->pipeline.pc.value = A;
        cpu->pipeline.ri.value = EOF;
    } else result->validation = 0;
    cpu->pipeline.issue = ISSUE_CONTINUE;
}
void bgtz    (PARAM_STANDARD) {
    INIT_ARGS;
    if (!cpu->alu.operation[OP_SEQUALS](vj, 0)) {
        cpu->pipeline.pc.value = A;
        cpu->pipeline.ri.value = EOF;
    }
    cpu->pipeline.issue = ISSUE_CONTINUE;
}
void blez    (PARAM_STANDARD) {
    INIT_ARGS;
    if (cpu->alu.operation[OP_SEQUALS](vj, 0)) {
        cpu->pipeline.pc.value = A;
        cpu->pipeline.ri.value = EOF;
    }
    cpu->pipeline.issue = ISSUE_CONTINUE;
}
void bltzal  (PARAM_STANDARD) {
    INIT_ARGS;
    if (!cpu->alu.operation[OP_TEQUALS](vj, 0)) {
        result->content.value = cpu->pipeline.pc.value;
        cpu->pipeline.pc.value = A;
        cpu->pipeline.ri.value = EOF;
    } else result->validation = 0;
    cpu->pipeline.issue = ISSUE_CONTINUE;
}
void bltz    (PARAM_STANDARD) {
    INIT_ARGS;
    if (!cpu->alu.operation[OP_TEQUALS](vj, 0)) {
        cpu->pipeline.pc.value = A;
        cpu->pipeline.ri.value = EOF;
    }
    cpu->pipeline.issue = ISSUE_CONTINUE;
}
void bne     (PARAM_STANDARD) {
    INIT_ARGS;
    if (!cpu->alu.operation[OP_EQUALS](vj, vk)) {
        cpu->pipeline.pc.value = A;
        cpu->pipeline.ri.value = EOF;
    }
    cpu->pipeline.issue = ISSUE_CONTINUE;
}

void lw      (PARAM_STANDARD) {
    INIT_ARGS;
    unsigned int address = (unsigned int)alu_exec(&cpu->alu, OP_ADD, A, vj);
    result->content = cache_read(&cpu->cache, address);
}
void sw      (PARAM_STANDARD) {
    INIT_ARGS;
    unsigned int address = (unsigned int)alu_exec(&cpu->alu, OP_ADD, A, vj);
    cache_write(&cpu->cache, address, (Word){ .value = vk } );
    result->validation = 0;
    cpu->pipeline.issue = ISSUE_CONTINUE;
}

void movn     (PARAM_STANDARD) {
    INIT_ARGS;
    result->content.value = vj;
    result->validation = alu_exec(&cpu->alu, OP_EQUALS, vk, 0);
}
void movz     (PARAM_STANDARD) {
    INIT_ARGS;
    result->content.value = vj;
    result->validation = alu_exec(&cpu->alu, OP_EQUALS, vk, 0);
}

void _break  (PARAM_STANDARD) {}
void syscall (PARAM_STANDARD) {
    INIT_ARGS;
    switch (vj) {
        case SYSCALL_PRINT_INT  : so_print_int(cpu);  break;
        case SYSCALL_READ_INT   : so_read_int(cpu);   break;
        case SYSCALL_EXIT       : so_exit(cpu);       break;
    }
    cpu->pipeline.issue = ISSUE_CONTINUE;
}
void nop     (PARAM_STANDARD) {

}

void err     (PARAM_STANDARD) {
    printf("ERROR: No such instruction.\n");
}

InstructionSet inst_init() {

    InstructionSet instructionSet = {0};

    inst_add(&instructionSet, &sll,     "sll",    TYPE_SHIFT,      COLUMN_FUNCT1, 0); //
    inst_add(&instructionSet, &srl,     "srl",    TYPE_SHIFT,      COLUMN_FUNCT1, 2);
    inst_add(&instructionSet, &sra,     "sra",    TYPE_SHIFT,      COLUMN_FUNCT1, 3);
    inst_add(&instructionSet, &sllv,    "sllv",   TYPE_SHIFT,      COLUMN_FUNCT1, 4); //
    inst_add(&instructionSet, &srlv,    "srlv",   TYPE_SHIFT,      COLUMN_FUNCT1, 6);
    inst_add(&instructionSet, &srav,    "srav",   TYPE_SHIFT,      COLUMN_FUNCT1, 7);
    inst_add(&instructionSet, &jr,      "jr",     TYPE_JMP,        COLUMN_FUNCT1, 8);
    inst_add(&instructionSet, &jalr,    "jalr",   TYPE_JMP,        COLUMN_FUNCT1, 9);
    inst_add(&instructionSet, &movn,    "movn",   TYPE_ARITHMETIC, COLUMN_FUNCT1, 11);
    inst_add(&instructionSet, &movz,    "movz",   TYPE_ARITHMETIC, COLUMN_FUNCT1, 10);
    inst_add(&instructionSet, &syscall, "syscall",TYPE_UNKNOWN,    COLUMN_FUNCT1, 12);
    inst_add(&instructionSet, &_break,  "break",  TYPE_JMP,        COLUMN_FUNCT1, 13); //
    inst_add(&instructionSet, &mfhi,    "mfhi",   TYPE_ACUMULATOR, COLUMN_FUNCT1, 16);
    inst_add(&instructionSet, &mthi,    "mthi",   TYPE_ACUMULATOR, COLUMN_FUNCT1, 17);
    inst_add(&instructionSet, &mflo,    "mflo",   TYPE_ACUMULATOR, COLUMN_FUNCT1, 18);
    inst_add(&instructionSet, &mtlo,    "mtlo",   TYPE_ACUMULATOR, COLUMN_FUNCT1, 19); //;
    inst_add(&instructionSet, &mult,    "mult",   TYPE_MULT,       COLUMN_FUNCT1, 24);
    inst_add(&instructionSet, &multu,   "multu",  TYPE_MULT,       COLUMN_FUNCT1, 25);
    inst_add(&instructionSet, &_div,    "div",    TYPE_MULT,       COLUMN_FUNCT1, 26);
    inst_add(&instructionSet, &divu,    "divu",   TYPE_MULT,       COLUMN_FUNCT1, 27); //
    inst_add(&instructionSet, &add,     "add",    TYPE_ARITHMETIC, COLUMN_FUNCT1, 32);
    inst_add(&instructionSet, &addu,    "addu",   TYPE_ARITHMETIC, COLUMN_FUNCT1, 33);
    inst_add(&instructionSet, &sub,     "sub",    TYPE_ARITHMETIC, COLUMN_FUNCT1, 34);
    inst_add(&instructionSet, &subu,    "subu",   TYPE_ARITHMETIC, COLUMN_FUNCT1, 35);
    inst_add(&instructionSet, &and,     "and",    TYPE_LOGICAL,    COLUMN_FUNCT1, 36);
    inst_add(&instructionSet, &or,      "or",     TYPE_LOGICAL,    COLUMN_FUNCT1, 37);
    inst_add(&instructionSet, &xor,     "xor",    TYPE_LOGICAL,    COLUMN_FUNCT1, 38);
    inst_add(&instructionSet, &nor,     "nor",    TYPE_LOGICAL,    COLUMN_FUNCT1, 39);
    inst_add(&instructionSet, &slt,     "slt",    TYPE_IF,         COLUMN_FUNCT1, 42);
    inst_add(&instructionSet, &sltu,    "sltu",   TYPE_IF,         COLUMN_FUNCT1, 43); //

    inst_add(&instructionSet, &mul,     "mul",    TYPE_MULT,       COLUMN_FUNCT2, 2); //
    inst_add(&instructionSet, &clz,     "clz",    TYPE_ARITHMETIC, COLUMN_FUNCT2, 32);
    inst_add(&instructionSet, &clo,     "clo",    TYPE_ARITHMETIC, COLUMN_FUNCT2, 33);

    inst_add(&instructionSet, &bltz,    "bltz",   TYPE_BRANCH,     COLUMN_RT, 0);
    inst_add(&instructionSet, &bgez,    "bgez",   TYPE_BRANCH,     COLUMN_RT, 1);
    inst_add(&instructionSet, &bltzal,  "bltzal", TYPE_BRANCH,     COLUMN_RT, 16);
    inst_add(&instructionSet, &bgezal,  "bgezal", TYPE_BRANCH,     COLUMN_RT, 17);

    inst_add(&instructionSet, &j,       "j",      TYPE_JMP,        COLUMN_OP, 2);
    inst_add(&instructionSet, &jal,     "jal",    TYPE_JMP,        COLUMN_OP, 3);
    inst_add(&instructionSet, &beq,     "beq",    TYPE_BRANCH,     COLUMN_OP, 4);
    inst_add(&instructionSet, &bne,     "bne",    TYPE_BRANCH,     COLUMN_OP, 5);
    inst_add(&instructionSet, &blez,    "blez",   TYPE_BRANCH,     COLUMN_OP, 6);
    inst_add(&instructionSet, &bgtz,    "bgtz",   TYPE_BRANCH,     COLUMN_OP, 7);
    inst_add(&instructionSet, &addi,    "addi",   TYPE_ARITHMETIC, COLUMN_OP, 8);
    inst_add(&instructionSet, &addiu,   "addiu",  TYPE_ARITHMETIC, COLUMN_OP, 9);
    inst_add(&instructionSet, &slti,    "slti",   TYPE_IF,         COLUMN_OP, 10);
    inst_add(&instructionSet, &sltiu,   "sltiu",  TYPE_IF,         COLUMN_OP, 11);
    inst_add(&instructionSet, &andi,    "andi",   TYPE_LOGICAL,    COLUMN_OP, 12);
    inst_add(&instructionSet, &ori,     "ori",    TYPE_LOGICAL,    COLUMN_OP, 63); // 13
    inst_add(&instructionSet, &xori,    "xori",   TYPE_LOGICAL,    COLUMN_OP, 14);
    inst_add(&instructionSet, &lw,      "lw",     TYPE_LOAD,       COLUMN_OP, 35);
    inst_add(&instructionSet, &sw,      "sw",     TYPE_STORE,      COLUMN_OP, 43);

    inst_add(&instructionSet, &nop,     "NOP",    TYPE_UNKNOWN,    COLUMN_FUNCT2, 63);

    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 64; j++)
            if (instructionSet.table[i][j].realization == NULL)
                inst_add(&instructionSet, &err, "ERR", TYPE_UNKNOWN, i, j);

    return instructionSet;
}

void inst_add(InstructionSet *set, void *function, char *mnemonic, EType type, size_t m, size_t n) {
    set->table[m][n].mnemonic = strdup(mnemonic);
    set->table[m][n].realization = function;
    set->table[m][n].type = type;
}
