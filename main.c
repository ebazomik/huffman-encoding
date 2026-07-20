#include <errno.h>
#include <fcntl.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "src/tree.h"
#include "src/node_list.h"

int main(int argc, char **argv) {

  if (argc != 2) {
    printf("Usage: %s [file]\n", argv[0]);
    return 1;
  }

  size_t exit_status = EXIT_SUCCESS;

  long page_size = sysconf(_SC_PAGESIZE);
  char read_buffer[page_size];

  NodeList *node_list = NULL;

  int file_fd = open(argv[1], O_RDONLY);
  if (file_fd == -1) {
    printf("Error while trying open [%s]: %s\n", argv[1], strerror(errno));
    return EXIT_FAILURE;
  }

  node_list = createNodeList();
  if(node_list == NULL) {
      exit_status = EXIT_FAILURE;
      goto clean;
  }

  ssize_t bytes_read = 0;
  while ((bytes_read = read(file_fd, read_buffer, page_size)) > 0) {

    int err = buildFrequencyList(read_buffer, bytes_read, node_list);
    if (err) {
        exit_status = EXIT_FAILURE;
        goto clean;
    }
  }

  if (bytes_read == -1) {
      printf("Error on bytes_read\n");
      goto clean;
  }


  if(buildTree(node_list) != 0){
      exit_status = EXIT_FAILURE;
      goto clean;
  }

  clean:
    close(file_fd);
    if(node_list != NULL)
        freeNodeList(node_list);
    return exit_status;
}
