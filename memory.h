#ifndef STANDARDCPROJECT_MEMORY_H
#define STANDARDCPROJECT_MEMORY_H

// 256M = 8388608 Cells

#define mem_size 64
#define mem_cell_size 4

typedef unsigned char Byte;
typedef Byte Cell[mem_cell_size];
typedef Cell Memory[mem_size];

void mem_write(Memory mem, int address, Cell cell) {
    if (address < 0 || address >= mem_size) return;

    for (int i = 0; i < mem_cell_size; i++) {
        mem[address][i] = cell[i];
    }

}

Cell *mem_read(Memory mem, int address) {
    if (address < 0 || address >= mem_size) return NULL;
    return mem[address];
}

void mem_print(Memory mem) {
    printf("--------- Memory<%d Cells x %d Bytes> ----------\n", mem_size, mem_cell_size);

    for(int i = 0; i < mem_size; i++) {
        printf("\n  %d \t-> [", i);
        for(int j = 0; j < mem_cell_size; j++) {
            printf("%d", mem[i][j]);
            if (j != mem_cell_size - 1) printf(",");
        }
        printf("]");
    }

    printf("\n\n------------------------------------------------\n");
}

#endif //STANDARDCPROJECT_MEMORY_H
