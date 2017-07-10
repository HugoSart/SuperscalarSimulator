//
// Created by hsart on 09/07/17.
//

#include "alu.h"

int op_add      (int a, int b) {
   return a + b;
}
int op_subtract (int a, int b) {
    return a - b;
}
int op_and      (int a, int b) {
    return a != 0 && b != 0;
}
int op_or       (int a, int b) {
    return a != 0 || b != 0;
}
int op_nor      (int a, int b) {
    return !(a != 0 || b != 0);
}
int op_xor      (int a, int b) {
    return a ^ b;
}
int op_mult     (int a, int b) {
    return a * b;
}
int op_div      (int a, int b) {
    return a / b;
}
int op_zero     (int a, int b) {
    return a != 0;
}

ALU alu_init() {
    ALU alu = { .operation[OP_ADD]      = &op_add,
                .operation[OP_SUBTRACT] = &op_subtract,
                .operation[OP_AND]      = &op_and,
                .operation[OP_OR]       = &op_or,
                .operation[OP_NOR]      = &op_nor,
                .operation[OP_XOR]      = &op_xor,
                .operation[OP_MULT]     = &op_mult,
                .operation[OP_DIV]      = &op_div,
                .operation[OP_DIV]      = &op_zero};
    return alu;
}
