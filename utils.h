#pragma once
#include "node.h"

typedef int (*compare_function)(const void *, const void *);
void printNode(Node *node);
void printNodeList(Node *list, int list_length);
int compareByWeight(const void *a, const void *b);
