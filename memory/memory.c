#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include "memory.h"
#include "cache.h"

// Aux functions declarations
int check_address(Memory*, unsigned int);

// Implementation of declarations in memory.h
Memory mem_create(size_t size, size_t text_address) {
    Memory mem;
    mem.mem = calloc(size, sizeof(BYTE));
    mem.size = size;
    mem.text_address = text_address;
    return mem;
}

void mem_destroy(Memory *mem) {
    free(mem->mem);
    free(mem);
}

void mem_write(Memory *mem, unsigned int address, BYTE byte) {
    if (!check_address(mem, address)) return;
    mem->mem[address] = byte;
}

void mem_write_word(Memory *mem, unsigned int address, WORD word) {
    address = WORD_ADDRESS(address);
    if (!check_address(mem, address) || address % 4 != 0 && address + 3 >= mem->size) return;
    for (int i = 0; i < WORD_SIZE; i++) {
        mem_write(mem, address + i, word[i]);
    }
}

BYTE mem_read(Memory *mem, unsigned int address) {
    if (!check_address(mem, address)) return NULL;
    return mem->mem[address];
}

WORD mem_read_word(Memory *mem, unsigned int address) {
    if (!check_address(mem, address) || address % 4 != 0) return NULL;

    WORD word = C_WORD{mem->mem[address] ,  \
                    mem->mem[address + 1],  \
                    mem->mem[address + 2],  \
                    mem->mem[address + 3]};

    return word;

}

void mem_print(Memory *mem) {
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
int check_address(Memory *mem, unsigned int address) {
    if (address < 0 || address >= mem->size) return 0;
    else                                     return 1;
}