//
// Created by hsart on 16/07/17.
//

#ifndef SUPERSCALARSIMULATOR_FIFO_H
#define SUPERSCALARSIMULATOR_FIFO_H

#include <stdio.h>
#include "../types.h"

FIFO fifo_init();

void fifo_add(FIFO *fifo, Opcode code, EType type, InstructionRef ref);
Instruction fifo_remove(FIFO *fifo);
void fifo_print(FIFO *fifo);
size_t fifo_size(FIFO *fifo);


#endif //SUPERSCALARSIMULATOR_FIFO_H
