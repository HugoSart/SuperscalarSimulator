#include <stdlib.h>
#include <stdio.h>
#include "memory/memory.h"

int main() {

    mem_t mem = mem_create(512, 64);
    WORD word = {255,255,255,255};
    mem_write_word(&mem, 12, word);

    return EXIT_SUCCESS;
}