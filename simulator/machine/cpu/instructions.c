//
// Created by hsart on 09/07/17.
//

#include <stdarg.h>
#include "instructions.h"
#include "../types.h"

#define VA_3(valist)    int *rd = va_arg(valist, int*); \
                        int *rs = va_arg(valist, int*); \
                        int *rt = va_arg(valist, int*);

#define VA_3I(valist)   ERegisters R1 = va_arg(valist, ERegisters); \
                        ERegisters R2 = va_arg(valist, ERegisters); \
                        int imm      = va_arg(valist, int);

#define VA_END  va_end(valist);

typedef struct r_t {
    unsigned int op     : 6;
    unsigned int rs     : 5;
    unsigned int rt     : 5;
    unsigned int rd     : 5;
    unsigned int z      : 5;
    unsigned int func   : 6;
} _R;

typedef struct ri_t {
    unsigned int op     : 6;
    unsigned int rs     : 5;
    unsigned int rt     : 5;
    unsigned int imm    : 16;
} _RI;

typedef struct j_t {
    unsigned int op     : 6;
    unsigned int target : 26;
} _J;

typedef union {
    unsigned int opcode;
    _R r;
    _RI ri;
    _J j;
} Opcode;

// VER MOVF E BRANCHES

// Instruction implementations
void add   (va_list valist) {
    VA_3(valist)
    *rd = alu->operation[OP_ADD](*rs, *rt);
}
void addu  (va_list valist) {

}
void addi  (va_list valist) {

}
void addiu (va_list valist) {

}
void andi  (va_list valist) {

}
void and   (va_list valist) {

}
void clo   (va_list valist) {

}
void clz   (va_list valist) {

}
void div   (va_list valist) {
}
void divu  (va_list valist) {

}
void mult  (va_list valist) {

}
void multu (va_list valist) {

}
void mul   (va_list valist) {

}
void madd  (va_list valist) {

}
void maddu (va_list valist) {

}
void msub  (va_list valist) {

}
void nor   (va_list valist) {

}
void or    (va_list valist) {

}
void ori   (va_list valist) {

}

InstructionSet inst_init() {
    InstructionSet instructionSet = {
            .instruction[ADD]     = &add,
            .instruction[ADDU]    = &addu,
            .instruction[ADDI]    = &addi,
            .instruction[ADDIU]   = &addiu,
            .instruction[AND]     = &and,
            .instruction[ANDI]    = &andi,
            .instruction[CLO]     = &clo,
            .instruction[CLZ]     = &clz,
            .instruction[DIV]     = &div,
            .instruction[DIVU]    = &divu,
            .instruction[MULT]    = &mult,
            .instruction[MULTU]   = &multu,
            .instruction[MUL]     = &mul,
            .instruction[MADD]    = &madd,
            .instruction[MADDU]   = &maddu,
            .instruction[MSUB]    = &msub,
            .instruction[NOR]     = &nor,
            .instruction[OR]      = &or,
            .instruction[ORI]     = &ori
    };
    return instructionSet;
}
