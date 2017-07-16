//
// Created by hsart on 15/07/17.
//

#ifndef SUPERSCALARSIMULATOR_LIST_H
#define SUPERSCALARSIMULATOR_LIST_H

typedef struct label_node {
    unsigned int offset;
    char *label;
    struct label_node *next;
} Node;

typedef struct list {
    Node *first;
} List;

void list_add(List *list, char *label, unsigned int offset);

Node *list_get(List *list, char *label);

void list_print(List *list);

#endif //SUPERSCALARSIMULATOR_LIST_H
