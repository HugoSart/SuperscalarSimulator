//
// Created by hsart on 09/07/17.
//

#ifndef SUPERSCALARSIMULATOR_INSTRUCTIONS_H
#define SUPERSCALARSIMULATOR_INSTRUCTIONS_H

#include "alu.h"

#define ARG_3  (REGISTER *rd, REGISTER *rs, REGISTER *rt)
#define ARG_3I (REGISTER *r1, REGISTER *r2, int imm)
#define ARG_3S (REGISTER *r1, REGISTER *r2, unsigned int shamt)
#define ARG_2  (REGISTER *r1, REGISTER *r2)
#define ARG_2I (REGISTER *r1, int imm)
#define ARG_2S (REGISTER *r1, unsigned int shamt)
#define ARG_2A (REGISTER *r1, int oi)
#define ARG_1  (REGISTER *r1)
#define ARG_1I (int imm)
#define ARG_1S (unsigned int sham)
#define ARG_1T (unsigned int target)

enum instructions_type{
    OP,
    OP_3, OP_3I, OP_3S,
    OP_2, OP_2I, OP_2S, OP_2A,
    OP_1, OP_1I, OP_1S, OP_1T
};

typedef enum {
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
    MFHI, MFLO, MTHI, MTLO, MFC0, MFC1, MTC0, MTC1, MOVN, MOVZ, MOVF, MOVT,
    INSTRUCTION_COUNT
} EInstructions;

typedef union {
    void (*instruction)(va_list);
} Instruction;

typedef struct {
    void (*instruction[INSTRUCTION_COUNT])(ALU *alu, va_list);
} InstructionSet;

InstructionSet inst_init();

#endif //SUPERSCALARSIMULATOR_INSTRUCTIONS_H
