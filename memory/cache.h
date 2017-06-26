#ifndef SUPERSCALARSIMULATOR_CACHE_H
#define SUPERSCALARSIMULATOR_CACHE_H

#include <stdio.h>
#include "memory.h"

#define CACHE_SIZE 32000
#define CACHE_BLOCK_SIZE 4

typedef WORD BLOCK[CACHE_BLOCK_SIZE];

typedef struct {
    BLOCK *line;
    size_t size;
} cache_t;

cache_t cache_create(size_t size);


#endif //SUPERSCALARSIMULATOR_CACHE_H
