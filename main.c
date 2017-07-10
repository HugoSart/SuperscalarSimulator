#include <stdio.h>
#include <stdlib.h>
#include "simulator/machine/cpu/cpu.h"
#include "simulator/machine/cpu/registers.h"

#define FUNC_4(r, a, b, c) ()

int main() {

    int a = 2, b = 25;
    printf("Result: %d\n", a & b);

    return EXIT_SUCCESS;
}