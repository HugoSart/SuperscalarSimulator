#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "memory.h"
#include "../cpu/cache.h"
#include "../util.h"


const char *byte_to_binary(int x) {
    static char b[9];
    b[0] = '\0';

    int z;
    for (z = 128; z > 0; z >>= 1)
    {
        strcat(b, ((x & z) == z) ? "1" : "0");
    }

    return b;
}

// Aux functions declarations
int check_address(Memory*, unsigned int);

// memory.h declarations implementations
Memory mem_init(size_t size, size_t text_address) {
    Memory mem;
    mem.byte = calloc(size, sizeof(BYTE));
    mem.size = size;
    mem.text_address = text_address;
    return mem;
}

void mem_destroy(Memory *mem) {
    free(mem->byte);
    free(mem);
}

void mem_write(Memory *mem, unsigned int address, BYTE byte) {
    if (!check_address(mem, address)) return;
    mem->byte[address] = byte;
}

void mem_write_word(Memory *mem, unsigned int address, Word word) {
    address = WORD_ADDRESS(address);
    if (!check_address(mem, address) || address % 4 != 0 && address + 3 >= mem->size) return;
    for (int i = 0; i < WORD_SIZE; i++) {
        mem_write(mem, address + i, word.byte[i]);
    }
}

BYTE mem_read(Memory *mem, unsigned int address) {
    if (!check_address(mem, address)) return NULL;
    return mem->byte[address];
}

Word mem_read_word(Memory *mem, unsigned int address) {
    Address a = {.full_address = WORD_ADDRESS(address)};
    Word word = {0};
    for (unsigned int i = 0; i < WORD_SIZE; i++) {
        word.byte[i] = mem->byte[a.full_address + i];
    }

    return word;

}

/*void mem_print(Memory *mem, Cache *cache) {
    printf("======================= Memory <%zuB> =======================\n\n", mem->size, WORD_SIZE);
    printf("%7c", ' ');

    for(int i = 0; i < 16; i++) {
        printf("%s%02X%s ", COLOR_WHITE, i, COLOR_NORMAL);
    }

    //printf("        ------------------------------------------------- ");
    for(int i = 0; i < mem->size; i ++) {
        //if (i != 0 && i % 16 == 0) printf("|");

        if (i % 16 == 0) printf("\n  %s%04X%s ", COLOR_WHITE, i, COLOR_NORMAL);

        if (i >= MEM_TEXT_ADDRESS)  SET_COLOR(COLOR_CYAN);
        else                        SET_COLOR(COLOR_MAGENTA);
        if (mem->mem[i] != 0)
            if (i >= MEM_TEXT_ADDRESS) SET_COLOR(COLOR_CYAN_BRIGHT);
            else                       SET_COLOR(COLOR_MAGENTA_BRIGHT);

        printf("%02X", mem->mem[i]);

        SET_COLOR(COLOR_NORMAL);

        printf(" ");
        if ((i % 16) == 15 && i < cache->size) {
            for (int j = i; j < i + 16; j++) {
                if (j % 16 == 0) printf("\n  %s%04X%s ", COLOR_WHITE, i, COLOR_NORMAL);
                printf("%02X", cache->mem[i]);
            }
        }

    }
    //printf("|\n        -------------------------------------------------");

    printf("\n\n=================================================================\n");
    for(int i = 0; i < 16; i++) {
        printf("%u ", mem->mem[0x00110 + i]);
    }
}*/

// Aux functions
int check_address(Memory *mem, unsigned int address) {
    if (address < 0 || address >= mem->size) return 0;
    else                                     return 1;
}