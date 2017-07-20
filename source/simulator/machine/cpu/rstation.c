//
// Created by hsart on 16/07/17.
//

#include "types.h"

int rstation_index(CPU *cpu, ReservationStation *rstation) {
    for (int i = 0; i < 7; i++) {
        if (rstation == cpu->pipeline.rstation) {
            return i;
        }
    }
    return -1;
}