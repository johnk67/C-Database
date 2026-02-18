#include "../include/linked_list.h"
#include "../include/inventory_item.h"

// Return the size of the list.
int size(cllist * p_list)
{
	int count = 0;
	if (NULL != p_list)
	{
		cllist * p_temp = p_list;
		do
		{
			count++;
            p_temp = p_temp->next;
	    } while (p_temp != p_list);
	}
	return count;
}

// Print out the list.
void print_list(cllist * p_list)
{
	if (NULL == p_list)
	{
		printf("List is empty.\n");
	}
	else
	{
		cllist * p_temp;
		p_temp = p_list;
		printf("\n");
		printf("%-10s %-10s\n", "ID", "Name");
		do
		{
			printf("%-10d %-10s\n", ((inventory_item *)p_temp->data)->id, ((inventory_item *)p_temp->data)->name);
            p_temp = p_temp->next;
		} while (p_temp != p_list);
		printf("\n");
	}
}

// Create a new node
cllist * create_node(void * input)
{
	cllist * p_node;
	p_node = malloc(sizeof(* p_node));
	p_node->data = input;
	// Node points to itself since it's the only node in the list.
    p_node->next = p_node;
	p_node->prev = p_node;
	return p_node;
}

// Insert a node into the front of the list.
void insert_front(cllist ** pp_list, cllist * p_node)
{
	// Create a new node if the list is empty.
	if (NULL == * pp_list)
	{
		create_node(p_node->data);
	}
	// Set the pointer from the end of the list to the new node.
	(* pp_list)->prev->next = p_node;
	// Set the pointer from the start of the list to the new node.
	(* pp_list)->next->prev = p_node;
	// Set the pointer from the new node to the start of the list.
	p_node->next = * pp_list;
	// Set the pointer from the new node to the end of the list.
	p_node->prev = (* pp_list)->prev;
	// Set the new node as the start of the list.
	* pp_list = p_node;
}

// Insert a node into the end of the list.
void insert_back(cllist * p_list, cllist * p_node)
{
	// Create a new node if the list is empty.
	if (NULL == p_list->data)
	{
		p_list->data = p_node->data;
	}
	else
    {
		// Set the pointer from the new node to the end of the list.
		p_node->prev = p_list->prev;
		// Set the pointer from the new node to the start of the list.
		p_node->next = p_list;
		// Set the pointer from the end of the list to the new node.
		p_list->prev->next = p_node;
		// Set the pointer from the start of the list to the new node.
		p_list->prev = p_node;
	}
}

// Insert a node at a specified location in the list.
void insert_at(cllist ** pp_list, cllist * p_node, int loc)
{
	struct cllist * p_temp = * pp_list;
	if (0 == loc)
	{
		insert_front(pp_list, p_node);
	}
	else
	{
		// If location is greater than the size of the list, insert at end.
		for (int i = 0; (i < loc - 1) && (p_temp != (* pp_list)->prev); i++)
    	{
        	p_temp = p_temp->next;
    	}
    	p_node->next = p_temp->next;
		p_node->prev = p_temp;
		p_temp->next->prev = p_node;
		p_temp->next = p_node;
	}
	
}

// Find the first occurrence of a part in a list given its name. Return NULL if not found.
cllist * name_find(cllist * p_list, char name[])
{
	struct cllist * p_temp = p_list;
    inventory_item * p_part = malloc(sizeof(inventory_item));
    p_part = (inventory_item *) p_temp->data;
	while (strcmp(p_part->name, name))
	{
		p_temp = p_temp->next;
		p_part = (inventory_item *) p_temp->data;
		// Break the loop after finding the first occurrence.
		if (p_temp == p_list)
		{
			p_temp = NULL;
			break;
		}
	}
	return p_temp;
}

// Find the first occurrence of a part in a list given its ID. Return NULL if not found.
cllist * id_find(cllist * p_list, unsigned int pid)
{
	struct cllist * p_temp = p_list;
    inventory_item * p_part = malloc(sizeof(inventory_item));
    p_part = (inventory_item *) p_temp->data;
	while (p_part->id != pid)
	{
		p_temp = p_temp->next;
		// Break the loop after finding the first occurrence.
		if (p_temp == p_list)
		{
			p_temp = NULL;
			break;
		}
	}
	return p_temp;
}

// Delete the item at a specified location in the list.
void delete_at(cllist ** pp_list, int loc)
{
	struct cllist * p_temp = * pp_list;
	for (int i = 0; (i < loc) && (p_temp != (* pp_list)->prev); i++)
	{
		p_temp = p_temp->next;
	}
	// Reassign pointers.
	p_temp->next->prev = p_temp->prev;
	p_temp->prev->next = p_temp->next;
	// Reassign first pointer to the second node if first node is deleted.
	if (0 == loc)
	{
		* pp_list = p_temp->next;
	}
	// Free memory.
	free(p_temp);
	p_temp = NULL;
}

// Sort the list alphabetically by name.
void sort_by_name(cllist * p_list)
{
	struct cllist * p_temp1 = p_list;
	struct cllist * p_temp2 = p_list;
	void * p_val;

    // Sort list using insertion sort.
    do
	{
		p_temp2 = p_temp1->next;

		while (p_temp2 != p_list)
		{
			if (0 < strcmp(((inventory_item *) p_temp1->data)->name, ((inventory_item *) p_temp2->data)->name))
			{
                p_val = p_temp1->data;
				p_temp1->data = p_temp2->data;
				p_temp2->data = p_val;
			}
			p_temp2 = p_temp2->next;
		}

		p_temp1 = p_temp1->next;
	} while (p_temp1 != p_list);
}

// Sort the list by part ID.
void sort_by_id(cllist * p_list)
{
	struct cllist * p_temp1 = p_list;
	struct cllist * p_temp2 = p_list;
	void * p_val;

    // Sort list using insertion sort.
    do
	{
		p_temp2 = p_temp1->next;

		while (p_temp2 != p_list)
		{
			if (((inventory_item *) p_temp1->data)->id > ((inventory_item *) p_temp2->data)->id)
			{
                p_val = p_temp1->data;
				p_temp1->data = p_temp2->data;
				p_temp2->data = p_val;
			}
			p_temp2 = p_temp2->next;
		}

		p_temp1 = p_temp1->next;
	} while (p_temp1 != p_list);
}

// Delete the list.
void delete_list(cllist ** pp_list)
{
	int length = size(* pp_list);
	for (int i = 0; i < length; i++)
	{
		delete_at(pp_list, 0);
	}
	* pp_list = NULL;
}
