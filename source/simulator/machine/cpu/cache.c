#include <stdio.h>
#include <stdlib.h>
#include "cache.h"
#include "../util.h"

void miss_handler(Cache *, unsigned int);
Line get_memory_block(Cache *cache, unsigned int);

Cache cache_init(Memory *mem, size_t size) {

    if ((size % 4) != 0) {
        fprintf(stderr, "ERROR: cache size needs to be multiple of %d\n", CACHE_BLOCK_WORD_COUNT);
        return;
    }

    Cache cache;
    cache.mem = mem;
    cache.size = size;
    cache.line = malloc(LINE_COUNT(cache.size) * sizeof(Line));

    for (unsigned int i = 0; i < LINE_COUNT(cache.size); i++) {
        for (unsigned j = 0; j < WORD_SIZE; j++) {
            cache.line[i].word[j].value = 0;
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
                printf("%d", cache->line[l].word[i].byte[j]);
                if (j != WORD_SIZE - 1) printf(",");
            }
            printf("]\n");
        }
    }
    printf("\n------------------------------------------------\n");
}

Word cache_read(Cache *cache, unsigned int address) {

    Address a = {.full_address = WORD_ADDRESS(address)};

    if (a.mapped_address.tag != cache->line[a.mapped_address.line].tag) {
        miss_handler(cache, address);
    }
    printf("\n");
    return cache->line[a.mapped_address.line].word[a.mapped_address.byte / CACHE_BLOCK_WORD_COUNT];

}

void cache_write(Cache *cache, unsigned int address, Word word) {
    printf("WRITEEE!\n");
    Address a = {.full_address = WORD_ADDRESS(address)};

    if (a.mapped_address.tag != cache->line[a.mapped_address.line].tag) {
        miss_handler(cache, address);
    }

    cache->line[a.mapped_address.line].word[BLOCK_WORD_TAG(a.mapped_address.byte)].value = word.value;

}

Line get_memory_block(Cache *cache, unsigned int address) {
    printf("BLOCKKK!\n");
    address = BLOCK_ADDRESS(address);
    Address a = {.full_address = address};
    Line line = {.tag = a.mapped_address.tag};

    cache->_p_cpu->_p_mobo->control_bus.data.value = CONTROL_READ;
    cache->_p_cpu->_p_mobo->control_bus.busy = 1;
    cache->_p_cpu->_p_mobo->address_bus.data.decimal = address;
    cache->_p_cpu->_p_mobo->address_bus.busy = 1;

    // SIMULA um clock da RAM
    mem_clock(cache->mem);

    for (unsigned int i = 0; i < CACHE_BLOCK_WORD_COUNT; i++) {
        line.word[i] = cache->_p_cpu->_p_mobo->data_bus.data[i];
    }
    // ver se ta certo

    cache->_p_cpu->_p_mobo->control_bus.data.value = CONTROL_NOP;
    cache->_p_cpu->_p_mobo->control_bus.busy = NOT_BUSY;
    cache->_p_cpu->_p_mobo->address_bus.busy = NOT_BUSY;

    return line;

}

void miss_handler(Cache *cache, unsigned int address) {

    Address a = { .full_address = address };

    if (cache->line[a.mapped_address.line].tag != -1) {
        cache->_p_cpu->_p_mobo->control_bus.data.value = CONTROL_WRITE;
        cache->_p_cpu->_p_mobo->control_bus.busy = 1;
        a.mapped_address.tag = cache->line[a.mapped_address.line].tag;
        cache->_p_cpu->_p_mobo->address_bus.data.decimal = a.full_address;
        cache->_p_cpu->_p_mobo->address_bus.busy = 1;

        for (int i = 0; i < CACHE_BLOCK_WORD_COUNT; i++)
            cache->_p_cpu->_p_mobo->data_bus.data[i] = cache->line[a.mapped_address.line].word[i];
        cache->_p_cpu->_p_mobo->address_bus.busy = 1;

        // Simula clock da RAM
        mem_clock(cache->mem);
    }

    cache->_p_cpu->_p_mobo->control_bus.data.value = CONTROL_NOP;
    cache->_p_cpu->_p_mobo->control_bus.busy = NOT_BUSY;
    cache->_p_cpu->_p_mobo->address_bus.busy = NOT_BUSY;

    cache->line[a.mapped_address.line] = get_memory_block(cache, address);

}