#include <stdlib.h>
#include <stdio.h>

#include "tree.h"

int buildTree(Node *list, int list_length, compare_function compare){

    int tree_node_list_length = 0;
    Node *tree_node_list = NULL;

    for (int i = 0; i < list_length; i += 2){
        Node *nl = malloc(sizeof(Node));
        if(nl == NULL){
            printf("Error nl alloc while build tree_node_list -> cycle %d\n", i);
            exit(EXIT_FAILURE);
        }
        *nl = list[i];

        Node *nr = malloc(sizeof(Node));
        if(i + 1 <= list_length){

            if(nr == NULL){
                printf("Error nr malloc while build tree_node_list -> cycle %d\n", i);
                exit(EXIT_FAILURE);
            }
            *nr = list[i+1];
        } else {
            free(nr);
            nr = NULL;
        }

        void *temp = realloc(tree_node_list, (tree_node_list_length + 1 ) * sizeof(Node));
        if(temp == NULL){
            printf("Error on realloc whils build tree_node_list -> cycle %d\n", i);
            if(nr != NULL) free(nr);
            free(nl);
            exit(EXIT_FAILURE);
        }
        tree_node_list = temp;
        tree_node_list[tree_node_list_length++] = (Node){ .nodeLeft = nl, .nodeRight = nr, .weight = (nl->weight + nr->weight) };
    }

    free(list);

    return tree_node_list_length;
}
