#include <stdio.h>
#include <malloc.h>
#include "memory.h"

// Aux functions declarations
int check_address(mem_t*, int);

// Implementation of declarations in memory.h
mem_t mem_create(size_t size, size_t text_address) {
    mem_t mem;
    mem.mem = calloc(size, sizeof(BYTE));
    mem.size = size;
    mem.stack_address = size - 1;
    mem.text_address = text_address;
    return mem;
}

void mem_destroy(mem_t *mem) {
    free(mem->mem);
    free(mem);
}

void mem_write(mem_t *mem, int address, BYTE byte) {
    if (!check_address(mem, address)) return;
    mem->mem[address] = byte;
}

void mem_write_word(mem_t *mem, int address, WORD word) {
    if (!check_address(mem, address) || address % 4 != 0 && address + 3 >= mem->size) return;
    for (int i = 0; i < WORD_SIZE; i++) {
        mem_write(mem, address + i, word[i]);
    }
}

BYTE mem_read(mem_t *mem, int address) {
    if (!check_address(mem, address)) return NULL;
    return mem->mem[address];
}

void mem_print(mem_t *mem) {
    printf("--------- Memory<%zu Cells x %d Bytes> ----------\n", mem->size, WORD_SIZE);

    for(int i = 0; i < mem->size; i += WORD_SIZE) {
        printf("\n  %d-%d   \t-> [", i, i + WORD_SIZE - 1);
        for(int j = 0; j < WORD_SIZE; j++) {
            printf("%d", mem->mem[i + j]);
            if (j != WORD_SIZE - 1) printf(",");
        }
        printf("]");
    }

    printf("\n\n------------------------------------------------\n");
}

// Aux function
int check_address(mem_t *mem, int address) {
    if (address < 0 || address >= mem->size) return 0;
    else                                     return 1;
}