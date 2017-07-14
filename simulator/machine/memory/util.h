//
// Created by hsart on 03/07/17.
//

#ifndef SUPERSCALARSIMULATOR_UTIL_H_H
#define SUPERSCALARSIMULATOR_UTIL_H_H

#define WORD_SIZE 4

typedef unsigned char BYTE;
typedef union {
    BYTE byte[WORD_SIZE];
    unsigned int value;
} Word;

#define C_WORD (BYTE[WORD_SIZE])
#define M_WORD(word, a, b, c, d) \
    word = calloc(WORD_SIZE, sizeof(BYTE)); \
    word[0] = a; \
    word[1] = b; \
    word[2] = c; \
    word[3] = d;

#endif //SUPERSCALARSIMULATOR_UTIL_H_H
