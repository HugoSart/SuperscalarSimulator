//
// Created by hsart on 09/07/17.
//

#ifndef SUPERSCALARSIMULATOR_ALU_H
#define SUPERSCALARSIMULATOR_ALU_H

typedef enum {
    OP_ADD, OP_SUBTRACT,
    OP_AND, OP_OR, OP_NOR, OP_XOR,
    OP_MULT, OP_DIV,
    OP_ZERO,
    OPERATIONS_COUNTER
} EOperations;

typedef struct {
    int (*operation[OPERATIONS_COUNTER])(int, int);
} ALU;

ALU alu_init();

#endif //SUPERSCALARSIMULATOR_ALU_H
