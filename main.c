#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "node.h"
#include "tree.h"
#include "utils.h"


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
  Node *node_list = NULL;
  int node_list_length = 0;

  char read_buffer[page_size];
  int bytes_read = 0;

  // In this loop iterate through readed buffer from file.
  // Check if symbol exist in Node form inside symbol_list, if exist increase
  // the wheight value. If not exist, realloc symbol_list space and create new
  // Node with current symbol and set weight to 1. This process permit to create
  // a list with n Node that rapreset every char use in file and relative amount
  // of usage.
  while ((bytes_read = read(file_fd, read_buffer, page_size)) != 0) {

    int err = countSymbolFrequency(read_buffer, page_size, &node_list, &node_list_length);

    if (err) {
      close(file_fd);
      free(node_list);
      exit(EXIT_FAILURE);
    }
  }

  qsort(node_list, node_list_length, sizeof(Node), compareByWeight);

  printNodeList(node_list, node_list_length);

  int symbol_list_check = 2;

  while (symbol_list_check > 1) {
    printf("symbol_list_check %d \n", symbol_list_check);
    symbol_list_check =
        buildTree(node_list, node_list_length, compareByWeight);
  }

  printNodeList(node_list, node_list_length);

  close(file_fd);
}
