#include <stdlib.h>
#include "node_list.h"
#include "utils.h"

void printNodeList(NodeList *node_list)
{
  for (int k = 0; k < node_list->length; k++) {
      printNode(node_list->list[k]);
  }
}

NodeList *createNodeList()
{
    NodeList *node_list = malloc(sizeof(NodeList));
    if(node_list == NULL){
        printf("Error on malloc node_list in createNodeList\n");
        return NULL;
    }

    node_list->list = NULL;
    node_list->list = 0;

    return node_list;
}

Node *findNode(char symbol, NodeList *node_list)
{
  for (int i = 0; i < node_list->length; i++) {
    if (symbol == node_list->list[i]->symbol) {
      return node_list->list[i];
    }
  }
  return NULL;
}

int appendNode(Node *node, NodeList *node_list)
{
  errno = 0;

  void *temp = realloc(node_list->list, (node_list->length + 1) * sizeof(Node *));

  if (temp == NULL) {
    printf("Error when trying realloc symbol_list: %s\n", strerror(errno));
    return 1;
  }

  node_list->list = (Node **)temp;
  node_list->list[node_list->length] = node;

  node_list->length++;

  return 0;
}

int buildFrequencyList(char *buffer, int buffer_size, NodeList *node_list)
{
  for (int i = 0; i < buffer_size; i++) {

    Node *node = findNode(buffer[i], node_list);

    if (node != NULL) {
      node->weight++;
    } else {
      Node *new_node = createNode(buffer[i], 1, NULL, NULL);
      if(new_node == NULL){
          printf("Error on create new node in countSymbolFrequency\n");
          return 1;
      }

      int err = appendNode(new_node, node_list);
      if(err) return 1;
    }
  }
  return 0;
}

void sortNodeListByWeight(NodeList *node_list)
{
    qsort(node_list->list, node_list->length, sizeof(Node *), compareByWeight);
}

Node *extractFirstNode(NodeList *node_list)
{
    Node *first = node_list->list[0];

    for(int i = 1; i < node_list->length; i++){
        node_list->list[i-1] = node_list->list[i];
    }

    void* temp = realloc(node_list->list, (node_list->length - 1) * sizeof(Node *));
    if(temp == NULL){
        printf("Error on realloc in sortNodeListByWeight\n");
        return NULL;
    }

    node_list->list = (Node** )temp;
    node_list->length--;

    return first;
};

int insertNode(NodeList* node_list, Node* node)
{
    void *temp = realloc(node_list->list, (node_list->length + 1) * sizeof(Node *));
    if(temp == NULL){
        printf("Error on realloc in inserNode\n");
        return -1;
    }

    node_list->list = (Node **)temp;
    node_list->list[node_list->length] = node;
    node_list->length++;

    return 0;
}


void freeNodeList(NodeList *node_list)
{
    if(node_list == NULL) return;

    for(int i = 0; i < node_list->length; i++){
        free(node_list->list[i]);
    }

    free(node_list->list);
    free(node_list);
}
