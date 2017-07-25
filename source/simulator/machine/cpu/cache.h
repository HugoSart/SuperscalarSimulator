#ifndef SUPERSCALARSIMULATOR_CACHE_H
#define SUPERSCALARSIMULATOR_CACHE_H

#include <stdio.h>
#include "../memory/memory.h"
#include "../types.h"

#define UNDEFINED_TAG -1

#define CACHE_SIZE 64//32768 // 2048 blocos
#define CACHE_BLOCK_WORD_COUNT 4

#define WORD_ADDRESS(address)   address - (address % (WORD_SIZE))
#define BLOCK_WORD_TAG(address) (address / WORD_SIZE) % (WORD_SIZE)
#define BLOCK_ADDRESS(address)  address - (address % (WORD_SIZE * CACHE_BLOCK_WORD_COUNT))
#define BLOCK_TAG(address)      address / (WORD_SIZE * CACHE_BLOCK_WORD_COUNT)
#define LINE_COUNT(size)        size / ((WORD_SIZE) * CACHE_BLOCK_WORD_COUNT)

Cache cache_init(Memory *mem, size_t size);
void cache_print(Cache *cache);
void cache_write(Cache *cache, unsigned int address, Word value);
Word cache_read(Cache *cache, unsigned int address);

#endif //SUPERSCALARSIMULATOR_CACHE_H
