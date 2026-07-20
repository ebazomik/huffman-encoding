#include <stdio.h>
#include "utils.h"

// Compare weight field of Node struct, ASC order.
int compareByWeight(const void *a, const void *b)
{
    const Node *nodeA = (const Node *)a;
    const Node *nodeB = (const Node *)b;

    return nodeA->weight - nodeB->weight;
}
