//
// Created by hsart on 10/07/17.
//

#ifndef SUPERSCALARSIMULATOR_CPU_PIPELINE_H_H
#define SUPERSCALARSIMULATOR_CPU_PIPELINE_H_H

#include <stdio.h>
#include "memory/util.h"

typedef unsigned char BYTE;

// Pipeline definitions
enum stages_e {
    FETCH, DECODE, EXEC, MEM_ACCESS, WRITE_BACK,
    STAGE_COUNT
} EStage;
typedef struct {
    int pc, ri;
    void (*stage[STAGE_COUNT])(unsigned int);
} Pipeline;

// CPU definitions

#endif //SUPERSCALARSIMULATOR_CPU_PIPELINE_H_H
