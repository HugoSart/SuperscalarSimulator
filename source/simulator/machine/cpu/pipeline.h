//
// Created by hsart on 10/07/17.
//

#ifndef SUPERSCALARSIMULATOR_PIPELINE_H
#define SUPERSCALARSIMULATOR_PIPELINE_H

#include "../types.h"

// Pipeline struct defiened in cpu_pipeline.h

Pipeline pipe_init();
void pipe_fetch(CPU *);
void pipe_decode(CPU *);
void pipe_issue(CPU *);
void pipe_exec(CPU *);

#endif //SUPERSCALARSIMULATOR_PIPELINE_H
