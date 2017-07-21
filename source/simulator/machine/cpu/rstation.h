//
// Created by hsart on 16/07/17.
//

#ifndef SUPERSCALARSIMULATOR_RESTATIONS_H
#define SUPERSCALARSIMULATOR_RESTATIONS_H

#include <stdbool.h>

#define NOT_BUSY (-1)
#define FINISHED 0

typedef struct rstation_t ReservationStation;

int rstation_index(CPU *cpu, ReservationStation *rstation);
void rstation_clean(ReservationStation *);

#endif //SUPERSCALARSIMULATOR_RESTATIONS_H
