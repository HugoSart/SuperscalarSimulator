#include <stdlib.h>
#include <stdio.h>
#include "memory/memory.h"
#include "memory/cache.h"

int main() {

    printf("size: %zu\n", cache_create(CACHE_SIZE)->size);

    return EXIT_SUCCESS;
}