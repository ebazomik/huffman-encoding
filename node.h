#pragma once
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>


typedef struct Node {
    int weight;
    char symbol;
    struct Node *nodeLeft;
    struct Node *nodeRight;
} Node;

Node *findNode(char symbol, Node* node_list, int node_list_length);

int countSymbolFrequency(char *buffer, int buffer_size, Node **node_list, int *node_list_length);
