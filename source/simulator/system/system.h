//
// Created by hsart on 09/07/17.
//

#ifndef SUPERSCALARSIMULATOR_SYSTEM_H_H
#define SUPERSCALARSIMULATOR_SYSTEM_H_H

#include <stdio.h>
#include "../machine/cpu/cpu.h"

#define COLOR_NORMAL            "\x1B[0m"
#define COLOR_YELLOW            "\x1B[33m"
#define COLOR_MAGENTA           "\x1B[35m"
#define COLOR_CYAN              "\x1B[36m"
#define COLOR_WHITE             "\x1B[37m"
#define COLOR_NORMAL_BRIGHT     "\x1B[0;1m"
#define COLOR_YELLOW_BRIGHT     "\x1B[33;1m"
#define COLOR_MAGENTA_BRIGHT    "\x1B[35;1m"
#define COLOR_CYAN_BRIGHT       "\x1B[36;1m"
#define COLOR_WHITE_BRIGHT      "\x1B[37;1m"

#define SET_COLOR(color)        printf(color)

void so_print_int(CPU *cpu);
int so_read_int();

void so_load(Memory *mem, char *bfile_name);
void so_show(CPU *cpu);

#endif //SUPERSCALARSIMULATOR_SYSTEM_H_H
