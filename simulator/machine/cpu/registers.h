//
// Created by hsart on 09/07/17.
//

#ifndef SUPERSCALARSIMULATOR_REGISTERS_H
#define SUPERSCALARSIMULATOR_REGISTERS_H

#include "../memory/util.h"

#define C_OP_

typedef union {
    BYTE byte[4];
    int value;
} REGISTER;

enum reg_e {
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
    RA,
    REG_COUNT
};

typedef struct {
    REGISTER reg[32];
} RegistersSet;

RegistersSet reg_init();

#endif //SUPERSCALARSIMULATOR_REGISTERS_H
