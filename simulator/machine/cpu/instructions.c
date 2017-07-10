//
// Created by hsart on 09/07/17.
//

#include <stdarg.h>
#include "instructions.h"
#include "registers.h"
#include "cpu.h"

#define VA_3(valist)    Register *r1 = va_arg(valist, Register*); \
                        Register *r2 = va_arg(valist, Register*); \
                        Register *r3 = va_arg(valist, Register*);

#define VA_3I(valist)   Register *r1 = va_arg(valist, Register*); \
                        Register *r2 = va_arg(valist, Register*); \
                        int imm      = va_arg(valist, int);

#define VA_END  va_end(valist);

// Instruction implementations
void add   (CPU *cpu, va_list valist) {
    VA_3(valist)
    r1->value = cpu->alu.operation[OP_ADD](r2->value, r3->value);
}
void addu  (ALU *alu, va_list valist) {

}
void addi  (ALU *alu, va_list valist) {
    VA_3I(valist);
    r1->value = alu->operation[OP_ADD](r2->value, imm);
}
void addiu (va_list valist) {

}
void andi  (va_list valist) {

}
void and   (ALU *alu, va_list valist) {

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
