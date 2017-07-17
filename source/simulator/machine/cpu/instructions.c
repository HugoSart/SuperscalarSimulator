//
// Created by hsart on 09/07/17.
//

#include <string.h>
#include "instructions.h"
#include "cpu.h"

#define PARAM_STANDARD CPU *cpu, unsigned int opcode

// VER MOVF E BRANCHES

void inst_add(InstructionSet *set, void *, char *, size_t m, size_t n);

// Instruction implementations
void add     (PARAM_STANDARD) {
    Opcode code = {.opcode = opcode};
    cpu->cdb.value = cpu->alu.operation[OP_ADD](cpu_reg_get(cpu, code.r.rs), cpu_reg_get(cpu, code.r.rt));
    cpu_reg_set(cpu, code.r.rd, cpu->cdb.value);

}
void addu    (PARAM_STANDARD) {

}
void addi    (PARAM_STANDARD) {
    Opcode code = {.opcode = opcode};
    cpu_reg_set(cpu, code.ri.rt, cpu->alu.operation[OP_ADD](code.ri.rs, code.ri.imm));
    //cpu->reg[code.ri.rt].value = cpu->reg[code.ri.rs].value + code.ri.imm;
}
void addiu   (PARAM_STANDARD) {

}
void andi    (PARAM_STANDARD) {

}
void and     (PARAM_STANDARD) {

}
void clo     (PARAM_STANDARD) {

}
void clz     (PARAM_STANDARD) {

}
void _div    (PARAM_STANDARD) {
}
void divu    (PARAM_STANDARD) {

}
void mult    (PARAM_STANDARD) {

}
void multu   (PARAM_STANDARD) {

}
void mul     (PARAM_STANDARD) {
    Opcode code = {.opcode = opcode};
    Word *rd = &cpu->reg[code.r.rd],
            *rs = &cpu->reg[code.r.rs],
            *rt = &cpu->reg[code.r.rt];
    cpu->cdb.value = cpu->alu.operation[OP_MULT](rs->value, rt->value);
    rd->value = cpu->cdb.value;
}
void madd    (PARAM_STANDARD) {

}
void maddu   (PARAM_STANDARD) {

}
void msub    (PARAM_STANDARD) {

}
void nor     (PARAM_STANDARD) {

}
void or      (PARAM_STANDARD) {

}
void ori     (PARAM_STANDARD) {

}
void syscall (PARAM_STANDARD) {}
void sync    (PARAM_STANDARD) {}
void slr     (PARAM_STANDARD) {}
void sra     (PARAM_STANDARD) {}
void sllv    (PARAM_STANDARD) {}
void srlv    (PARAM_STANDARD) {}
void srav    (PARAM_STANDARD) {}
void jr      (PARAM_STANDARD) {}
void jalr    (PARAM_STANDARD) {}
void movz    (PARAM_STANDARD) {}
void movn    (PARAM_STANDARD) {}
void _break  (PARAM_STANDARD) {}
void mfhi    (PARAM_STANDARD) {}
void mthi    (PARAM_STANDARD) {}
void mflo    (PARAM_STANDARD) {}
void sub     (PARAM_STANDARD) {}
void subu    (PARAM_STANDARD) {}
void xor     (PARAM_STANDARD) {}
void slt     (PARAM_STANDARD) {}
void sltu    (PARAM_STANDARD) {}
void tge     (PARAM_STANDARD) {}
void tgeu    (PARAM_STANDARD) {}
void tlt     (PARAM_STANDARD) {}
void tltu    (PARAM_STANDARD) {}
void teq     (PARAM_STANDARD) {}
void tne     (PARAM_STANDARD) {}
void msubu   (PARAM_STANDARD) {}
void bltz    (PARAM_STANDARD) {}
void bgez    (PARAM_STANDARD) {}
void bltzl   (PARAM_STANDARD) {}
void bgzel   (PARAM_STANDARD) {}
void tgei    (PARAM_STANDARD) {}
void tgeiu   (PARAM_STANDARD) {}
void tlti    (PARAM_STANDARD) {}
void tltiu   (PARAM_STANDARD) {}
void tegi    (PARAM_STANDARD) {}
void tnei    (PARAM_STANDARD) {}
void bltzal  (PARAM_STANDARD) {}
void bgezal  (PARAM_STANDARD) {}
void bltzall (PARAM_STANDARD) {}
void bgczall (PARAM_STANDARD) {}
void j       (PARAM_STANDARD) {}
void jal     (PARAM_STANDARD) {}
void beq     (PARAM_STANDARD) {}
void bne     (PARAM_STANDARD) {}
void blez    (PARAM_STANDARD) {}
void bgtz    (PARAM_STANDARD) {}
void slti    (PARAM_STANDARD) {}
void sltiu   (PARAM_STANDARD) {}
void xori    (PARAM_STANDARD) {}
void lui     (PARAM_STANDARD) {}
void sll     (PARAM_STANDARD) {}
void benql   (PARAM_STANDARD) {}
void bnel    (PARAM_STANDARD) {}
void blezl   (PARAM_STANDARD) {}
void bgtzl   (PARAM_STANDARD) {}
void lb      (PARAM_STANDARD) {}
void lh      (PARAM_STANDARD) {}
void lwl     (PARAM_STANDARD) {}
void lw      (PARAM_STANDARD) {
    Opcode code = {.opcode = opcode};
    cpu_reg_set(cpu, code.ri.rt, mem_read_word(cpu->cache.mem, code.ri.imm).value);
}

void err     (PARAM_STANDARD) {
    printf("ERROR: No such instruction.\n");
}

InstructionSet inst_init() {

    InstructionSet instructionSet = {0};

    inst_add(&instructionSet, &sll,     "sll",    COLUMN_FUNCT1, 0); //
    inst_add(&instructionSet, &slr,     "slr",    COLUMN_FUNCT1, 2);
    inst_add(&instructionSet, &sra,     "sra",    COLUMN_FUNCT1, 3);
    inst_add(&instructionSet, &sllv,    "sllv",   COLUMN_FUNCT1, 4); //
    inst_add(&instructionSet, &srlv,    "srlv",   COLUMN_FUNCT1, 6);
    inst_add(&instructionSet, &srav,    "srav",   COLUMN_FUNCT1, 7);
    inst_add(&instructionSet, &jr,      "jr",     COLUMN_FUNCT1, 8);
    inst_add(&instructionSet, &jalr,    "jalr",   COLUMN_FUNCT1, 9);
    inst_add(&instructionSet, &movz,    "movz",   COLUMN_FUNCT1, 10);
    inst_add(&instructionSet, &movn,    "movn",   COLUMN_FUNCT1, 11);
    inst_add(&instructionSet, &syscall, "syscall",COLUMN_FUNCT1, 12);
    inst_add(&instructionSet, &_break,  "break",  COLUMN_FUNCT1, 13); //
    inst_add(&instructionSet, &sync,    "sync",   COLUMN_FUNCT1, 16);
    inst_add(&instructionSet, &mfhi,    "mfhi",   COLUMN_FUNCT1, 17);
    inst_add(&instructionSet, &mthi,    "mthi",   COLUMN_FUNCT1, 18);
    inst_add(&instructionSet, &mflo,    "mflo",   COLUMN_FUNCT1, 19); //;
    inst_add(&instructionSet, &mult,    "mult",   COLUMN_FUNCT1, 24);
    inst_add(&instructionSet, &multu,   "multu",  COLUMN_FUNCT1, 25);
    inst_add(&instructionSet, &div,     "div",    COLUMN_FUNCT1, 26);
    inst_add(&instructionSet, &divu,    "divu",   COLUMN_FUNCT1, 27); //
    inst_add(&instructionSet, &add,     "add",    COLUMN_FUNCT1, 32);
    inst_add(&instructionSet, &addu,    "addu",   COLUMN_FUNCT1, 33);
    inst_add(&instructionSet, &sub,     "sub",    COLUMN_FUNCT1, 34);
    inst_add(&instructionSet, &subu,    "subu",   COLUMN_FUNCT1, 35);
    inst_add(&instructionSet, &and,     "and",    COLUMN_FUNCT1, 36);
    inst_add(&instructionSet, &or,      "or",     COLUMN_FUNCT1, 37);
    inst_add(&instructionSet, &xor,     "xor",    COLUMN_FUNCT1, 38);
    inst_add(&instructionSet, &nor,     "nor",    COLUMN_FUNCT1, 39);
    inst_add(&instructionSet, &slt,     "slt",    COLUMN_FUNCT1, 42);
    inst_add(&instructionSet, &sltu,    "sltu",   COLUMN_FUNCT1, 43); //
    inst_add(&instructionSet, &tge,     "tge",    COLUMN_FUNCT1, 48);
    inst_add(&instructionSet, &tgeu,    "tgeu",   COLUMN_FUNCT1, 49);
    inst_add(&instructionSet, &tlt,     "tlt",    COLUMN_FUNCT1, 50);
    inst_add(&instructionSet, &tltu,    "tltu",   COLUMN_FUNCT1, 51);
    inst_add(&instructionSet, &teq,     "teq",    COLUMN_FUNCT1, 52);
    inst_add(&instructionSet, &tne,     "tne",    COLUMN_FUNCT1, 54);

    inst_add(&instructionSet, &madd,    "madd",   COLUMN_FUNCT2, 0);
    inst_add(&instructionSet, &maddu,   "maddu",  COLUMN_FUNCT2, 1);
    inst_add(&instructionSet, &mul,     "mul",    COLUMN_FUNCT2, 2); //
    inst_add(&instructionSet, &msub,    "msub",   COLUMN_FUNCT2, 4);
    inst_add(&instructionSet, &msubu,   "msubu",  COLUMN_FUNCT2, 5);
    inst_add(&instructionSet, &clz,     "clz",    COLUMN_FUNCT2, 32);
    inst_add(&instructionSet, &clo,     "clo",    COLUMN_FUNCT2, 33);

    inst_add(&instructionSet, &bltz,    "bltz",   COLUMN_RT, 0);
    inst_add(&instructionSet, &bgez,    "bgez",   COLUMN_RT, 1);
    inst_add(&instructionSet, &bltzl,   "bltzl",  COLUMN_RT, 2);
    inst_add(&instructionSet, &bgzel,   "bgzel",  COLUMN_RT, 3);
    inst_add(&instructionSet, &tgei,    "tgei",   COLUMN_RT, 8);
    inst_add(&instructionSet, &tgeiu,   "tgeiu",  COLUMN_RT, 9);
    inst_add(&instructionSet, &tlti,    "tlti",   COLUMN_RT, 10);
    inst_add(&instructionSet, &tltiu,   "tltiu",  COLUMN_RT, 11);
    inst_add(&instructionSet, &tegi,    "tegi",   COLUMN_RT, 12);
    inst_add(&instructionSet, &tnei,    "tnei",   COLUMN_RT, 14);
    inst_add(&instructionSet, &bltzal,  "bltzal", COLUMN_RT, 16);
    inst_add(&instructionSet, &bgezal,  "bgezal", COLUMN_RT, 17);
    inst_add(&instructionSet, &bltzall, "bltzall",COLUMN_RT, 18);
    inst_add(&instructionSet, &bgczall, "bgczall",COLUMN_RT, 19);

    inst_add(&instructionSet, &j,       "j",      COLUMN_OP, 2);
    inst_add(&instructionSet, &jal,     "jal",    COLUMN_OP, 3);
    inst_add(&instructionSet, &beq,     "beq",    COLUMN_OP, 4);
    inst_add(&instructionSet, &bne,     "bne",    COLUMN_OP, 5);
    inst_add(&instructionSet, &blez,    "blez",   COLUMN_OP, 6);
    inst_add(&instructionSet, &bgtz,    "bgtz",   COLUMN_OP, 7);
    inst_add(&instructionSet, &addi,    "addi",   COLUMN_OP, 8);
    inst_add(&instructionSet, &addu,    "addu",   COLUMN_OP, 9);
    inst_add(&instructionSet, &slti,    "slti",   COLUMN_OP, 10);
    inst_add(&instructionSet, &sltiu,   "sltiu",  COLUMN_OP, 11);
    inst_add(&instructionSet, &andi,    "andi",   COLUMN_OP, 12);
    inst_add(&instructionSet, &ori,     "ori",    COLUMN_OP, 13);
    inst_add(&instructionSet, &xori,    "xori",   COLUMN_OP, 14);
    inst_add(&instructionSet, &lui,     "lui",    COLUMN_OP, 15);
    inst_add(&instructionSet, &benql,   "benql",  COLUMN_OP, 20);
    inst_add(&instructionSet, &bnel,    "bnel",   COLUMN_OP, 21);
    inst_add(&instructionSet, &blezl,   "blezl",  COLUMN_OP, 22);
    inst_add(&instructionSet, &bgtzl,   "bgtzl",  COLUMN_OP, 23);
    inst_add(&instructionSet, &lb,      "lb",     COLUMN_OP, 32);
    inst_add(&instructionSet, &lh,      "lh",     COLUMN_OP, 33);
    inst_add(&instructionSet, &lwl,     "lwl",    COLUMN_OP, 34);
    inst_add(&instructionSet, &lw,      "lw",     COLUMN_OP, 35);

    return instructionSet;
}

void inst_add(InstructionSet *set, void *function, char *mnemonic, size_t m, size_t n) {
    set->table[m][n].mnemonic = strdup(mnemonic);
    set->table[m][n].realization = function;
}
