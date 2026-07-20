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

void printNode(Node *node);

Node *createNode(char symbol, int weight, Node* left, Node* right);

Node *mergeNodes(Node* left, Node * right);
