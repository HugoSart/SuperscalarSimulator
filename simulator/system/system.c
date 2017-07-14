//
// Created by hsart on 09/07/17.
//

#include <stdio.h>
#include <stdio_ext.h>
#include <stdlib.h>
#include "system.h"
#include "../machine/memory/memory.h"
#include "../machine/types.h"
#include "../machine/memory/util.h"

void so_load(Memory *mem, char *bfile_name) {

    FILE *file;

    if (!(file = fopen(bfile_name, "rb"))) {
        fprintf(stderr, "ERROR: can't open file %s, or file doesn't exists.\n", bfile_name);
        return;
    }

    for (size_t i = mem->text_address; i < mem->text_address + 400; fread(&mem->byte[i], sizeof(BYTE), 1, file), i++);
    for (size_t i = 0; i < mem->text_address; fread(&mem->byte[i], sizeof(BYTE), 1, file), i++);

}

void so_show(CPU *cpu) {

    Memory *mem = cpu->cache.mem;
    Cache cache = cpu->cache;

    printf("\n%23cRAM MEMORY%45cCACHE MEMORY%26cREGISTERS\n\n", ' ', ' ', ' ');

    printf("%7c", ' ');

    for(int i = 0; i < 16; i++) {
        printf("%s%02X%s ", COLOR_WHITE, i, COLOR_NORMAL);
    }
    printf("%7c", ' ');
    for(int i = 0; i < 16; i++) {
        printf("%s%02d%s ", COLOR_WHITE, i, COLOR_NORMAL);
    }
    printf("  %sRegister %s$%u%s %*c: %s%u", COLOR_YELLOW, COLOR_YELLOW_BRIGHT, 0, COLOR_YELLOW, 2, ' ', COLOR_NORMAL, cpu->reg_set.reg[0].value);
    int line = 0, line2 = 1;
    //printf("        ------------------------------------------------- ");
    for(unsigned int i = 0; i < mem->size; i ++) {
        //if (i != 0 && i % 16 == 0) printf("|");
        if (i % 16 == 0) {
            printf("\n");
            printf("  %s%04X%s ", COLOR_WHITE, i, COLOR_NORMAL);
        }

        if (i >= mem->text_address)  SET_COLOR(COLOR_CYAN);
        else                         SET_COLOR(COLOR_MAGENTA);
        if (mem->byte[i] != 0)
            if (i >= mem->text_address) SET_COLOR(COLOR_CYAN_BRIGHT);
            else                        SET_COLOR(COLOR_MAGENTA_BRIGHT);

        printf("%02X ", mem->byte[i]);

        SET_COLOR(COLOR_NORMAL);

        if ((i % 16) == 15 && i < cache.size) {
            if (line == 0) {

            }
            printf("  %s%04d%s ", COLOR_WHITE, cache.line[line].tag, COLOR_NORMAL);
            for (unsigned int j = 0; j < 4; j++) {

                for (unsigned int b = 0; b < 4; b++) {
                    if (cache.line[line].word[j].byte[b] != 0) SET_COLOR(COLOR_MAGENTA_BRIGHT);
                    else
                        SET_COLOR(COLOR_MAGENTA);
                    printf("%02X ", cache.line[line].word[j].byte[b]);
                }
            }
            line++;
        }
        if ((i % 16) == 15 && line2 < 32) {
            if (i >= cache.size) printf("%55c", ' ');
            int space = 1;
            if (line2 < 10) space = 2;
            printf("  %sRegister %s$%u%s %*c: %s%u", COLOR_YELLOW, COLOR_YELLOW_BRIGHT, line2, COLOR_YELLOW, space, ' ', COLOR_NORMAL, cpu->reg_set.reg[line2].value);
            line2++;
        }

    }
    printf("\n");
    //printf("|\n        -------------------------------------------------");


}

