#include "node.h"

void printNode(Node *node)
{
    printf("{ ");

    if (node->nodeLeft != NULL) {
        if(node->nodeLeft->symbol == '\0'){
            printf(".nodeLeft = \\0");
        } else {
            printf(".nodeLeft = %c ", node->nodeLeft->symbol);
        }

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

Node *createNode(char symbol, int weight, Node* left, Node* right)
{
    Node* new_node = malloc(sizeof(Node));

    if(new_node == NULL) return NULL;

    new_node->symbol = symbol;
    new_node->weight = weight;
    new_node->nodeLeft = left;
    new_node->nodeRight = right;

    return new_node;
}

Node *mergeNodes(Node* left, Node * right){
    int tot_weight = left->weight + right->weight;
    Node *merged_node = malloc(sizeof(Node *));
    if(merged_node == NULL){
        printf("Error on malloc in mergeNodes\n");
        return NULL;
    }
    merged_node = createNode('\0', tot_weight, left, right);
    if(merged_node == NULL){
        printf("Error on createNode in mergeNodes\n");
        return NULL;
    }

    return merged_node;
}
