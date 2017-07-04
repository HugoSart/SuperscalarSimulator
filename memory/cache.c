#include <stdio.h>
#include <stdlib.h>
#include "cache.h"

Cache *cache_create(size_t size) {
    if (size % 4 != 0) {
        sprintf(stderr, "ERROR: cache size needs to be multiple of %d\n", CACHE_BLOCK_SIZE);
        return NULL;
    }
    Cache *cache = malloc(sizeof(cache));
    cache->size = size;
    cache->line = malloc((size / 8) / 16);
    return cache;
}

size_t cache_line_count(Cache *cache) {
    return (cache->size / 8) / 16;
}

