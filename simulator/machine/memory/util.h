#ifndef SUPERSCALARSIMULATOR_UTIL_H_H
#define SUPERSCALARSIMULATOR_UTIL_H_H

#define C_WORD(b1, b2, b3, b4) (Word){.byte[0] = b1, .byte[1] = b2, .byte[2] = b3, .byte[3] = b4}
#define M_WORD(word, a, b, c, d) \
    word = calloc(WORD_SIZE, sizeof(BYTE)); \
    word[0] = a; \
    word[1] = b; \
    word[2] = c; \
    word[3] = d;

#define WORD_SIZE 4

typedef unsigned char BYTE;
typedef union {
    BYTE byte[WORD_SIZE];
    unsigned int value;
} Word;

#endif //SUPERSCALARSIMULATOR_UTIL_H_H
