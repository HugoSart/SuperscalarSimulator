//
// Created by hsart on 10/07/17.
//

#ifndef SUPERSCALARSIMULATOR_CPU_PIPELINE_H_H
#define SUPERSCALARSIMULATOR_CPU_PIPELINE_H_H

#include <stdio.h>
#include <stdbool.h>
#include "util.h"
#include "types.h"
#include "cpu/register.h"

typedef struct bus_t {
    Word data;
    int busy;
} Bus;

typedef struct bus128_t {
    Word data[4];
    int busy;
} Bus128;

// Mobo declarations
typedef struct cpu_t CPU;
typedef struct mem_t Memory;
typedef struct mobo_t {
    Memory *mem;
    CPU *cpu;
    Bus128 data_bus;
    Bus control_bus, address_bus;
} Mobo;

// Memory declarations
typedef struct mem_t {

    Mobo *_p_mobo;

    BYTE *byte;
    unsigned int size;
    unsigned int text_address;

};

// Cache declarations
struct dec_t {
    unsigned int byte : 4;
    unsigned int line : 3; // 11
    unsigned int tag  : 3; // 14
};
typedef union dec_address {
    unsigned int full_address;
    struct dec_t mapped_address;
} Address;
typedef struct line_t {
    int tag;
    Word word[4];
} Line;
typedef struct cache_t {

    // Parents
    CPU *_p_cpu;

    Memory *mem;
    Line *line;
    size_t size; // in bytes

} Cache;

// Instruction declarations
typedef struct rstation_t ReservationStation;
typedef struct r_t {
    unsigned int func : 6;
    unsigned int z    : 5;
    unsigned int rd   : 5;
    unsigned int rt   : 5;
    unsigned int rs   : 5;
    unsigned int op   : 6;
} _R;
typedef struct ri_t {
    int imm    : 16;
    unsigned int rt     : 5;
    unsigned int rs     : 5;
    unsigned int op     : 6;
} _RI;
typedef struct j_t {
    unsigned int target : 26;
    unsigned int op     : 6;
} _J;
typedef union {
    unsigned int opcode;
    _R r;
    _RI ri;
    _J j;
} Opcode;
typedef enum {
    COLUMN_OP, COLUMN_RT, COLUMN_FUNCT1, COLUMN_FUNCT2, COLUMN_J
} EColumnType;
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
    MFHI, MFLO, MTHI, MTLO, MOVN, MOVZ,
    INSTRUCTION_COUNT
} EInstructions;
typedef enum {
    RTYPE_R, RTYPE_RI, RTYPE_RT, RTYPE_J, RTYPE_UNKNOWN
} ERType;
typedef enum {
    TYPE_ARITHMETIC, TYPE_SHIFT, TYPE_LOGICAL, TYPE_IF,
    TYPE_MULT, TYPE_ACUMULATOR, TYPE_JMP, TYPE_BRANCH, TYPE_LOAD, TYPE_STORE,
    TYPE_COUNT
#define TYPE_UNKNOWN TYPE_COUNT
} EType;
typedef struct instruction_ref_t {
    char *mnemonic;
    EType type;
    void (*realization)(CPU *cpu, ...);
} InstructionRef;
typedef struct instruction_t {
    Opcode code;
    ERType rtype;
    InstructionRef *ref;
} Instruction;
typedef struct instruction_set_t {
    InstructionRef table[4][64];
} InstructionSet;

// IFIFO declarations
typedef struct inode_t {
    Instruction instruction;
    struct inode_t *next;
} INode;
typedef struct fifo {
    INode *first;
} IFIFO;

// Register declarations
typedef struct lohi_t {
    long long int lo : 32;
    long long int hi : 32;
} LOHI;
typedef union lohi_u {
    int value;
    LOHI lohi;
} CLOHI;
typedef struct rstation_t ReservationStation;
typedef enum reg_e {
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
    REG_COUNT,
    LO = 32, HI = 33,
    REG_COUNT_2 = 34
#define REG_UNKNOWN REG_COUNT_2
} ERegisters;
typedef struct register_t {
    Word content;
    ReservationStation *rstation;
} Register;

// ReservationStation declarations
typedef enum rstation_type_e {
    RS_TYPE_ADD, RS_TYPE_MUL, RS_TYPE_LOAD, RS_TYPE_STORE,
    RS_TYPE_COUNT
#define RS_TYPE_UNKNOWN RS_TYPE_COUNT
} ERStationType;
typedef enum rstation_e {
    RS_ADD1, RS_ADD2, RS_ADD3,
    RS_MUL1, RS_MUL2,
    RS_LOAD1, RS_LOAD2, RS_LOAD3, RS_LOAD4, RS_LOAD5,
    RS_SOTR1, RS_STOR2, RS_STOR3, RS_STOR4, RS_STOR5,
    RS_COUNT
#define RS_UNKNOWN RS_COUNT
} ERStation;
typedef struct rsresult_t {
    Word content;
    int validation;
} RSResult;
typedef struct rstation_t {

    Instruction instruction;
    ERStationType type;

    int busy;
    int qj, qk;
    int vj, vk;
    int A;

    RSResult result;

};

// CDBFIFO declarations
typedef struct cdbnode_t {
    ERegisters destination;
    ERStation tag;
    Word data;
    struct cdbnode_t *next;
} CDBNode;

typedef struct cdbfifo_t {
    CDBNode *first;
} CDBFifo;

// Pipeline declarations
enum stages_e {
    FETCH, DECODE, ISSUE, EXEC, WRITE_RESULT,
    STAGE_COUNT
} EStage;
typedef struct {
#define ISSUE_STOP 0
#define ISSUE_CONTINUE 1
    Word pc, ri;
    IFIFO queue;
    int issue;
    ReservationStation rstation[RS_COUNT];
    void (*stage[STAGE_COUNT])(CPU *);
} Pipeline;

// ALU declarations
typedef enum {
    OP_ADD, OP_ADDU, OP_SUB, OP_SUBU,
    OP_AND, OP_OR, OP_NOR, OP_XOR,
    OP_MULT, OP_MULTU, OP_DIV, OP_DIVU,
    OP_ARSHIFT, OP_ALSHIFT,
    OP_LRSHIFT, OP_LLSHIFT,
    OP_EQUALS, OP_TEQUALS, OP_SEQUALS, OP_TALLER, OP_UTALLER, OP_SMALLER, OP_USMALLER,
    OP_ZERO,
    OPERATIONS_COUNTER
} EOperations;
typedef struct alu_t {
    int (*operation[OPERATIONS_COUNTER])(int, int);
} ALU;

typedef struct cdb_t {
    Word data;
    ERStation tag;
    ERegisters destination;
    int busy;
    CDBFifo queue;
} CDB;

// CPU declarations
typedef struct cpu_t {

    // Parents
    Mobo *_p_mobo;

    Cache cache;
    ALU alu;
    Register reg[34];
    Pipeline pipeline;
    InstructionSet inst_set;
    CDB cdb;

} CPU;

#endif //SUPERSCALARSIMULATOR_CPU_PIPELINE_H_H
