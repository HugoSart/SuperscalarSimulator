//
// Created by hsart on 16/07/17.
//

#include "inst_fifo.h"

IFIFO ififo_init() {
    IFIFO fifo = { .first = NULL };
    return fifo;
}

void ififo_add(IFIFO *fifo, Opcode code, ERType type, InstructionRef *ref) {

    INode *node = malloc(sizeof(INode));
    node->instruction.code = code;
    node->instruction.rtype = type;
    node->instruction.ref = ref;
    node->next = NULL;

    if (fifo->first == NULL) {
        fifo->first = node;
    } else {
        INode *aux;
        for (aux = fifo->first; aux->next != NULL; aux = aux->next);
        aux->next = node;
    }

}

Instruction ififo_remove(IFIFO *fifo) {

    Instruction instruction;

    if (fifo->first == NULL) {
        instruction.code.opcode = 0;
        instruction.rtype = RTYPE_UNKNOWN;
        instruction.ref = NULL;
    } else {
        instruction = fifo->first->instruction;
        INode *aux = fifo->first;
        fifo->first = fifo->first->next;
        free(aux);
    }
    return instruction;

}

size_t ififo_size(IFIFO *fifo) {

    size_t size = 0;
    for (INode *node = fifo->first; node != NULL; node = node->next, size++);
    return size;

}

void ififo_print(IFIFO *fifo) {
    for (INode *node = fifo->first; node != NULL; node = node->next) {
        printf("%s", node->instruction.ref->mnemonic);
        if (node->next != NULL) printf(", ");
    }
}