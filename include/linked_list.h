#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Linked list structure contains an inventory item.
struct cllist {
	struct cllist * next;
	struct cllist * prev;
	void * data;
};

typedef struct cllist cllist;

int size(cllist * p_list);
void print_list(cllist * p_list);
cllist * create_node(void * input);
void insert_front(cllist ** pp_list, cllist * p_node);
void insert_back(cllist * p_list, cllist * p_node);
void insert_at(cllist ** pp_list, cllist * p_node, int loc);
cllist * name_find(cllist * p_list, char name[]);
cllist * id_find(cllist * p_list, unsigned int pid);
void delete_at(cllist ** pp_list, int loc);
void sort_by_name(cllist * p_list);
void sort_by_id(cllist * p_list);
void delete_list(cllist ** pp_list);

#endif
