//
// Created by hsart on 09/07/17.
//

#include <stdio.h>
#include <string.h>
#include "system.h"
#include "../machine/cpu/rstation.h"
#include "../machine/cpu/types.h"
#include "../machine/cpu/structures/fifo.h"

void so_load(Memory *mem, char *bfile_name) {

    FILE *file;

    if (!(file = fopen(bfile_name, "rb"))) {
        fprintf(stderr, "ERROR: can't open file %s, or file doesn't exists.\n", bfile_name);
        return;
    }

    for (size_t i = mem->text_address; i < mem->text_address + 400; fread(&mem->byte[i], sizeof(BYTE), 1, file), i++);
    for (size_t i = 0; i < mem->text_address; fread(&mem->byte[i], sizeof(BYTE), 1, file), i++);

}

void so_show_rcr(CPU *cpu) {

    Memory *mem = cpu->cache.mem;
    Cache cache = cpu->cache;

    printf("\n%s%23cRAM MEMORY%45cCACHE MEMORY%26cREGISTERS%s\n\n", COLOR_WHITE_BRIGHT, ' ', ' ', ' ', COLOR_WHITE_BRIGHT);

    printf("%7c", ' ');

    for(int i = 0; i < 16; i++) {
        printf("%s%02X%s ", COLOR_WHITE, i, COLOR_NORMAL);
    }
    printf("%7c", ' ');
    for(int i = 0; i < 16; i++) {
        printf("%s%02d%s ", COLOR_WHITE, i, COLOR_NORMAL);
    }
    printf("  %sRegister %s$%u%s %*c: %s%d", COLOR_YELLOW, COLOR_YELLOW_BRIGHT, 0, COLOR_YELLOW, 2, ' ', COLOR_NORMAL, cpu_reg_get(cpu, 0));
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
            printf("  %sRegister %s$%u%s %*c: %s%d", COLOR_YELLOW, COLOR_YELLOW_BRIGHT, line2, COLOR_YELLOW, space, ' ', COLOR_NORMAL, cpu_reg_get(cpu, line2));
            line2++;
        }

    }
    printf("\n");
    //printf("|\n        -------------------------------------------------");


}

void so_show_rrf(CPU *cpu) {

    printf("\n%s%8cREGISTERS%25cRESERVATION STATIONS%s\n\n", COLOR_WHITE_BRIGHT, ' ', ' ', COLOR_WHITE_BRIGHT);

    for (int i = 0; i < 32; i++) {
        int space = 1;
        if (i < 10) space = 2;
        printf("%4c%sRegister %s$%u%s %*c: %s%d\t", ' ', COLOR_YELLOW, COLOR_YELLOW_BRIGHT, i, COLOR_YELLOW, \
               space, ' ', COLOR_NORMAL, cpu_reg_get(cpu, i));

        Node *current = cpu->pipeline.queue.first;
        if (i == 0) printf("%10c%sNAME  BUSY    OP   Vj  Vk  Qj  Qk  A%s ", ' ', COLOR_CYAN, COLOR_NORMAL);

        size_t size = fifo_size(&cpu->pipeline.queue);
        int i2 = i - 1;
        if (i2 < 5 && i2 >= 0) {
            printf("%10c", ' ');
            char name[10];
            switch (cpu->rstation[i2].type) {
                case RS_ADD:
                    strcpy(name, "ADDI");
                    break;
                case RS_MUL:
                    strcpy(name, "MULT");
                    break;
                case RS_LOAD:
                    strcpy(name, "LOAD");
                    break;
                case RS_STORE:
                    strcpy(name, "STOR");
                    break;
                default:
                    strcpy(name, "????");
            }
            printf("%s  ", name);

            if (cpu->rstation[i2].busy == true) printf("%sYes%s", COLOR_RED, COLOR_NORMAL);
            else                                printf("%sNo %s", COLOR_GREEN, COLOR_NORMAL);

            if (cpu->rstation[i2].op.realization == NULL) printf("          ");

            if (cpu->rstation[i2].vj != RS_UNDEFINED) printf("%02d ", cpu->rstation[i2].vj);
            else                                      printf("    ");
            if (cpu->rstation[i2].vj != RS_UNDEFINED) printf("%02d ", cpu->rstation[i2].vk);
            else                                      printf("    ");
            if (cpu->rstation[i2].vj != RS_UNDEFINED) printf("%02d ", cpu->rstation[i2].qj);
            else                                      printf("    ");
            if (cpu->rstation[i2].vj != RS_UNDEFINED) printf("%02d ", cpu->rstation[i2].qk);
            else                                      printf("    ");

        }

        if (i == 7) {
            printf("%10c%sInstruction Queue -> %s", ' ', COLOR_BLUE_BRIGHT, COLOR_NORMAL);
            fifo_print(&cpu->pipeline.queue);
        }

        printf("\n");
    }
}

