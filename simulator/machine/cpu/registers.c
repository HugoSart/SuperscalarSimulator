//
// Created by hsart on 09/07/17.
//

#include "registers.h"

RegistersSet reg_init() {

    RegistersSet reg_set;

    for (unsigned int i = 0; i < REG_COUNT; i++)
        reg_set.reg[i].value = 0;

    return reg_set;
}