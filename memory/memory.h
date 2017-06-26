#ifndef STANDARDCPROJECT_MEMORY_H
#define STANDARDCPROJECT_MEMORY_H

// 256M = 8388608 Cells

#define MEM_SIZE 512000000
//#define MEM_TEXT_ADDRESS 49548387
#define MEM_TEXT_ADDRESS 64000000
#define WORD_SIZE 4

#define WORD(b1, b2, b3, b4) {b1,b2,b3,b4}

typedef unsigned char BYTE;
typedef BYTE *MEMORY;
typedef BYTE WORD[WORD_SIZE];

typedef struct {
    MEMORY mem;
    size_t size;
    size_t text_address;
} mem_t;

// Type manipulation functions
mem_t mem_create(size_t size, size_t text_address);
void mem_destroy(mem_t *mem);
void mem_print(mem_t *mem);

// Data manipulation functions
void mem_write(mem_t *mem, int address, BYTE byte);
void mem_write_word(mem_t *mem, int address, WORD word);
BYTE mem_read(mem_t *mem, int address);

#endif //STANDARDCPROJECT_MEMORY_H
