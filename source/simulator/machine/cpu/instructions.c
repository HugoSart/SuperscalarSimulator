//
// Created by hsart on 09/07/17.
//

#include <string.h>
#include "instructions.h"
#include "cpu.h"
#include "../util.h"

#define PARAM_STANDARD CPU *cpu, ...

// VER MOVF E BRANCHES

void inst_add(InstructionSet *set, void *, char *, EType, size_t m, size_t n);

// Instruction implementations
void add     (PARAM_STANDARD) {
    va_list va;
    va_start(va, 3);
    Register *rd = va_arg(va, Register*);
    Register *rs = va_arg(va, Register*);
    Register *rt = va_arg(va, Register*);

}
void addu    (PARAM_STANDARD) {

}
void addi    (PARAM_STANDARD) {

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
    va_list va;
    va_start(va, 3);
    Register *buffer = va_arg(va, Register*);
    int rs = va_arg(va, int);
    int rt = va_arg(va, int);

    buffer->content.value = cpu->alu.operation[OP_MULT](cpu_reg_get(cpu, rs), cpu_reg_get(cpu, rt));

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

}

void err     (PARAM_STANDARD) {
    printf("ERROR: No such instruction.\n");
}

InstructionSet inst_init() {

    InstructionSet instructionSet = {0};

    inst_add(&instructionSet, &sll,     "sll",    TYPE_SHIFT,   COLUMN_FUNCT1, 0); //
    inst_add(&instructionSet, &slr,     "slr",    TYPE_SHIFT,   COLUMN_FUNCT1, 2);
    inst_add(&instructionSet, &sra,     "sra",    TYPE_SHIFT,   COLUMN_FUNCT1, 3);
    inst_add(&instructionSet, &sllv,    "sllv",   TYPE_SHIFT,   COLUMN_FUNCT1, 4); //
    inst_add(&instructionSet, &srlv,    "srlv",   TYPE_SHIFT,   COLUMN_FUNCT1, 6);
    inst_add(&instructionSet, &srav,    "srav",   TYPE_SHIFT,   COLUMN_FUNCT1, 7);
    inst_add(&instructionSet, &jr,      "jr",     TYPE_JMP,     COLUMN_FUNCT1, 8);
    inst_add(&instructionSet, &jalr,    "jalr",   TYPE_JMP,     COLUMN_FUNCT1, 9);
    inst_add(&instructionSet, &movz,    "movz",   TYPE_IF,      COLUMN_FUNCT1, 10);
    inst_add(&instructionSet, &movn,    "movn",   TYPE_IF,      COLUMN_FUNCT1, 11);
    inst_add(&instructionSet, &syscall, "syscall",TYPE_UNKNOWN, COLUMN_FUNCT1, 12);
    inst_add(&instructionSet, &_break,  "break",  TYPE_JMP,     COLUMN_FUNCT1, 13); //
    inst_add(&instructionSet, &sync,    "sync",   TYPE_UNKNOWN, COLUMN_FUNCT1, 16);
    inst_add(&instructionSet, &mfhi,    "mfhi",   TYPE_ACUMULATOR, COLUMN_FUNCT1, 17);
    inst_add(&instructionSet, &mthi,    "mthi",   TYPE_ACUMULATOR, COLUMN_FUNCT1, 18);
    inst_add(&instructionSet, &mflo,    "mflo",   TYPE_ACUMULATOR, COLUMN_FUNCT1, 19); //;
    inst_add(&instructionSet, &mult,    "mult",   TYPE_MULT, COLUMN_FUNCT1, 24);
    inst_add(&instructionSet, &multu,   "multu",  TYPE_MULT, COLUMN_FUNCT1, 25);
    inst_add(&instructionSet, &div,     "div",    TYPE_MULT,    COLUMN_FUNCT1, 26);
    inst_add(&instructionSet, &divu,    "divu",   TYPE_MULT,    COLUMN_FUNCT1, 27); //
    inst_add(&instructionSet, &add,     "add",    TYPE_ARITHMETIC, COLUMN_FUNCT1, 32);
    inst_add(&instructionSet, &addu,    "addu",   TYPE_ARITHMETIC, COLUMN_FUNCT1, 33);
    inst_add(&instructionSet, &sub,     "sub",    TYPE_ARITHMETIC, COLUMN_FUNCT1, 34);
    inst_add(&instructionSet, &subu,    "subu",   TYPE_ARITHMETIC, COLUMN_FUNCT1, 35);
    inst_add(&instructionSet, &and,     "and",    TYPE_LOGICAL, COLUMN_FUNCT1, 36);
    inst_add(&instructionSet, &or,      "or",     TYPE_LOGICAL, COLUMN_FUNCT1, 37);
    inst_add(&instructionSet, &xor,     "xor",    TYPE_LOGICAL, COLUMN_FUNCT1, 38);
    inst_add(&instructionSet, &nor,     "nor",    TYPE_LOGICAL, COLUMN_FUNCT1, 39);
    inst_add(&instructionSet, &slt,     "slt",    TYPE_IF, COLUMN_FUNCT1, 42);
    inst_add(&instructionSet, &sltu,    "sltu",   TYPE_IF, COLUMN_FUNCT1, 43); //
    inst_add(&instructionSet, &tge,     "tge",    TYPE_UNKNOWN, COLUMN_FUNCT1, 48);
    inst_add(&instructionSet, &tgeu,    "tgeu",   TYPE_UNKNOWN, COLUMN_FUNCT1, 49);
    inst_add(&instructionSet, &tlt,     "tlt",    TYPE_UNKNOWN, COLUMN_FUNCT1, 50);
    inst_add(&instructionSet, &tltu,    "tltu",   TYPE_UNKNOWN, COLUMN_FUNCT1, 51);
    inst_add(&instructionSet, &teq,     "teq",    TYPE_UNKNOWN, COLUMN_FUNCT1, 52);
    inst_add(&instructionSet, &tne,     "tne",    TYPE_UNKNOWN, COLUMN_FUNCT1, 54);

    inst_add(&instructionSet, &madd,    "madd",   TYPE_MULT, COLUMN_FUNCT2, 0);
    inst_add(&instructionSet, &maddu,   "maddu",  TYPE_MULT, COLUMN_FUNCT2, 1);
    inst_add(&instructionSet, &mul,     "mul",    TYPE_MULT, COLUMN_FUNCT2, 2); //
    inst_add(&instructionSet, &msub,    "msub",   TYPE_MULT, COLUMN_FUNCT2, 4);
    inst_add(&instructionSet, &msubu,   "msubu",  TYPE_MULT, COLUMN_FUNCT2, 5);
    inst_add(&instructionSet, &clz,     "clz",    TYPE_ARITHMETIC, COLUMN_FUNCT2, 32);
    inst_add(&instructionSet, &clo,     "clo",    TYPE_ARITHMETIC, COLUMN_FUNCT2, 33);

    inst_add(&instructionSet, &bltz,    "bltz",   TYPE_JMP, COLUMN_RT, 0);
    inst_add(&instructionSet, &bgez,    "bgez",   TYPE_JMP, COLUMN_RT, 1);
    inst_add(&instructionSet, &bltzl,   "bltzl",  TYPE_JMP, COLUMN_RT, 2);
    inst_add(&instructionSet, &bgzel,   "bgzel",  TYPE_JMP, COLUMN_RT, 3);
    inst_add(&instructionSet, &tgei,    "tgei",   TYPE_UNKNOWN, COLUMN_RT, 8);
    inst_add(&instructionSet, &tgeiu,   "tgeiu",  TYPE_UNKNOWN, COLUMN_RT, 9);
    inst_add(&instructionSet, &tlti,    "tlti",   TYPE_UNKNOWN, COLUMN_RT, 10);
    inst_add(&instructionSet, &tltiu,   "tltiu",  TYPE_UNKNOWN, COLUMN_RT, 11);
    inst_add(&instructionSet, &tegi,    "tegi",   TYPE_UNKNOWN, COLUMN_RT, 12);
    inst_add(&instructionSet, &tnei,    "tnei",   TYPE_UNKNOWN, COLUMN_RT, 14);
    inst_add(&instructionSet, &bltzal,  "bltzal", TYPE_JMP, COLUMN_RT, 16);
    inst_add(&instructionSet, &bgezal,  "bgezal", TYPE_JMP, COLUMN_RT, 17);
    inst_add(&instructionSet, &bltzall, "bltzall",TYPE_JMP, COLUMN_RT, 18);
    inst_add(&instructionSet, &bgczall, "bgczall",TYPE_JMP, COLUMN_RT, 19);

    inst_add(&instructionSet, &j,       "j",      TYPE_JMP, COLUMN_OP, 2);
    inst_add(&instructionSet, &jal,     "jal",    TYPE_JMP, COLUMN_OP, 3);
    inst_add(&instructionSet, &beq,     "beq",    TYPE_JMP, COLUMN_OP, 4);
    inst_add(&instructionSet, &bne,     "bne",    TYPE_JMP, COLUMN_OP, 5);
    inst_add(&instructionSet, &blez,    "blez",   TYPE_JMP, COLUMN_OP, 6);
    inst_add(&instructionSet, &bgtz,    "bgtz",   TYPE_JMP, COLUMN_OP, 7);
    inst_add(&instructionSet, &addi,    "addi",   TYPE_ARITHMETIC, COLUMN_OP, 8);
    inst_add(&instructionSet, &addu,    "addu",   TYPE_ARITHMETIC, COLUMN_OP, 9);
    inst_add(&instructionSet, &slti,    "slti",   TYPE_IF, COLUMN_OP, 10);
    inst_add(&instructionSet, &sltiu,   "sltiu",  TYPE_IF, COLUMN_OP, 11);
    inst_add(&instructionSet, &andi,    "andi",   TYPE_LOGICAL, COLUMN_OP, 12);
    inst_add(&instructionSet, &ori,     "ori",    TYPE_LOGICAL, COLUMN_OP, 13);
    inst_add(&instructionSet, &xori,    "xori",   TYPE_LOGICAL, COLUMN_OP, 14);
    inst_add(&instructionSet, &lui,     "lui",    TYPE_LOGICAL, COLUMN_OP, 15);
    inst_add(&instructionSet, &benql,   "benql",  TYPE_JMP, COLUMN_OP, 20);
    inst_add(&instructionSet, &bnel,    "bnel",   TYPE_JMP, COLUMN_OP, 21);
    inst_add(&instructionSet, &blezl,   "blezl",  TYPE_JMP, COLUMN_OP, 22);
    inst_add(&instructionSet, &bgtzl,   "bgtzl",  TYPE_JMP, COLUMN_OP, 23);
    inst_add(&instructionSet, &lb,      "lb",     TYPE_LOAD, COLUMN_OP, 32);
    inst_add(&instructionSet, &lh,      "lh",     TYPE_LOAD, COLUMN_OP, 33);
    inst_add(&instructionSet, &lwl,     "lwl",    TYPE_LOAD, COLUMN_OP, 34);
    inst_add(&instructionSet, &lw,      "lw",     TYPE_LOAD, COLUMN_OP, 35);

    return instructionSet;
}

void inst_add(InstructionSet *set, void *function, char *mnemonic, EType type, size_t m, size_t n) {
    set->table[m][n].mnemonic = strdup(mnemonic);
    set->table[m][n].realization = function;
    set->table[m][n].type = type;
}
