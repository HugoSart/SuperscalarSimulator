//
// Created by hsart on 24/07/17.
//

#include "cdb_fifo.h"

CDBFifo cdbfifo_init() {
    CDBFifo fifo = { .first = NULL };
    return fifo;
}

void cdbfifo_add(CDBFifo *fifo, ERStation tag, ERegisters destination, Word data) {

    CDBNode *node = malloc(sizeof(INode));
    node->tag = tag;
    node->destination = destination;
    node->data = data;
    node->next = NULL;

    if (fifo->first == NULL) {
        fifo->first = node;
    } else {
        CDBNode *aux;
        for (aux = fifo->first; aux->next != NULL; aux = aux->next);
        aux->next = node;
    }

}

void cdbfifo_remove(CDBFifo *fifo) {

    if (fifo->first == NULL) {

    } else {
        CDBNode *aux = fifo->first;
        fifo->first = fifo->first->next;
        free(aux);
    }

}

void cdbfifo_print(CDBFifo *fifo) {
    for (CDBNode *node = fifo->first; node != NULL; node = node->next) {
        printf("%d", node->data);
        if (node->next != NULL) printf(", ");
    }
}
size_t cdbfifo_size(CDBFifo *fifo);