#include "node.h"


Node *findNode(char symbol, Node *node_list, int node_list_length)
{
  for (int i = 0; i < node_list_length; i++) {
    if (symbol == node_list[i].symbol) {
      return &node_list[i];
    }
  }
  return NULL;
}


int appendNode(Node node, Node **node_list, int *node_list_length)
{
  errno = 0;

  void *temp = realloc(*node_list, (*node_list_length + 1) * sizeof(Node));

  if (temp == NULL) {
    printf("Error when trying realloc symbol_list: %s\n", strerror(errno));
    return 1;
  }

  *node_list = (Node *)temp;
  (*node_list)[(*node_list_length)] = node;

  (*node_list_length)++;

  return 0;
}


int countSymbolFrequency(char *buffer, int buffer_size, Node **node_list,
                         int *node_list_length)
{
  for (int i = 0; i < buffer_size; i++) {

    Node *node = findNode(buffer[i], *node_list, *node_list_length);

    if (node != NULL) {
      node->weight++;
    } else {
      Node new_node = {.weight = 1,
                       .symbol = buffer[i],
                       .nodeLeft = NULL,
                       .nodeRight = NULL};

      int err = appendNode(new_node, node_list, node_list_length);
      if(err) return 1;
    }
  }
  return 0;
}
