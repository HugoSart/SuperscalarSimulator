//
// Created by hsart on 09/07/17.
//

#ifndef SUPERSCALARSIMULATOR_SYSTEM_H_H
#define SUPERSCALARSIMULATOR_SYSTEM_H_H

#include <stdio.h>
#include "../machine/cpu/cpu.h"

#define COLOR_NORMAL            "\x1B[0m"
#define COLOR_GRAY              "\x1B[30m"
#define COLOR_RED               "\x1B[31m"
#define COLOR_GREEN             "\x1B[32m"
#define COLOR_YELLOW            "\x1B[33m"
#define COLOR_BLUE              "\x1B[34m"
#define COLOR_MAGENTA           "\x1B[35m"
#define COLOR_CYAN              "\x1B[36m"
#define COLOR_WHITE             "\x1B[38m"

#define COLOR_NORMAL_BRIGHT     "\x1B[0;1m"
#define COLOR_GRAY_BRIGHT       "\x1B[30;1m"
#define COLOR_RED_BRIGHT        "\x1B[31;1m"
#define COLOR_GREEN_BRIGHT      "\x1B[32;1m"
#define COLOR_YELLOW_BRIGHT     "\x1B[33;1m"
#define COLOR_BLUE_BRIGHT       "\x1B[34;1m"
#define COLOR_MAGENTA_BRIGHT    "\x1B[35;1m"
#define COLOR_CYAN_BRIGHT       "\x1B[36;1m"
#define COLOR_WHITE_BRIGHT      "\x1B[38;1m"

#define SET_COLOR(color)        printf(color)

#define SYSCALL_PRINT_INT 1
#define SYSCALL_READ_INT 5
#define SYSCALL_EXIT 10

void so_print_int(CPU *cpu);
void so_read_int(CPU *cpu);
void so_exit(CPU *cpu);

void so_load(Memory *mem, char *bfile_name);
void so_show_rcr(CPU *cpu);
void so_show_rrf(CPU *cpu);
int so_finished(CPU *cpu);

#endif //SUPERSCALARSIMULATOR_SYSTEM_H_H
