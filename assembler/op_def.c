#include "op_def.h"

char *bsopcode(int id) {

    switch(id) {
        case ADD:
            return "000000";
        case ADDU:
            return "000000";
        case ADDI:
            return "001000";
        case ADDIU:
            return "001001";
        case AND:
            return "000000";
        case ANDI:
            return "001100";
        case CLO:
            return "011100";
        case CLZ:
            return "000000";
        case DIV:
            return "000000";
        case DIVU:
            return "000000";
        case MULT:
            return "000000";
        case MULTU:
            return "000000";
        case SRA:
            return "000000";
        case SRL:
            return "000000";
        default:
            printf("ERROR: ID not found.\n");
            return NULL;
    }

}

char *bsfunc(int id) {

    switch(id) {
        case ADD:
            return "100000";
        case ADDU:
            return "100001";
        case ADDI:
            return "------";
        case ADDIU:
            return "------";
        case AND:
            return "100100";
        case ANDI:
            return "------";
        case CLO:
            return "100001";
        case CLZ:
            return "100000";
        case DIV:
            return "011010";
        case DIVU:
            return "011011";
        case MULT:
            return "011000";
        case MULTU:
            return "011001";
        case SRA:
            return "000011";
        case SRL:
            return "000010";
        default:
            printf("ERROR: ID not found.\n");
            return NULL;
    }

}

char *regcode(unsigned int id) {

    if (id > 31) return NULL;

    return itbs(5, id);
}

