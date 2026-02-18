## Makefile to create executable inventory file.

## Parameters to control Makefile operation.
CC = gcc
CFLAGS = -Wall -Wextra -g

## Entries to bring executable inventory up to date.

all: bin/inventory tests/test

tests/test: tests/test.c helper_functions.o inventory_item.o linked_list.o hash_table.o
	$(CC) $(CFLAGS) -o tests/test tests/test.c inventory_item.o linked_list.o hash_table.o

bin/inventory: src/inventory.c helper_functions.o inventory_item.o linked_list.o hash_table.o
	$(CC) $(CFLAGS) -o bin/inventory src/inventory.c helper_functions.o inventory_item.o linked_list.o hash_table.o

hash_table.o: src/hash_table.c include/hash_table.h
	$(CC) $(CFLAGS) -c src/hash_table.c

linked_list.o: src/linked_list.c include/linked_list.h
	$(CC) $(CFLAGS) -c src/linked_list.c

inventory_item.o: src/inventory_item.c include/inventory_item.h
	$(CC) $(CFLAGS) -c src/inventory_item.c

helper_functions.o: src/helper_functions.c include/helper_functions.h
	$(CC) $(CFLAGS) -c src/helper_functions.c

run: bin/inventory inventory_data/little_endian_sample.bin inventory_data/little_endian_saved.bin
	./bin/inventory inventory_data/little_endian_sample.bin inventory_data/little_endian_saved.bin

test: bin/inventory
	./bin/inventory < tests/test.txt inventory_data/little_endian_sample.bin

clean:
	$(RM) *.o bin/inventory