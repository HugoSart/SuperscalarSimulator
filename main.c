#include <stdio.h>
#include <stdlib.h>
#include "memory/util.h"
#include "memory/memory.h"
#include "memory/cache.h"

int main() {

    Memory mem = mem_create(MEM_SIZE, 32);
    mem_write_word(&mem, 4,  C_WORD{1,2,3,4});
    mem_write_word(&mem, 48,  C_WORD{5,6,7,8});
    mem_write_word(&mem, 60, C_WORD{9,10,11,12});
    mem_write_word(&mem, 84, C_WORD{13,14,15,16});
    mem_print(&mem);

    Cache cache = cache_create(&mem, CACHE_SIZE);
    cache_read(&cache, 62);
    cache_read(&cache, 62);
    cache_print(&cache);

    return EXIT_SUCCESS;
}