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
// Order list of symbol in ascending Order
//
// STEP 2
// Order all symbols in binary tree
//
// STEP 3
// Huffman encoding for every symbol

typedef struct Node {
  int weight;
  char symbol;
} Node;

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
        void *temp =
            realloc(symbol_list, (symbol_list_length + 1) * sizeof(Node));

        if (temp == NULL) {
          printf("Error when trying realloc symbol_list: %s\n",
                 strerror(errno));
          close(file_fd);
          free(symbol_list);
          exit(EXIT_FAILURE);
        }

        symbol_list = temp;
        symbol_list[symbol_list_length++] =
            (Node){.weight = 1, .symbol = read_buffer[i]};
      }
    }
  }

  for (int k = 0; k < symbol_list_length; k++) {
    printf("{ .weight = %d; .symbol = ", symbol_list[k].weight);

    switch (symbol_list[k].symbol) {
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
      printf("'%c'", symbol_list[k].symbol);
    }

    printf(" }\n");
  }

  close(file_fd);
  free(symbol_list);
}
