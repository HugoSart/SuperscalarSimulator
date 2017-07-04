//
// Created by hsart on 03/05/17.
//

#ifndef SUPERSCALARSIMULATOR_OP_DEF_H
#define SUPERSCALARSIMULATOR_OP_DEF_H

#include <stdio.h>
#include "bop.h"

enum op {
    ADD, ADDU, ADDI, ADDIU, ANDI, AND,
    CLO, CLZ,
    DIV, DIVU,
    MULT, MULTU, MUL, MADD, MADDU, MSUB,
    NOR,
    OR, ORI,
    SLL, SLLV, SRA, SRAV, SRL, SRLV,
    SUB, SUBU,
    XOR, XORI,
    LUI,
    SLT, SLTU, SLTI, SLTIU,
    BCLF, BCLT, BEQ, BGEZ, BGEZAL, BGTZ, BLEZ, BLTZAL, BLTZ, BNE,
    J, JAL, JALR, JR,
    TEQ, TEQI, TGE, TGEU, TGEI, TGEIU, TLT, TLTU, TLTI, TLTIU,
    LB, LBU, LH, LHU, LW, LWCL, LWL, LWR, LL,
    SB, SH, SW, SWCL, SDCL, SWL, SWR, SC,
    MFHI, MFLO, MTHI, MTLO, MFC0, MFC1, MTC0, MTC1, MOVN, MOVZ, MOVF, MOVT
};

enum reg {
    ZERO,
    AT,
    V0, V1,
    A0, A1, A2, A3,
    T0, T1, T2, T3, T4, T5, T6, T7,
    S0, S1, S2, S3, S4, S5, S6, S7,
    T8, T9,
    K0, K1,
    GP, SP,
    S8, FP = S8,
    RA
};

int opcode(unsigned int id);
int func(unsigned int id);
char *regcode(unsigned int id);

#endif //SUPERSCALARSIMULATOR_OP_DEF_H
