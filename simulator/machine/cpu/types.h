//
// Created by hsart on 10/07/17.
//

#ifndef SUPERSCALARSIMULATOR_CPU_PIPELINE_H_H
#define SUPERSCALARSIMULATOR_CPU_PIPELINE_H_H

#include "cache.h"

// Registers definitions
typedef union {
    BYTE byte[4];
    int value;
} Register;
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
    Register reg[32];
} RegistersSet;

// Bus definitions
typedef union {
    BYTE bus[4];
    int value;
} Bus;

// ALU definitions
typedef enum {
    OP_ADD, OP_SUBTRACT,
    OP_AND, OP_OR, OP_NOR, OP_XOR,
    OP_MULT, OP_DIV,
    OP_ZERO,
    OPERATIONS_COUNTER
} EOperations;
typedef struct alu_t {
    int (*operation[OPERATIONS_COUNTER])(int, int);
} ALU;

// Pipeline definitions
enum stages_e {
    FETCH, DECODE, EXEC, MEM_ACCESS, WRITE_BACK,
    STAGE_COUNT
} EStage;
typedef struct {
    int pc, ri;
    void (*stage[STAGE_COUNT])(unsigned int);
} Pipeline;

// InstructionsSet
typedef struct cpu_t CPU;
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
typedef struct instruction_set_t {
    void (*instruction[INSTRUCTION_COUNT])(CPU *cpu, va_list);
} InstructionSet;

// CPU definitions
struct cpu_t {
    Cache cache;
    ALU alu;
    RegistersSet reg_set;
    Pipeline pipeline;
    InstructionSet inst_set;
    Bus cdb;
};

#endif //SUPERSCALARSIMULATOR_CPU_PIPELINE_H_H
