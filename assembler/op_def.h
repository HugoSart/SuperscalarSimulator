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
    DIV, DIVU, DIV_3, DIVU_3,
    MULT, MULTU, MUL, MULO, MULOU, MADD, MADDU, MSUB,
    NEG, NEGU, NOR,
    OR, ORI,
    REM, REMU,
    SLL, SLLV, SRA, SRAV, SRL, SRLV,
    ROL, ROR,
    SUB, SUBU,
    XOR, XORI,
    LUI, LI,
    SLT, SLTU, SLTI, SLTIU, SEQ, SGE, SGEU, SGT, SGTU, SLE, SLEU, SNE,
    B, BCLF, BCLT, BEQ, BGEZ, BGEZAL, BGTZ, BLEZ, BLTZAL, BLTZ, BNE, BEQZ, BGE,
    BGEU, BGT, BGTU, BLE, BLEU, BLT, BLTU, BNEZ,
    J, JAL, JAIR, JR,
    TEQ, TEQI, TGE, TGEU, TGEI, TGEIU, TLT, TLTU, TLTI, TLTIU,
    LA, LB, LBU, LH, LHU, LW, LWCL, LWL, LWR, LD, ULH, ULHU, ULW,
    LL, SB, SH, SW, SWCL, SDCL
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

char *bsopcode(int id);

char *bsfunc(int id);

char *regcode(unsigned int id);

#endif //SUPERSCALARSIMULATOR_OP_DEF_H
