#include <stdio.h>
#include "memory.h"

int main() {

    Memory mem = {0};
    mem_print(mem);
    Cell cell = {56,23,79,125};
    mem_write(mem, 7, cell);
    mem_print(mem);

    return 0;
}