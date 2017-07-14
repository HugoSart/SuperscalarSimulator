#ifndef STANDARDCPROJECT_MEMORY_H
#define STANDARDCPROJECT_MEMORY_H

// 256M = 8388608 Cells

#include <stdio.h>
#include "util.h"
#include "../types.h"

#define MEM_SIZE 512
//#define MEM_TEXT_ADDRESS 49548387
#define MEM_TEXT_ADDRESS 64


// Type manipulation functions
Memory mem_init(size_t size, size_t text_address);
void mem_destroy(Memory *mem);
void mem_print(Memory *mem, Cache *cache);

// Data manipulation functions
void mem_write(Memory *mem, unsigned int address, BYTE byte);
void mem_write_word(Memory *mem, unsigned int address, WORD word);
BYTE mem_read(Memory *mem, unsigned int address);
WORD mem_read_word(Memory *mem, unsigned int address);

#endif //STANDARDCPROJECT_MEMORY_H
