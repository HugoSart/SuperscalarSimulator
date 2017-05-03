#include <stdio.h>
#include "memory/memory.h"

int main() {

    Memory mem = {0};
    mem_print(mem);
    Cell cell = {56,23,79,125};
    mem_write(mem, 7, cell);
    mem_print(mem);

    Cell *cell2 = mem_read(mem, 7);

    for(int j = 0; j < mem_cell_size; j++) {
        printf("%d", cell[j]);
        if (j != mem_cell_size - 1) printf(",");
    }

    return 0;
}