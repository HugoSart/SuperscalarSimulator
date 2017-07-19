//
// Created by hsart on 16/07/17.
//

#include "fifo.h"

FIFO fifo_init() {
    FIFO fifo = { .first = NULL };
    return fifo;
}

void fifo_add(FIFO *fifo, Opcode code, ERType type, InstructionRef *ref) {

    Node *node = malloc(sizeof(Node));
    node->instruction.code = code;
    node->instruction.rtype = type;
    node->instruction.ref = ref;
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
        instruction.rtype = RTYPE_UNKNOWN;
        instruction.ref->realization = NULL;
        instruction.ref->mnemonic = NULL;
        instruction.ref->type = NULL;
    } else {
        instruction = fifo->first->instruction;
        Node *aux = fifo->first;
        fifo->first = fifo->first->next;
        free(aux);
    }
    return instruction;

}

size_t fifo_size(FIFO *fifo) {

    size_t size = 0;
    for (Node *node = fifo->first; node != NULL; node = node->next, size++);
    return size;

}

void fifo_print(FIFO *fifo) {
    for (Node *node = fifo->first; node != NULL; node = node->next) {
        printf("%s", node->instruction.ref->mnemonic);
        if (node->next != NULL) printf(", ");
    }
}