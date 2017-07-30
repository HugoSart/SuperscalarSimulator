#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <ctype.h>
#include <string.h>
#include "simulator/machine/cpu/cpu.h"
#include "simulator/system/system.h"

int cbc;
int rrf;
int rcr;

int main(int argc, char **argv) {

    char *file_name = "";

    int c;
    while ((c = getopt(argc, argv, "f:m:s:")) != -1) {
        switch (c) {
            case 'f':
                file_name = optarg;
                break;
            case 'm':
                if (!strcmp(optarg, "cbc")) cbc = 1;
                break;
            case 's':
                if (!strcmp(optarg, "rrf")) rrf = 1;
                else if (!strcmp(optarg, "rcr")) rcr = 1;
                break;
            case '?':
                if (optopt == 'f')
                    fprintf(stderr, "Option -%c requires an argument.\n", optopt);
                else if (isprint(optopt))
                    fprintf(stderr, "Unknown option `-%c'.\n", optopt);
                else
                    fprintf(stderr, "Unknown option character `\\x%x'.\n", optopt);
                return 1;
            default:
                abort();
        }
    }

    Memory *mem = mem_new(MEM_SIZE, MEM_TEXT_ADDRESS);
    CPU *cpu = cpu_new(mem);

    for (int i = 0; i < strlen(file_name); i++)
        if (file_name[i] == '?') file_name[i] = ' ';

    so_load(mem, file_name);

    Mobo *mobo = mobo_new(cpu, mem);


    int clock = 0;
    while (!so_finished(cpu)) {
        if (cbc) printf("  Clock %d\n", clock);
        if (rcr && cbc) so_show_rcr(cpu);
        if (rrf && cbc) so_show_rrf(cpu);
        if (cbc) getchar();
        cpu_clock(cpu);
        clock++;
    }

    if (rcr) so_show_rcr(cpu);
    if (rrf) so_show_rrf(cpu);
    printf("\nTotal number of clocks : %d\n", clock);

    return EXIT_SUCCESS;
}