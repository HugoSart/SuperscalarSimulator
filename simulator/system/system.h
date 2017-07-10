//
// Created by hsart on 09/07/17.
//

#ifndef SUPERSCALARSIMULATOR_SYSTEM_H_H
#define SUPERSCALARSIMULATOR_SYSTEM_H_H

#include <stdio.h>
#include "../machine/cpu/cpu.h"
#include "../machine/cpu/registers.h"

void so_print_int(CPU *cpu) {
    printf("%d\n", cpu->reg_set.reg[A0]);
}

int so_read_int()

#endif //SUPERSCALARSIMULATOR_SYSTEM_H_H
