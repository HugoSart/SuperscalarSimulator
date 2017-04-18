#include <stdio.h>
#include "memory.h"

int main() {

    Memory mem;
    mem_init(mem);
    mem_print(mem);
    Cell cell = {56,23,79,254};
    mem_write(&mem, 7, cell);
    mem_print(mem);

    return 0;
}