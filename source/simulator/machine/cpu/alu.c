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
    return a & b;
}
int op_or       (int a, int b) {
    return a | b;
}
int op_nor      (int a, int b) {
    return ~(a | b);
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
     return ~a;
}
int op_alshift  (int a, int b) {
    return a << b;
}
int op_arshift  (int a, int b) {
    return a >> b;
}
int op_llshift  (int a, int b) {
    return (int)((unsigned int) a << b);
}
int op_lrshift  (int a, int b) {
    return (int)((unsigned int) a >> b);
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
                .operation[OP_ALSHIFT]  = &op_alshift,
                .operation[OP_ARSHIFT]  = &op_arshift,
                .operation[OP_LLSHIFT]  = &op_llshift,
                .operation[OP_LRSHIFT]  = &op_lrshift,
                .operation[OP_ZERO]     = &op_zero};
    return alu;
}

int alu_exec(ALU *alu, EOperations e, int a, int b) {
    return alu->operation[e](a, b);
}
