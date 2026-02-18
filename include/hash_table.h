#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <err.h>
#include <errno.h>
#include <math.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/time.h>

// Hash node structure contains a linked list.
struct hash_node
{
    int key;
	void * value;
};
typedef struct hash_node hash_node;

// Hash table structure contains an array of hash nodes.
struct hash_table
{
    hash_node ** nodes;
    int count;
    int size;
};
typedef struct hash_table hash_table;

hash_table * create_table(int size);
void insert(hash_table * p_table, void * item);
unsigned long hash_function(int item, int size);
void * search_by_id(hash_table * p_table, unsigned int part_id);
int find_key(hash_table * p_table, char part_name[]);
void * search_by_name(hash_table * p_table, char item[]);
void delete_by_name(hash_table * p_table, char item[]);
void delete_by_id(hash_table * p_table, unsigned int part_id);
void delete_all(hash_table * p_table);
void print_table(hash_table * p_table);
void list_by_id(hash_table * p_table);
void list_by_name(hash_table * p_table);

#endif
