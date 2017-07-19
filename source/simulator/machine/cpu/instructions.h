//
// Created by hsart on 09/07/17.
//

#ifndef SUPERSCALARSIMULATOR_INSTRUCTIONS_H
#define SUPERSCALARSIMULATOR_INSTRUCTIONS_H

#include <stdarg.h>
#include "types.h"
#include "alu.h"
#include "cache.h"

#define CLOCK_UNKNOWN -1

#define CLOCK_ARITHMETIC 2
#define CLOCK_SHIFT 1
#define CLOCK_LOGICAL 1
#define CLOCK_IF 2
#define CLOCK_MULT 5
#define CLOCK_ACUMULATOR 1
#define CLOCK_JMP 2
#define CLOCK_LOAD 4

InstructionSet inst_init();

#endif //SUPERSCALARSIMULATOR_INSTRUCTIONS_H
