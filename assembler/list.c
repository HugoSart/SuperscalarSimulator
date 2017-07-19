//
// Created by hsart on 15/07/17.
//

#include <stdio.h>
#include "list.h"

List varList = {0};

void list_add(List *list, char *label, unsigned int offset) {
    LNode *newNode = malloc(sizeof(LNode));
    newNode->offset = offset;
    newNode->label = strdup(label);
    newNode->next = list->first;
    list->first = newNode;
    printf("Label %s added.\n", label);
}

LNode *list_get(List *list, char *label) {
    for (LNode *node = list->first; node != NULL; node = node->next) {
        if (!strcmp(node->label, label)) return node;
    }
    return NULL;
}

void list_print(List *list) {
    printf("List -> ");
    for (LNode *node; node != NULL; node = node->next) {
        printf("%s(%d) ", node->label, node->offset);
    }
    printf("<-\n");
}