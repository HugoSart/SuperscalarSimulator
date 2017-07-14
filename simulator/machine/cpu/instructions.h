//
// Created by hsart on 09/07/17.
//

#ifndef SUPERSCALARSIMULATOR_INSTRUCTIONS_H
#define SUPERSCALARSIMULATOR_INSTRUCTIONS_H

#include <stdarg.h>
#include "../types.h"

#define ARG_3  (REGISTER *rd, REGISTER *rs, REGISTER *rt)
#define ARG_3I (REGISTER *r1, REGISTER *r2, int imm)
#define ARG_3S (REGISTER *r1, REGISTER *r2, unsigned int shamt)
#define ARG_2  (REGISTER *r1, REGISTER *r2)
#define ARG_2I (REGISTER *r1, int imm)
#define ARG_2S (REGISTER *r1, unsigned int shamt)
#define ARG_2A (REGISTER *r1, int oi)
#define ARG_1  (REGISTER *r1)
#define ARG_1I (int imm)
#define ARG_1S (unsigned int sham)
#define ARG_1T (unsigned int target)

InstructionSet inst_init();

#endif //SUPERSCALARSIMULATOR_INSTRUCTIONS_H
