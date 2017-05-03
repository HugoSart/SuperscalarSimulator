//
// Created by hsart on 03/05/17.
//

#ifndef SUPERSCALARSIMULATOR_OP_DEF_H
#define SUPERSCALARSIMULATOR_OP_DEF_H

enum instructions {
    ADD, ADDU, ADDI, ADDIU, ANDI, AND,
    CLO, CLZ,
    DIV, DIVU, DIV_3, DIVU_3,
    MULT, MULTU, MUL, MULO, MULOU, MADD, MADDU, MSUB
};

enum registrers {
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

#endif //SUPERSCALARSIMULATOR_OP_DEF_H
