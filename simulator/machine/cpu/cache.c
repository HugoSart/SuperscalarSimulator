#include <stdio.h>
#include <stdlib.h>
#include "cache.h"

void miss_handler(Cache *, unsigned int);
BLOCK get_memory_block(Memory *, unsigned int);

Cache cache_init(Memory *mem, size_t size) {

    if ((size % 4) != 0) {
        sprintf(stderr, "ERROR: cache size needs to be multiple of %d\n", CACHE_BLOCK_WORD_COUNT);
        return;
    }

    Cache cache;
    cache.mem = mem;
    cache.size = size;
    cache.line = malloc(LINE_COUNT(cache.size) * sizeof(Line));

    for (unsigned int i = 0; i < LINE_COUNT(cache.size); i++) {
        cache.line[i].block = malloc(sizeof(BLOCK) * CACHE_BLOCK_WORD_COUNT);
        for (unsigned j = 0; j < WORD_SIZE; j++) {
            M_WORD(cache.line[i].block[j], 0, 0, 0, 0);
            cache.line[i].tag = UNDEFINED_TAG;
        }
    }

    return cache;

}

void cache_print(Cache *cache) {

    printf("---------- Cache<%zu Cells x %d Bytes> -----------\n\n", cache->size, WORD_SIZE);

    for (unsigned int l = 0; l < LINE_COUNT(cache->size); l++) {
        printf("Line %u \t--> %d\t", l, cache->line[l].tag);
        for (unsigned int i = 0; i < CACHE_BLOCK_WORD_COUNT; i++) {
            if (i != 0) printf("                ");
            printf("  [");
            for (unsigned j = 0; j < WORD_SIZE; j++) {
                printf("%d", cache->line[l].block[i][j]);
                if (j != WORD_SIZE - 1) printf(",");
            }
            printf("]\n");
        }
    }
    printf("\n------------------------------------------------\n");
}

WORD cache_read(Cache *cache, unsigned int address) {

    Address a;
    a.full_address = WORD_ADDRESS(address);

    if (a.mapped_address.tag != cache->line[a.mapped_address.line].tag) {
        miss_handler(cache, address);
    }
    printf("\n");
    return cache->line[a.mapped_address.line].block[a.mapped_address.byte / CACHE_BLOCK_WORD_COUNT];

}

void cache_write(Cache *cache, unsigned int address, WORD word) {

    Address a;
    a.full_address = WORD_ADDRESS(address);

    if (a.mapped_address.tag != cache->line[a.mapped_address.line].tag) {
        miss_handler(cache, address);
    }

    for (unsigned int i = 0; i < WORD_SIZE; i++) {
        cache->line[a.mapped_address.line].block[BLOCK_WORD_TAG(a.mapped_address.byte)][i] = word[i];
    }

}

BLOCK get_memory_block(Memory *mem, unsigned int address) {

    BLOCK block = malloc(CACHE_BLOCK_WORD_COUNT);
    address = BLOCK_ADDRESS(address);
    for (unsigned int i = 0; i < CACHE_BLOCK_WORD_COUNT; i++) {
        M_WORD(block[i], mem->mem[address++], mem->mem[address++], mem->mem[address++], mem->mem[address++]);
    }

    return block;

}

void miss_handler(Cache *cache, unsigned int address) {

    Address a = { .full_address = address };

    BLOCK block = get_memory_block(cache->mem, address);

    for (unsigned int i = 0; i < CACHE_BLOCK_WORD_COUNT; i++) {
        for (unsigned int j = 0; j < WORD_SIZE; j++) {
            cache->line[a.mapped_address.line % (LINE_COUNT(cache->size))].block[i][j] = block[i][j];
        }
    }
    cache->line[a.mapped_address.line % (LINE_COUNT(cache->size))].tag = a.mapped_address.tag;
}