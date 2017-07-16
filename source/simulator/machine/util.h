#ifndef SUPERSCALARSIMULATOR_UTIL_H_H
#define SUPERSCALARSIMULATOR_UTIL_H_H

#include <stdlib.h>

#define WORD_SIZE 4
#define C_WORD(b1, b2, b3, b4) (Word){.byte[0] = b1, .byte[1] = b2, .byte[2] = b3, .byte[3] = b4}

typedef unsigned char BYTE;

typedef union {
    BYTE byte[WORD_SIZE];
    unsigned int decimal;
    int value;
} Word;

#endif //SUPERSCALARSIMULATOR_UTIL_H_H
