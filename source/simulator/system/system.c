//
// Created by hsart on 09/07/17.
//

#include <stdio.h>
#include <string.h>
#include "system.h"
#include "../machine/cpu/rstation.h"
#include "../machine/types.h"
#include "../machine/cpu/structures/inst_fifo.h"
#include "../machine/cpu/register.h"
#include "../machine/util.h"
#include "../machine/cpu/structures/cdb_fifo.h"

void so_print_int(CPU *cpu) {
    printf("print_int: %d\n", cpu_reg_get(cpu, A0)->content.value);
}

void so_read_int(CPU *cpu) {
    printf("read_int: ");
    scanf("%d", &cpu->reg[V0].content.value);
}

void so_exit(CPU *cpu) {
    exit(EXIT_SUCCESS);
}

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
    printf("  %sRegister %s$%s%s %*c: %s%d", COLOR_YELLOW, COLOR_YELLOW_BRIGHT, reg_name(0), COLOR_YELLOW, 2, ' ', COLOR_NORMAL, cpu_reg_get(cpu, 0)->content.value);
    int line = 0, line2 = 1;
    //printf("        ------------------------------------------------- ");
    for(unsigned int i = 0; i < mem->size; i ++) {
        //if (i != 0 && i % 16 == 0) printf("|");
        if (i % 16 == 0) {
            printf("\n");
            printf("  %s%04X%s ", COLOR_WHITE, i, COLOR_NORMAL);
        }

        if (i >= cpu->reg[SP].content.decimal)  SET_COLOR(COLOR_RED);
        else if (i >= mem->text_address) SET_COLOR(COLOR_CYAN);
        else                         SET_COLOR(COLOR_MAGENTA);
        if (mem->byte[i] != 0)
            if (i >= cpu->reg[SP].content.decimal) SET_COLOR(COLOR_RED_BRIGHT);
            else if (i >= mem->text_address) SET_COLOR(COLOR_CYAN_BRIGHT);
            else                        SET_COLOR(COLOR_MAGENTA_BRIGHT);
        if (cpu->pipeline.pc.value == WORD_ADDRESS(i)) SET_COLOR(COLOR_BLUE_BRIGHT);

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
            printf("  %sRegister %s$%s%s %*c: %s%d", COLOR_YELLOW, COLOR_YELLOW_BRIGHT, reg_name(line2), COLOR_YELLOW, space, ' ', COLOR_NORMAL, cpu_reg_get(cpu, line2)->content.value);
            line2++;
        }

    }
    printf("\n");
    //printf("|\n        -------------------------------------------------");


}

void so_show_rrf(CPU *cpu) {

    printf("\n%s%13cREGISTERS%s%42cRESERVATION STATIONS%s\n\n", COLOR_WHITE_BRIGHT, ' ', COLOR_NORMAL, ' ', COLOR_WHITE_BRIGHT);

    for (int i = 0; i < REG_COUNT_2; i++) {
        int space = 1;
        if (i == 32) printf("\n");
        if (i < 10) space = 2;
        printf("%2c", ' ');
        if (cpu->reg[i].rstation != NULL) printf("%s [%d]%s", COLOR_RED, rstation_index(cpu, cpu->reg[i].rstation), COLOR_NORMAL);
        else printf("    ");
        if (i == 0) printf(" %sRegister %s$%s%s : %s%6d\t", COLOR_YELLOW, COLOR_YELLOW_BRIGHT, reg_name(i), COLOR_YELLOW, COLOR_NORMAL, cpu_reg_get(cpu, i)->content.value);
        else        printf(" %sRegister %s$%s%s   : %s%6d\t", COLOR_YELLOW, COLOR_YELLOW_BRIGHT, reg_name(i), COLOR_YELLOW, COLOR_NORMAL, cpu_reg_get(cpu, i)->content.value);

        INode *current = cpu->pipeline.queue.first;
        if (i == 0) printf("%10c%sNAME  BUSY  MNEMONIC      Vj      Vk      Qj      Qk       A%s ", ' ', COLOR_CYAN, COLOR_NORMAL);

        size_t size = ififo_size(&cpu->pipeline.queue);
        int i2 = i - 1;
        if (i2 < RS_COUNT && i2 >= 0) {
            printf("%10c", ' ');
            char name[10];
            switch (cpu->pipeline.rstation[i2].type) {
                case RS_TYPE_ADD:
                    strcpy(name, "ADDI");
                    break;
                case RS_TYPE_MUL:
                    strcpy(name, "MULT");
                    break;
                case RS_TYPE_LOAD:
                    strcpy(name, "LOAD");
                    break;
                case RS_TYPE_STORE:
                    strcpy(name, "STOR");
                    break;
                default:
                    strcpy(name, "????");
            }
            printf("%s  ", name);

            if (cpu->pipeline.rstation[i2].busy >  0)           printf("%s%02d%s", COLOR_RED, cpu->pipeline.rstation[i2].busy, COLOR_NORMAL);
            else if (cpu->pipeline.rstation[i2].busy == 0)      printf("%s%02d%s", COLOR_BLUE, cpu->pipeline.rstation[i2].busy, COLOR_NORMAL);
            else                                                printf("%sNo%s", COLOR_GREEN, COLOR_NORMAL);

            if (cpu->pipeline.rstation[i2].instruction.ref == NULL) printf("              ");
            else                                                    printf("    %s%*c  ", cpu->pipeline.rstation[i2].instruction.ref->mnemonic, 8 - strlen(cpu->pipeline.rstation[i2].instruction.ref->mnemonic), ' ');

            if (cpu->pipeline.rstation[i2].vj != 0)  printf("%6d  ", cpu->pipeline.rstation[i2].vj);
            else                                     printf("%6c  ", ' ');
            if (cpu->pipeline.rstation[i2].vk != 0)  printf("%6d  ", cpu->pipeline.rstation[i2].vk);
            else                                     printf("%6c  ", ' ');
            if (cpu->pipeline.rstation[i2].qj != RS_UNKNOWN) printf("%6d  ", cpu->pipeline.rstation[i2].qj);
            else                                     printf("%6c  ", ' ');
            if (cpu->pipeline.rstation[i2].qk != RS_UNKNOWN) printf("%6d  ", cpu->pipeline.rstation[i2].qk);
            else                                     printf("%6c  ", ' ');
            if (cpu->pipeline.rstation[i2].A != 0)   printf("%6d  ", cpu->pipeline.rstation[i2].A);

        }

        if (i == 17) {
            printf("%10c%sInstruction Queue -> %s", ' ', COLOR_BLUE_BRIGHT, COLOR_NORMAL);
            ififo_print(&cpu->pipeline.queue);
        }

        if (i == 19) {
            printf("%10c%sCDB Queue -> %s", ' ', COLOR_BLUE_BRIGHT, COLOR_NORMAL);
            cdbfifo_print(&cpu->cdb.queue);
        }

        if (i == 20) {
            if (cpu->cdb.tag != RS_UNKNOWN) printf("%10c%sTag  : %s%d", ' ', COLOR_BLUE, COLOR_NORMAL, cpu->cdb.tag);
            else                            printf("%10c%sTag  : %s", ' ', COLOR_BLUE, COLOR_NORMAL);
        }

        if (i == 21) {
            if (cpu->cdb.destination != REG_UNKNOWN) printf("%10c%sDest : %s%d", ' ', COLOR_BLUE, COLOR_NORMAL, cpu->cdb.destination);
            else                            printf("%10c%sDest : %s", ' ', COLOR_BLUE, COLOR_NORMAL);
        }

        if (i == 22) {
            if (cpu->cdb.data.value != 0) printf("%10c%sData : %s%d", ' ', COLOR_BLUE, COLOR_NORMAL, cpu->cdb.data.value);
            else printf("%10c%sData : %s", ' ', COLOR_BLUE, COLOR_NORMAL);
        }

        if (i == 24) {
            printf("          %sIssue : %s", COLOR_GREEN_BRIGHT, COLOR_GREEN);
            if (cpu->pipeline.issue == ISSUE_STOP) printf("%sstopped", COLOR_RED);
            else    printf("issuing");
            printf("%s", COLOR_NORMAL);
        }

        printf("\n");
    }
}

int so_finished(CPU *cpu) {

    int allClean = 1;
    for (int r = 0; r < RS_COUNT; r++)
        if (cpu_rstation(cpu, r)->busy != NOT_BUSY) {
            allClean = 0;
            break;
        }

    return cpu->pipeline.ri.value == EOF && allClean == 1 && cpu->cdb.destination == REG_UNKNOWN && cpu->pipeline.queue.first == NULL;

}

