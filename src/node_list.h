#pragma once
#include "node.h"

typedef struct NodeList {
  Node **list;
  int length;
} NodeList;

void printNodeList(NodeList *node_list);

NodeList *createNodeList();

void sortNodeListByWeight(NodeList *node_list);

Node *extractFirstNode(NodeList *node_list);

Node *findNode(char symbol, NodeList *node_list);

int appendNode(Node *node, NodeList *node_list);

int buildFrequencyList(char *buffer, int buffer_size, NodeList *node_list);

int insertNode(NodeList *node_list, Node *node);

void freeNodeList(NodeList *nodeList);
