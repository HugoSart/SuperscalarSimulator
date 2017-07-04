#ifndef SUPERSCALARSIMULATOR_CACHE_H
#define SUPERSCALARSIMULATOR_CACHE_H

#include <stdio.h>
#include "memory.h"

#define CACHE_SIZE 32000 // 4KB -> 250 blocos
#define CACHE_BLOCK_SIZE 4

typedef WORD BLOCK[CACHE_BLOCK_SIZE];

typedef struct cache_t {
    BLOCK *line;
    size_t size; // in bits
} Cache;

Cache *cache_create(size_t size);
size_t cache_line_count(Cache *cache);

#endif //SUPERSCALARSIMULATOR_CACHE_H
