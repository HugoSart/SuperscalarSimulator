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
    mem_write_word(&mem, 32, C_WORD{13,14,15,16});
    mem_write_word(&mem, 128, C_WORD{128,14,15,16});
    mem_write_word(&mem, 90, C_WORD{67,14,15,16});
    mem_print(&mem);

    Cache cache = cache_create(&mem, CACHE_SIZE);
    cache_read(&cache, 4);
    cache_read(&cache, 17);
    cache_read(&cache, 48);
    cache_read(&cache, 32);
    cache_read(&cache, 63);
    cache_read(&cache, 64);
    cache_read(&cache, 90);
    cache_read(&cache, 128);
    cache_read(&cache, 129);
    cache_read(&cache, 133);
    cache_write(&cache, 0, C_WORD{2,2,2,2});
    cache_write(&cache, 7, C_WORD{2,7,2,2});
    cache_write(&cache, 88, C_WORD{5,7,2,2});
    cache_write(&cache, 92, C_WORD{5,8,2,2});
    cache_write(&cache, 53, C_WORD{5,15,2,2});
    cache_print(&cache);

    return EXIT_SUCCESS;
}