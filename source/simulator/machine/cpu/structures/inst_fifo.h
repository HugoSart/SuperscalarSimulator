//Bus
// Created by hsart on 16/07/17.
//

#ifndef SUPERSCALARSIMULATOR_FIFO_H
#define SUPERSCALARSIMULATOR_FIFO_H

#include <stdio.h>
#include "../types.h"

IFIFO ififo_init();

void ififo_add(IFIFO *fifo, Opcode code, ERType type, InstructionRef *ref);
Instruction ififo_remove(IFIFO *fifo);
void ififo_print(IFIFO *fifo);
size_t ififo_size(IFIFO *fifo);


#endif //SUPERSCALARSIMULATOR_FIFO_H
