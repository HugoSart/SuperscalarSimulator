#ifndef STANDARDCPROJECT_MEMORY_H
#define STANDARDCPROJECT_MEMORY_H

// 256M = 8388608 Cells

#include <stdio.h>
#include "../util.h"
#include "../types.h"
#include "../motherboard/mobo.h"
#include "../cpu/rstation.h"

#define MEM_SIZE 536870912
//#define MEM_TEXT_ADDRESS 49548387
#define MEM_TEXT_ADDRESS 67108864

#define CONTROL_NOP   0
#define CONTROL_READ  1
#define CONTROL_WRITE 2

// Type manipulation functions
Memory *mem_new(size_t size, size_t text_address);
void mem_destroy(Memory *mem);
//void mem_print(Memory *mem, Cache *cache);

// Data manipulation functions
void mem_write(Memory *mem, unsigned int address, BYTE byte);
void mem_write_word(Memory *mem, unsigned int address, Word word);
BYTE mem_read(Memory *mem, unsigned int address);
Word mem_read_word(Memory *mem, unsigned int address);

void mem_clock(Memory *mem);

#endif //STANDARDCPROJECT_MEMORY_H
