#ifndef SUPERSCALARSIMULATOR_CACHE_H
#define SUPERSCALARSIMULATOR_CACHE_H

#include <stdio.h>
#include "memory.h"

#define UNDEFINED_TAG -1

#define CACHE_SIZE 64//32768 // 2048 blocos
#define CACHE_BLOCK_WORD_COUNT 4

#define WORD_ADDRESS(address)  address - (address % (WORD_SIZE))
#define BLOCK_ADDRESS(address) address - (address % (WORD_SIZE * CACHE_BLOCK_WORD_COUNT))
#define BLOCK_TAG(address)     address / (WORD_SIZE * CACHE_BLOCK_WORD_COUNT)
#define LINE_COUNT(size)       size / ((WORD_SIZE) * CACHE_BLOCK_WORD_COUNT)

typedef WORD *BLOCK;

struct dec_t {
    unsigned int byte : 4;
    unsigned int line : 1; // 11
    unsigned int tag  : 7; // 14
};

typedef union dec_address {
    unsigned int full_address;
    struct dec_t mapped_address;
} Address;

typedef struct line_t {
    int tag;
    BLOCK block;
} Line;

typedef struct cache_t {
    Memory *mem;
    Line *line;
    size_t size; // in bits
} Cache;

Cache cache_create(Memory *mem, size_t size);
size_t cache_line_count(Cache *cache);
void cache_print(Cache *cache);

void cache_write(Cache *cache, unsigned int address, WORD value);
WORD cache_read(Cache *cache, unsigned int address);

#endif //SUPERSCALARSIMULATOR_CACHE_H
