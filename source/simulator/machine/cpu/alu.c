//
// Created by hsart on 09/07/17.
//

#include "alu.h"

int op_add      (int a, int b) {
   return a + b;
}
int op_addu     (int a, int b) {
    return ((unsigned int)a + (unsigned int)b);
}
int op_sub      (int a, int b) {
    return a - b;
}
int op_subu     (int a, int b) {
    return ((unsigned int)a - (unsigned int)b);;
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
int op_multu    (int a, int b) {
    return ((unsigned int)a * (unsigned int)b);
}
int op_div      (int a, int b) {
    return a / b;
}
int op_divu     (int a, int b) {
    return ((unsigned int)a / (unsigned int)b);
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
int op_equals   (int a, int b) {
    return a == b;
}
int op_tequals  (int a, int b) {
    return a >= b;
}
int op_sequals  (int a, int b) {
    return a <= b;
}
int op_taller   (int a, int b) {
    return a > b;
}
int op_utaller  (int a, int b) {
    return (unsigned int)a > (unsigned int)b;
}
int op_smaller  (int a, int b) {
    return a < b;
}
int op_usmaller (int a, int b) {
    return (unsigned int)a < (unsigned int)b;
}
int op_clo      (int a, int b) {
    return __builtin_clz(~a);
}
int op_clz      (int a, int b) {
    return __builtin_clz(a);
}
int op_zero     (int a, int b) {
    return ~a;
}

ALU alu_init() {
    ALU alu = { .operation[OP_ADD]  = &op_add,
            .operation[OP_ADDU]     = &op_addu,
            .operation[OP_SUB]      = &op_sub,
            .operation[OP_SUBU]     = &op_subu,
            .operation[OP_AND]      = &op_and,
            .operation[OP_OR]       = &op_or,
            .operation[OP_NOR]      = &op_nor,
            .operation[OP_XOR]      = &op_xor,
            .operation[OP_MULT]     = &op_mult,
            .operation[OP_MULTU]    = &op_multu,
            .operation[OP_DIV]      = &op_div,
            .operation[OP_DIVU]     = &op_divu,
            .operation[OP_ALSHIFT]  = &op_alshift,
            .operation[OP_ARSHIFT]  = &op_arshift,
            .operation[OP_LLSHIFT]  = &op_llshift,
            .operation[OP_LRSHIFT]  = &op_lrshift,
            .operation[OP_EQUALS]   = &op_equals,
            .operation[OP_TEQUALS]  = &op_tequals,
            .operation[OP_SEQUALS]  = &op_sequals,
            .operation[OP_TALLER]   = &op_taller,
            .operation[OP_UTALLER]  = &op_utaller,
            .operation[OP_SMALLER]  = &op_smaller,
            .operation[OP_USMALLER] = &op_usmaller,
            .operation[OP_CLO]      = &op_clo,
            .operation[OP_CLZ]      = &op_clz,
            .operation[OP_ZERO]     = &op_zero};
    //s_add();
    return alu;
}

int alu_exec(ALU *alu, EOperations e, int a, int b) {
    return alu->operation[e](a, b);
}
