#include <stdio.h>
#include "utils.h"


void printNode(Node *node)
{
    printf("{ ");

    if (node->nodeLeft != NULL) {
      printf(".nodeLeft = %c ", node->nodeLeft->symbol);
    } else {
      printf(".nodeLeft = NULL, ");
    }

    if (node->nodeRight != NULL) {
      printf(".nodeRight = %c ", node->nodeRight->symbol);
    } else {
      printf(".nodeRight = NULL, ");
    }

    printf(".weight = %d, .symbol = ", node->weight);

    switch (node->symbol)
    {
        case '\n':
            printf("'\\n'");
            break;
        case '\t':
            printf("'\\t'");
            break;
        case ' ':
            printf("'SPACE'");
            break;
        default:
            printf("'%c'", node->symbol);
    }

    printf(" }\n");
}


void printNodeList(Node *list, int list_length)
{
  for (int k = 0; k < list_length; k++) {
      printNode(&list[k]);
  }
}

// Compare weight field of Node struct, ASC order.
int compareByWeight(const void *a, const void *b)
{
    const Node *nodeA = (const Node *)a;
    const Node *nodeB = (const Node *)b;

    return nodeA->weight - nodeB->weight;
}
