#include <stdio.h>
#include <stdlib.h>

#include "node_list.h"
#include "tree.h"

int buildTree(NodeList *node_list)
{
  while (node_list->length > 1) {

    sortNodeListByWeight(node_list);

    Node *left = extractFirstNode(node_list);
    if (left == NULL)
      return -1;

    Node *right = extractFirstNode(node_list);
    if (right == NULL)
      return -1;

    Node *merged_node = mergeNodes(left, right);
    if (merged_node == NULL)
      return -1;

    if (insertNode(node_list, merged_node) != 0)
      return -1;
  }

  return 0;
}
