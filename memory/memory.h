#ifndef STANDARDCPROJECT_MEMORY_H
#define STANDARDCPROJECT_MEMORY_H

// 256M = 8388608 Cells

#include <stdio.h>
#include "util.h"

#define MEM_SIZE 256
//#define MEM_TEXT_ADDRESS 49548387
#define MEM_TEXT_ADDRESS 64000000

typedef BYTE *MEMORY;

typedef struct mem_t {
    MEMORY mem;
    size_t size;
    size_t text_address;
} Memory;

// Type manipulation functions
Memory mem_create(size_t size, size_t text_address);
void mem_destroy(Memory *mem);
void mem_print(Memory *mem);

// Data manipulation functions
void mem_write(Memory *mem, unsigned int address, BYTE byte);
void mem_write_word(Memory *mem, unsigned int address, WORD word);
BYTE mem_read(Memory *mem, unsigned int address);
WORD mem_read_word(Memory *mem, unsigned int address);

#endif //STANDARDCPROJECT_MEMORY_H
