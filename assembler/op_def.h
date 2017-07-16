//
// Created by hsart on 03/05/17.
//

#ifndef SUPERSCALARSIMULATOR_OP_DEF_H
#define SUPERSCALARSIMULATOR_OP_DEF_H

#include <stdio.h>
#include "bop.h"
#include "../source/simulator/machine/cpu/instructions.h"

int opcode(unsigned int id);
int func(unsigned int id);
char *regcode(unsigned int id);

#endif //SUPERSCALARSIMULATOR_OP_DEF_H
