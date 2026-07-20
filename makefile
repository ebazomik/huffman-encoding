CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -Iinclude

SRC = main.c \
      src/node.c \
      src/node_list.c \
      src/tree.c \
      src/utils.c

OBJ = $(SRC:.c=.o)

huffman: $(OBJ)
	$(CC) $(OBJ) -o huffman

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f *.o src/*.o huffman
