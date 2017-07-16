//
// Created by hsart on 16/07/17.
//

#include "fifo.h"

FIFO fifo_init() {
    FIFO fifo = { .first = NULL };
    return fifo;
}

void fifo_add(FIFO *fifo, Opcode code, EType type, void *realization) {

    Node *node = malloc(sizeof(Node));
    node->instruction.code = code;
    node->instruction.type = type;
    node->instruction.realization = realization;
    node->next = NULL;

    if (fifo->first == NULL) {
        fifo->first = node;
    } else {
        Node *aux;
        for (aux = fifo->first; aux->next != NULL; aux = aux->next);
        aux->next = node;
    }

}

Instruction fifo_remove(FIFO *fifo) {

    Instruction instruction;

    if (fifo->first == NULL) {
        instruction.code.opcode = 0;
        instruction.type = TYPE_UNKNOWN;
        instruction.realization = NULL;
    } else {
        instruction = fifo->first->instruction;
        Node *aux = fifo->first;
        fifo->first = fifo->first->next;
        free(aux);
    }
    return instruction;

}

void fifo_print(FIFO *fifo) {
    printf("FIFO -> ");
    for (Node *node = fifo->first; node != NULL; node = node->next) {
        printf("0x%02X ", node->instruction.code.r.op);
    }
    printf("<-\n");
}