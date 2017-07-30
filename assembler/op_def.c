#include "op_def.h"

#define NOT_FOUND -1

int opcode(unsigned int id) {

    switch(id) {
        case ADD:
            return 0x0;
        case ADDU:
            return 0x0;
        case ADDI:
            return 0x8;
        case ADDIU:
            return 0x9;
        case AND:
            return 0x0;
        case ANDI:
            return 0xc;
        case CLO:
            return 0x1c;
        case CLZ:
            return 0x1c;
        case DIV:
            return 0x0;
        case DIVU:
            return 0x0;
        case MULT:
            return 0x0;
        case MULTU:
            return 0x0;
        case MUL:
            return 0x1c;
        case MADD:
            return 0x1c;
        case MADDU:
            return 0x1c;
        case MSUB:
            return 0x1c;
        //case MSUB:
        //    return "000000";
        case NOR:
            return 0x0;
        case OR:
            return 0x0;
        case ORI:
            return 63;
        case SLL:
            return 0;
        case SLLV:
            return 0;
        case SRA:
            return 0;
        case SRAV:
            return 0;
        case SRL:
            return 0;
        case SRLV:
            return 0;
        case SUB:
            return 0;
        case SUBU:
            return 0;
        case XOR:
            return 0;
        case XORI:
            return 0xe;
        case LUI:
            return 0xf;
        case SLT:
            return 0;
        case SLTU:
            return 0;
        case SLTI:
            return 0xa;
        case SLTIU:
            return 0xb;
        case BCLF:
            return 0x11;
        case BCLT:
            return 0x11;
        case BEQ:
            return 4;
        case BGEZ:
            return 1;
        case BGEZAL:
            return 1;
        case BGTZ:
            return 7;
        case BLEZ:
            return 6;
        case BLTZAL:
            return 1;
        case BLTZ:
            return 1;
        case BNE:
            return 5;
        case J:
            return 2;
        case JAL:
            return 3;
        case JALR:
            return 0;
        case JR:
            return 0;
        case TEQ:
            return 0;
        case TEQI:
            return 1;
        case TGE:
            return 0;
        case TGEU:
            return 0;
        case TGEI:
            return 1;
        case TGEIU:
            return 1;
        case TLT:
            return 0;
        case TLTU:
            return 0;
        case TLTI:
            return 1;
        case TLTIU:
            return 1;
        case LB:
            return 0x20;
        case LBU:
            return 0x24;
        case LH:
            return 0x21;
        case LHU:
            return 0x25;
        case LW:
            return 0x23;
        case LWCL:
            return 0x31;
        case LWL:
            return 0x22;
        case LWR:
            return 0x26;
        case LL:
            return 0x30;
        case SB:
            return 0x28;
        case SH:
            return 0x29;
        case SW:
            return 0x2b;
        case SWCL:
            return 0x31;
        case SDCL:
            return 0x3d;
        case SWL:
            return 0x2a;
        case SWR:
            return 0x2e;
        case SC:
            return 0x38;
        case MFHI:
            return 0;
        case MFLO:
            return 0;
        case MTHI:
            return 0;
        case MTLO:
            return 0;
        case MOVN:
            return 0;
        case MOVZ:
            return 0;
        default:
            printf("ERROR: ID not found.\n");
            return NOT_FOUND;
    }

}

int func(unsigned int id) {

    switch(id) {
        case ADD:
            return 0x20;
        case ADDU:
            return 0x21;
        case AND:
            return 0x24;
        case CLO:
            return 0x21;
        case CLZ:
            return 0x20;
        case DIV:
            return 0x1a;
        case DIVU:
            return 0x1b;
        case MULT:
            return 0x18;
        case MULTU:
            return 0x19;
        case MUL:
            return 0x2;
        case MADD:
            return 0x0;
        case MADDU:
            return 0x1;
        case MSUB:
            return 0x4;
            //case MSUB:
            //    return "000000";
        case NOR:
            return 0x27;
        case OR:
            return 0x25;
        case SLL:
            return 0x0;
        case SLLV:
            return 0x4;
        case SRA:
            return 0x3;
        case SRAV:
            return 0x7;
        case SRL:
            return 0x2;
        case SRLV:
            return 0x6;
        case SUB:
            return 0x22;
        case SUBU:
            return 0x23;
        case XOR:
            return 0x26;
        case SLT:
            return 0x2a;
        case SLTU:
            return 0x2b;
        case JALR:
            return 0x9;
        case JR:
            return 0x8;
        case TEQ:
            return 0x34;
        case TGE:
            return 0x30;
        case TGEU:
            return 0x31;
        case TLT:
            return 0x32;
        case TLTU:
            return 0x33;
        case MFHI:
            return 0x10;
        case MFLO:
            return 0x12;
        case MTHI:
            return 0x11;
        case MTLO:
            return 0x13;
        case MOVN:
            return 0xb;
        case MOVZ:
            return 0xa;
        default:
            printf("ERROR: ID not found.\n");
            return NOT_FOUND;
    }

}

int rtfunc(unsigned int id) {

    switch (id) {
        case BGEZ   : return 1;
        case BGEZAL : return 0x11;
        case BGTZ   : return 0;
        case BLEZ   : return 0;
        case BLTZAL : return 0x10;
        case BLTZ   : return 0;
    }

    return NOT_FOUND;

}

char *regcode(unsigned int id) {

    if (id > 31) return NULL;

    return itbs(5, id);
}

