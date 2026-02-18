#include "../include/hash_table.h"
#include "../include/linked_list.h"
#include "../include/inventory_item.h"

// Create a new hash table.
hash_table * create_table(int size)
{
    // Allocate memory for the new hash table.
    hash_table * p_table = (hash_table *)malloc(sizeof(hash_table));
    p_table->size = size;
    p_table->count = 0;
    // Allocate memory for the array of hash nodes within the hash table.
    p_table->nodes = (hash_node **)calloc(p_table->size, sizeof(hash_node));
    // Initialize the hash nodes to NULL.
    for (int i = 0; i < p_table->size; i++)
    {
        p_table->nodes[i] = NULL;
    }
    return p_table;
}

// Insert an item into the hash table.
void insert(hash_table * p_table, void * item)
{
    int pos = hash_function(((inventory_item *)item)->id, p_table->size);
    // Handle collisions using chaining.
    if (p_table->nodes[pos])
    {
        insert_back(p_table->nodes[pos]->value, create_node((inventory_item *) item));
    }
    else
    {
        // Allocate memory for the new node.
        p_table->nodes[pos] = malloc(sizeof(hash_node));
        p_table->nodes[pos]->key = pos;
        p_table->nodes[pos]->value = create_node((inventory_item *) item);
    }
    p_table->count++;
}

// Given the input and size of the hash table, calculate and return the key
// where the input should be placed.
unsigned long hash_function(int item, int size)
{
    // Key is the remainder of the item divided by the size of the table.
    return item % size;
}

// Return the part given the part ID in a hash table.
void * search_by_id(hash_table * p_table, unsigned int part_id)
{
    cllist * p_temp = malloc(sizeof(cllist));
    p_temp = NULL;
    int loc = hash_function(part_id, p_table->size);
    if (p_table->nodes[loc])
    {
        p_temp = id_find((cllist *) p_table->nodes[loc]->value, part_id);
    }
    return p_temp;
}

// Return the position of the part in the hash table.
int find_key(hash_table * p_table, char part_name[])
{
    int loc = -1;
    cllist * p_temp = malloc(sizeof(cllist));
    for (int i = 0; i < p_table->size; i++)
    {
        if (p_table->nodes[i])
        {
            p_temp = name_find((cllist *) p_table->nodes[i]->value, part_name);
            if (p_temp)
            {
                loc = i;
                break;
            }
        }
    }
    return loc;
}

// Return the part given the part name in a hash table.
// If the part is not in the table, return NULL.
void * search_by_name(hash_table * p_table, char part_name[])
{
    cllist * p_temp = malloc(sizeof(cllist));
    int loc = find_key(p_table, part_name);
    if (-1 == loc)
    {
        p_temp = NULL;
    }
    else
    {
        p_temp = name_find((cllist *) p_table->nodes[loc]->value, part_name);
    }
    return p_temp;
}

// Delete a part in the hash table given its name.
void delete_by_name(hash_table * p_table, char part_name[])
{
    int loc = find_key(p_table, part_name);
    cllist ** pp_part = (cllist **) search_by_name(p_table, part_name);
    if (pp_part)
    {
        // Delete the linked list node.
        delete_at(pp_part, 0);
        // Free hash table node if no parts are left in it.
        if (0 == size(* pp_part))
        {
            free(p_table->nodes[loc]);
            p_table->nodes[loc] = NULL;
            p_table->count--;
        }
    }
}

// Delete a part in the hash table given its ID.
void delete_by_id(hash_table * p_table, unsigned int part_id)
{
    int loc = hash_function(part_id, p_table->size);
    cllist ** pp_part = (cllist **) search_by_id(p_table, part_id);
    if (pp_part)
    {
        // Delete the linked list node.
        delete_at(pp_part, 0);
        // Free hash table node if no parts are left in it.
        if (0 == size(* pp_part))
        {
            free(p_table->nodes[loc]);
            p_table->nodes[loc] = NULL;
            p_table->count--;
        }
    }
}

// Delete all items in a hash table.
void delete_all(hash_table * p_table)
{
    for (int i = 0; i < p_table->size; i++)
    {
        if (p_table->nodes[i])
        {
            cllist * p_temp = (cllist *) p_table->nodes[i]->value;
            delete_by_name(p_table, ((inventory_item *) p_temp->data)->name);
        }
    }
    free(p_table);
}

// Print a hash table in a user-readable format.
void print_table(hash_table * p_table)
{
    printf("\nHash Table\n-------------------\n");
    printf("Size: %d\n", p_table->size);
    printf("Count: %d\n", p_table->count);
    printf("%-10s %-10s\n", "Key", "Value");
    for (int i = 0; i < p_table->size; i++)
    {
        if (p_table->nodes[i])
        {
            printf("%-10d", p_table->nodes[i]->key);
            print_list((cllist *) p_table->nodes[i]->value);
        }
    }

    printf("-------------------\n\n");
}

// Print parts in numerical order by part ID.
void list_by_id(hash_table * p_table)
{
    cllist * p_parts = create_node(NULL);
    for (int i = 0; i < p_table->size; i++)
    {
        if (p_table->nodes[i])
        {
            cllist * p_list = (cllist *) p_table->nodes[i]->value;
            cllist * p_temp = p_list;
            do
            {
                insert_back(p_parts, create_node((inventory_item *) p_temp->data));
                p_temp = p_temp->next;
            } while (p_temp != p_list);
        }
    }
    sort_by_id(p_parts);
    print_list(p_parts);
    delete_list(&p_parts);
}

// Print parts in alphabetical order by part name.
void list_by_name(hash_table * p_table)
{
    cllist * p_parts = create_node(NULL);
    for (int i = 0; i < p_table->size; i++)
    {
        if (p_table->nodes[i])
        {
            cllist * p_list = (cllist *) p_table->nodes[i]->value;
            cllist * p_temp = p_list;
            do
            {
                insert_back(p_parts, create_node((inventory_item *) p_temp->data));
                p_temp = p_temp->next;
            } while (p_temp != p_list);
        }
    }
    sort_by_name(p_parts);
    print_list(p_parts);
    delete_list(&p_parts);
}
