//
// Created by hsart on 24/07/17.
//

#ifndef SUPERSCALARSIMULATOR_CDB_FIFO_H
#define SUPERSCALARSIMULATOR_CDB_FIFO_H

#include "../types.h"

CDBFifo cdbfifo_init();

void cdbfifo_add(CDBFifo *fifo, ERStation tag, ERegisters destination, Word data);
void cdbfifo_remove(CDBFifo *fifo);
void cdbfifo_print(CDBFifo *fifo);
size_t cdbfifo_size(CDBFifo *fifo);

#endif //SUPERSCALARSIMULATOR_CDB_FIFO_H
