//
// Created by hsart on 09/07/17.
//

#include "registers.h"

RegistersSet reg_init() {

    RegistersSet reg_set = { .reg[0 ... (REG_COUNT - 1)] = 0};

    return reg_set;
}