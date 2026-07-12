#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

// TODO
//
// STEP 1
// Find every symbol used in message - ok
// Find frequency of every symbol used in message - ok
// Order list of symbol in ascending Order - ok
//
// STEP 2
// Order all symbols in binary tree
//
// STEP 3
// Huffman encoding for every symbol

typedef int (*compare_function)(const void *, const void *);

typedef struct Node {
    int weight;
    char symbol;
    struct Node *nodeLeft;
    struct Node *nodeRight;
} Node;

void printNodeList(Node *list, int list_length) {
  for (int k = 0; k < list_length; k++) {
        
        printf("{ ");

        if(list[k].nodeLeft != NULL){
            printf(".nodeLeft = %c ", list[k].nodeLeft->symbol);
        } else {
            printf(".nodeLeft = NULL, ");
        }

        if(list[k].nodeRight != NULL){
            printf(".nodeRight = %c ", list[k]. nodeRight->symbol);
        } else {
            printf(".nodeRight = NULL, ");
        }

    printf(".weight = %d, .symbol = ", list[k].weight);
    switch (list[k].symbol) {
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
      printf("'%c'", list[k].symbol);
    }

    printf(" }\n");
  }
}

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

    //qsort(tree_node_list, tree_node_list_length, sizeof(Node), compare);

    //printf("=================== BUILD TREE =========================\n");
    //printNodeList(tree_node_list, tree_node_list_length);

    //if(tree_node_list_length > 1){
    //    buildTree(tree_node_list, tree_node_list_length, compare);
    //}
}

// Compare weight field of Node struct, ASC order.
int compareByWeight(const void *a, const void *b){
    const Node *nodeA = (const Node *)a;
    const Node *nodeB = (const Node *)b;
    return nodeA->weight - nodeB->weight;
}

int main(int argc, char **argv) {

    if (argc != 2) {
        printf("Usage: %s [file]\n", argv[0]);
        return 1;
    }

    errno = 0;
    int file_fd = open(argv[1], O_RDONLY);
    if (file_fd == -1) {
        printf("Error while trying open [%s]: %s\n", argv[1], strerror(errno));
        exit(EXIT_FAILURE);
    }

    int page_size = sysconf(_SC_PAGESIZE);
    int symbol_list_length = 0;
    Node *symbol_list = NULL;

    char read_buffer[page_size];
    int bytes_read = 0;

    // In this loop iterate through readed buffer from file.
    // Check if symbol exist in Node form inside symbol_list, if exist increase the wheight value.
    // If not exist, realloc symbol_list space and create new Node with current symbol and set weight to 1.
    // This process permit to create a list with n Node that rapreset every char use in file and relative amount 
    // of usage.
    while ((bytes_read = read(file_fd, read_buffer, page_size)) != 0) {

        for (int i = 0; i < bytes_read; i++) {
            int node_exist = 0;

            for (int j = 0; j < symbol_list_length; j++) {
                if (read_buffer[i] == symbol_list[j].symbol) {
                    symbol_list[j].weight++;
                    node_exist = 1;
                    break;
                }
            }

            if (!node_exist) {

                errno = 0;
                void *temp = realloc(symbol_list, (symbol_list_length + 1) * sizeof(Node));

                if (temp == NULL) {
                    printf("Error when trying realloc symbol_list: %s\n", strerror(errno));
                    close(file_fd);
                    free(symbol_list);
                    exit(EXIT_FAILURE);
                }

                symbol_list = temp;
                symbol_list[symbol_list_length++] = (Node){.weight = 1, .symbol = read_buffer[i], .nodeLeft = NULL, .nodeRight = NULL};
            }
        }
    }

    qsort(symbol_list, symbol_list_length, sizeof(Node), compareByWeight);

    printNodeList(symbol_list, symbol_list_length);

    int symbol_list_check = 2;

    while(symbol_list_check > 1){
        printf("symbol_list_check %d \n", symbol_list_check);
        symbol_list_check = buildTree(symbol_list, symbol_list_length, compareByWeight);
    }

    printNodeList(symbol_list, symbol_list_length);

    //buildTree(symbol_list, symbol_list_length, compareByWeight);

    // navigate through tree for build binary value
    
    close(file_fd);
}
