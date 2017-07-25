//
// Created by hsart on 09/07/17.
//

#ifndef SUPERSCALARSIMULATOR_ALU_H
#define SUPERSCALARSIMULATOR_ALU_H

#include "../types.h"

ALU alu_init();
int alu_exec(ALU *, EOperations, int, int);

#endif //SUPERSCALARSIMULATOR_ALU_H
